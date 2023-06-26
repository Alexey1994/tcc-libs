#ifndef GRAPHICS_3D_OBJECT_WAVEFRONT_INCLUDED
#define GRAPHICS_3D_OBJECT_WAVEFRONT_INCLUDED


#include <file.c>
#include <reader.c>
#include <data-structures/stack.c>
#include <graphics/image/TGA.c>


typedef struct {
	Real_Number32 x;
	Real_Number32 y;
	Real_Number32 z;
}
Wavefront_Object_Vertex;


typedef struct {
	Real_Number32 s;
	Real_Number32 t;
}
Wavefront_Object_Texture_Coord;


typedef struct {
	Number vertex_index;
	Number texture_coord_index;
	Number normal_index;
}
Wavefront_Object_Face_Index;


typedef struct {
	Stack  name;
	Stack  points;
	Stack  lines;
	Stack  triangles;
	Stack  quads;
	Number material_index;
}
Wavefront_Object_Face;


typedef struct {
	Stack  name;
	Number texture_id;
}
Wavefront_Object_Material;


typedef struct {
	Stack vertices;
	Stack texture_coords;
	Stack normals;
	Stack faces;
	Stack materials;
}
Wavefront_Object;


static Boolean is_Wavefront_Object_space_character(char character)
{
	return character == ' ' || character == '\t';
}

static void read_Wavefront_Object_spaces(Reader* reader)
{
	while(!end_of_reader(reader) && is_Wavefront_Object_space_character(get_reader_byte(reader)))
		read_next_byte(reader);
}


Boolean read_Wavefront_Object_Face_Index(Reader* reader, Wavefront_Object_Face_Index* index)
{
	Byte character;

	read_Wavefront_Object_spaces(reader);
	character = get_reader_byte(reader);

	if(!is_number_character(character) && character != '-') {
		return 0;
	}

	index->vertex_index = read_Number(reader);
	index->texture_coord_index = 0;
	index->normal_index = 0;

	if(get_reader_byte(reader) == '/') {
		read_next_byte(reader);
		index->texture_coord_index = read_Number(reader);

		if(get_reader_byte(reader) == '/') {
			read_next_byte(reader);
			index->normal_index = read_Number(reader);
		}
	}

	return 1;
}


static void read_Wavefront_Object_Name(Reader* reader, Stack* name)
{
	Byte character;
	
	read_Wavefront_Object_spaces(reader);
			
	while(!end_of_reader(reader)) {
		character = get_reader_byte(reader);

		if(character == '\r' || character == '\n')
			break;

		add_bytes_in_stack(name, &character, sizeof(character));
		read_next_byte(reader);
	}
	character = 0;
	add_bytes_in_stack(name, &character, sizeof(character));
}


static void add_Wavefront_Object_relative_path(Stack* name, Byte* path_to_wavefront)
{
	Number last_slash_index;
	Number i;
	Byte   character;

	last_slash_index = 0;
	for(i = 0; path_to_wavefront[i]; ++i) {
		if(path_to_wavefront[i] == '/')
			last_slash_index = i + 1;
	}

	if(last_slash_index) {
		for(i = 0; i < last_slash_index; ++i) {
			character = path_to_wavefront[i];
			add_bytes_in_stack(name, &character, sizeof(character));
		}
	}
}


Boolean read_Wavefront_Object_Material_Library(Byte* file_name, Wavefront_Object* object, Byte* object_file_name)
{
	File                      material_file;
	Reader                    reader;
	Byte                      reader_buffer[16];
	Wavefront_Object_Material material;
	
	material_file = open_file(file_name);
	
	if(!material_file) {
		return 0;
	}

	initialize_reader(&reader, material_file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
	material.name.data = 0;
	material.texture_id = 0;

	while(!end_of_reader(&reader)) {
		if(read_if(&reader, "map_Kd ")) {
			if(!material.texture_id) {
				Stack texture_name;
				initialize_stack(&texture_name, 16);
				add_Wavefront_Object_relative_path(&texture_name, object_file_name);
				read_Wavefront_Object_Name(&reader, &texture_name);
				
				File texture_file;
				Image image;
				
				texture_file = open_file(texture_name.data);
				if(texture_file) {
					if(read_TGA_image(texture_file, &read_bytes_from_file, &image)) {
						material.texture_id = create_texture_from_Image(&image);
						deinitialize_image(&image);
					}
					
					close_file(texture_file);
				}

				deinitialize_stack(&texture_name);
			}
		}
		else if(read_if(&reader, "newmtl ")) {
			if(material.name.data) {
				add_bytes_in_stack(&object->materials, &material, sizeof(material));
				material.texture_id = 0;
			}

			initialize_stack(&material.name, 16);
			read_Wavefront_Object_Name(&reader, &material.name);
		}

		read_line(&reader);
	}

	if(material.name.data) {
		add_bytes_in_stack(&object->materials, &material, sizeof(material));
	}

	close_file(material_file);

	return 1;
}


static Number find_Wavefront_Object_Material_index(Wavefront_Object* object, Stack* name)
{
	Wavefront_Object_Material* material;
	Number i;

	for(i = 0; i < object->materials.size; i += sizeof(Wavefront_Object_Material)) {
		material = object->materials.data + i;

		if(!compare_bytes(material->name.data, material->name.size, name->data, name->size)) {
			return i + 1;
		}
	}

	return 0;
}


Boolean read_Wavefront_Object(Byte* file_path, Wavefront_Object* object)
{
	File   file;
	Reader reader;
	Byte   reader_buffer[512];
	
	Wavefront_Object_Vertex        vertex;
	Wavefront_Object_Texture_Coord texture_coord;
	Wavefront_Object_Face_Index    index1;
	Wavefront_Object_Face_Index    index2;
	Wavefront_Object_Face_Index    index3;
	Wavefront_Object_Face_Index    index4;
	Wavefront_Object_Face          face;
	
	file = open_file(file_path);
	
	if(!file) {
		return 0;
	}
	
	initialize_reader(&reader, file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
	
	initialize_stack(&object->vertices, 128);
	initialize_stack(&object->texture_coords, 128);
	initialize_stack(&object->normals, 128);
	initialize_stack(&object->faces, 128);
	initialize_stack(&object->materials, 128);
	
	initialize_stack(&face.name, 16);
	initialize_stack(&face.points, 16);
	initialize_stack(&face.lines, 16);
	initialize_stack(&face.triangles, 128);
	initialize_stack(&face.quads, 128);
	
	while(!end_of_reader(&reader)) {
		if(read_if(&reader, "v ")) {
			read_Wavefront_Object_spaces(&reader);
			vertex.x = read_Real_Number(&reader);

			read_Wavefront_Object_spaces(&reader);
			vertex.y = read_Real_Number(&reader);

			read_Wavefront_Object_spaces(&reader);
			vertex.z = read_Real_Number(&reader);

			add_bytes_in_stack(&object->vertices, &vertex, sizeof(vertex));
		}
		else if(read_if(&reader, "vt ")) {
			read_Wavefront_Object_spaces(&reader);
			texture_coord.s = read_Real_Number(&reader);

			read_Wavefront_Object_spaces(&reader);
			texture_coord.t = read_Real_Number(&reader);

			add_bytes_in_stack(&object->texture_coords, &texture_coord, sizeof(texture_coord));
		}
		else if(read_if(&reader, "vn ")) {
			read_Wavefront_Object_spaces(&reader);
			vertex.x = read_Real_Number(&reader);

			read_Wavefront_Object_spaces(&reader);
			vertex.y = read_Real_Number(&reader);

			read_Wavefront_Object_spaces(&reader);
			vertex.z = read_Real_Number(&reader);

			add_bytes_in_stack(&object->normals, &vertex, sizeof(vertex));
		}
		else if(read_if(&reader, "f ")) {
			read_Wavefront_Object_Face_Index(&reader, &index1);

			if(!read_Wavefront_Object_Face_Index(&reader, &index2)) {
				add_bytes_in_stack(&face.points, &index1, sizeof(index1));
			}
			else if(!read_Wavefront_Object_Face_Index(&reader, &index3)) {
				add_bytes_in_stack(&face.lines, &index1, sizeof(index1));
				add_bytes_in_stack(&face.lines, &index2, sizeof(index2));
			}
			else if(!read_Wavefront_Object_Face_Index(&reader, &index4)) {
				add_bytes_in_stack(&face.triangles, &index1, sizeof(index1));
				add_bytes_in_stack(&face.triangles, &index2, sizeof(index2));
				add_bytes_in_stack(&face.triangles, &index3, sizeof(index3));
			}
			else {
				add_bytes_in_stack(&face.quads, &index1, sizeof(index1));
				add_bytes_in_stack(&face.quads, &index2, sizeof(index2));
				add_bytes_in_stack(&face.quads, &index3, sizeof(index3));
				add_bytes_in_stack(&face.quads, &index4, sizeof(index4));
			}
		}
		else if(read_if(&reader, "usemtl ")) {
			Stack material_name;
			initialize_stack(&material_name, 16);
			read_Wavefront_Object_Name(&reader, &material_name);
			face.material_index = find_Wavefront_Object_Material_index(object, &material_name);
			deinitialize_stack(&material_name);
		}
		else if(read_if(&reader, "mtllib ")) {
			Stack mtllib_file_name;
			initialize_stack(&mtllib_file_name, 16);
			add_Wavefront_Object_relative_path(&mtllib_file_name, file_path);
			read_Wavefront_Object_Name(&reader, &mtllib_file_name);	
			read_Wavefront_Object_Material_Library(mtllib_file_name.data, object, file_path);
			deinitialize_stack(&mtllib_file_name);
		}
		else {
			read_line(&reader);
		}
	}
	
	add_bytes_in_stack(&object->faces, &face, sizeof(face));
	close_file(file);
}


void draw_Wavefront_Object_Face_Index(Wavefront_Object* object, Wavefront_Object_Face_Index* index)
{
	Wavefront_Object_Vertex*        normal;
	Wavefront_Object_Vertex*        vertex;
	Wavefront_Object_Texture_Coord* texture_coord;

	if(index->normal_index > 0) {
		normal = object->normals.data + (index->normal_index - 1) * sizeof(Wavefront_Object_Vertex);
		glNormal3f(normal->x, normal->y, normal->z);
	}

	if(index->texture_coord_index > 0) {
		texture_coord = object->texture_coords.data + (index->texture_coord_index - 1) * sizeof(Wavefront_Object_Texture_Coord);
		glTexCoord2f(texture_coord->s, texture_coord->t);
	}

	if(index->vertex_index > 0) {
		vertex = object->vertices.data + (index->vertex_index - 1) * sizeof(Wavefront_Object_Vertex);
		glVertex3f(vertex->x, vertex->y, vertex->z);
	}
}


void draw_Wavefront_Object(Wavefront_Object* object)
{
	Number                       i;
	Number                       j;
	Wavefront_Object_Face*       face;
	Wavefront_Object_Face_Index* index;
	Wavefront_Object_Vertex*     vertex;
	Wavefront_Object_Material*   material;
	
	for(i = 0; i < object->faces.size; i += sizeof(Wavefront_Object_Face)) {
		face = object->faces.data + i;

		if(face->material_index) {
			material = object->materials.data + (face->material_index - 1) * sizeof(Wavefront_Object_Material);
			
			if(material->texture_id) {
				glBindTexture(GL_TEXTURE_2D, material->texture_id);
			}
		}

		glBegin(GL_TRIANGLES);
		for(j = 0; j < face->triangles.size; j += sizeof(Wavefront_Object_Face_Index) * 3) {
			index = face->triangles.data + j;
			draw_Wavefront_Object_Face_Index(object, index);
			draw_Wavefront_Object_Face_Index(object, index + 1);
			draw_Wavefront_Object_Face_Index(object, index + 2);
		}
		glEnd();

		glBegin(GL_QUADS);
		for(j = 0; j < face->quads.size; j += sizeof(Wavefront_Object_Face_Index) * 4) {
			index = face->quads.data + j;
			draw_Wavefront_Object_Face_Index(object, index);
			draw_Wavefront_Object_Face_Index(object, index + 1);
			draw_Wavefront_Object_Face_Index(object, index + 2);
			draw_Wavefront_Object_Face_Index(object, index + 3);
		}
		glEnd();
	}
}


#endif//GRAPHICS_3D_OBJECT_WAVEFRONT_INCLUDED

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
	Wavefront_Object object;
	
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
		
		if(!read_Wavefront_Object("untitled.obj", &object)) {
			return 1;
		}
	}
	end_draw_3D(window_display);
	
	for(;;) {
		while(pop_window_message()) {
			
		}
		
		begin_draw_3D(window_display, display_3D);
		{
			glLoadIdentity();
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glScalef(aspect_ratio, 1.0f, 1.0f);
			
			draw_Wavefront_Object(&object);
		}
		end_draw_3D(window_display);
		
		Sleep(10);
	}
	
	return 0;
}*/