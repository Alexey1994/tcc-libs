#ifndef GRAPHICS_3D_ANIMATION_INCLUDED
#define GRAPHICS_3D_ANIMATION_INCLUDED


#include <reader.c>
#include <graphics.c>


typedef struct {
	Number8       flags;
	Real_Number32 coords[3];
	Number8       bone_id;
	Number8       reference_count;
}
MS3D_Model_Vertex;

typedef struct {
	Number16      flags;
	Number16      vertex_indices[3];
	Real_Number32 normals[9];
	Real_Number32 texture_s[3];
	Real_Number32 texture_t[3];
	Number8       smoothing_group;
	Number8       group_index;
}
MS3D_Model_Triangle;

typedef struct {
	Number               number_of_vertices;
	MS3D_Model_Vertex*   vertices;

	Number               number_of_triangles;
	MS3D_Model_Triangle* triangles;

}
MS3D_Model;


Boolean read_MS3D(MS3D_Model* model, Reader* reader)
{
	Number i;

	if(!read_if(reader, "MS3D000000"))
		goto error;

	if(read_binary_Number32(reader) != 4) { //version
		goto error;
	}

	model->number_of_vertices = read_binary_Number16(reader);
	model->vertices = allocate_memory(model->number_of_vertices * sizeof(MS3D_Model_Vertex));
	for(i = 0; i < model->number_of_vertices; ++i) {
		model->vertices[i].flags = read_binary_Number8(reader);
		model->vertices[i].coords[0] = read_binary_Real_Number32(reader);
		model->vertices[i].coords[1] = read_binary_Real_Number32(reader);
		model->vertices[i].coords[2] = read_binary_Real_Number32(reader);
		model->vertices[i].bone_id = read_binary_Number8(reader);
		model->vertices[i].reference_count = read_binary_Number8(reader);
	}

	model->number_of_triangles = read_binary_Number16(reader);
	model->triangles = allocate_memory(model->number_of_triangles * sizeof(MS3D_Model_Triangle));
	for(i = 0; i < model->number_of_triangles; ++i) {
		model->triangles[i].flags = read_binary_Number16(reader);
		model->triangles[i].vertex_indices[0] = read_binary_Number16(reader);
		model->triangles[i].vertex_indices[1] = read_binary_Number16(reader);
		model->triangles[i].vertex_indices[2] = read_binary_Number16(reader);
		model->triangles[i].normals[0] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[1] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[2] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[3] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[4] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[5] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[6] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[7] = read_binary_Real_Number32(reader);
		model->triangles[i].normals[8] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_s[0] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_s[1] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_s[2] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_t[0] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_t[1] = read_binary_Real_Number32(reader);
		model->triangles[i].texture_t[2] = read_binary_Real_Number32(reader);
		model->triangles[i].smoothing_group = read_binary_Number8(reader);
		model->triangles[i].group_index = read_binary_Number8(reader);
	}

	return 1;

	error: {
		print_error("ошибка чтения ms3d модели\n");
		return 0;
	}
}


void draw_MS3D_model(MS3D_Model* model)
{
	Number               i;
	MS3D_Model_Triangle* triangle;
	MS3D_Model_Vertex*   vertex;

	glBegin(GL_TRIANGLES);
	for(i = 0; i < model->number_of_triangles; ++i) {
		triangle = model->triangles + i;

		vertex = model->vertices + triangle->vertex_indices[0];
		glNormal3f(triangle->normals[0], triangle->normals[1], triangle->normals[2]);
		glVertex3f(vertex->coords[0], vertex->coords[1], vertex->coords[2]);

		vertex = model->vertices + triangle->vertex_indices[1];
		glNormal3f(triangle->normals[3], triangle->normals[4], triangle->normals[5]);
		glVertex3f(vertex->coords[0], vertex->coords[1], vertex->coords[2]);

		vertex = model->vertices + triangle->vertex_indices[2];
		glNormal3f(triangle->normals[6], triangle->normals[7], triangle->normals[8]);
		glVertex3f(vertex->coords[0], vertex->coords[1], vertex->coords[2]);
	}
	glEnd();
}


#endif//GRAPHICS_3D_ANIMATION_INCLUDED

/*
#include <file.c>
#include <window.c>
#include <graphics.c>


void handle_messages(Window* window)
{
	switch(window->message_type) {
		case CLOSE_MESSAGE: {
			exit(0);
		}
	}
}


Number main(Number number_of_arguments, Byte** arguments)
{
	File       file;
	Reader     reader;
	Byte       reader_buffer[32];
	MS3D_Model model;

	Window        window;
	Byte*         window_display;
	Byte*         display_3D;
	Real_Number32 aspect_ratio;
	Number32      texture_id;
	
	initialize_window(&window, 0, &handle_messages);
	set_window_position(&window, 0, 0, 640, 480);
	show_window(&window);
	window_display = get_window_display(&window);
	display_3D = create_display3D(window_display);
	
	aspect_ratio = 480.0f / 640.0f;
	
	begin_draw_3D(window_display, display_3D);
	{
		glEnable(GL_TEXTURE_2D);
		
		
		file = open_file("breen.ms3d");
	
		if(!file) {
			return 1;
		}
		
		initialize_reader(&reader, file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
		read_MS3D(&model, &reader);
		close_file(file);
	}
	end_draw_3D(window_display);
	
	for(;;) {
		while(pop_window_message()) {
			
		}
		
		begin_draw_3D(window_display, display_3D);
		{
			glLoadIdentity();
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glScalef(0.015f * aspect_ratio, 0.015f, 0.015f);
			
			draw_MS3D_model(&model);
		}
		end_draw_3D(window_display);
		
		Sleep(10);
	}
	
	return 0;
}*/