#ifndef GRAPHICS_3D_DFF_INCLUDED
#define GRAPHICS_3D_DFF_INCLUDED


#include <reader.c>
#include <graphics.c>


typedef enum {
	DFF_STRUCT        = 0x0001,
	DFF_STRING        = 0x0002,
	DFF_EXTENSION     = 0x0003,
	DFF_TEXTURE       = 0x0006,
	DFF_MATERIAL      = 0x0007,
	DFF_MATERIALLIST  = 0x0008,
	DFF_FRAMELIST     = 0x000E,
	DFF_GEOMETRY      = 0x000F,
	DFF_CLUMP         = 0x0010,
	DFF_ATOMIC        = 0x0014,
	DFF_GEOMETRYLIST  = 0x001A,
	DFF_RENDERRIGHTS  = 0x001F,

	DFF_MORPHPLG      = 0x0105,
	DFF_SKINPLG       = 0x116,
	DFF_HANIMPLG      = 0x11E,
	DFF_MATEFFECTS    = 0x0120,
	DFF_BINMESHPLG    = 0x050E,
	DFF_FRAMENAME     = 0x253F2FE,
	DFF_COLLISION     = 0x253F2FA,
	DFF_MATSPECULAR   = 0x253F2F6,
	DFF_NIGHTCOLS     = 0x253F2F9,
	DFF_MATREFLECTION = 0x253F2FC,
	DFF_MESHEXTENSION = 0x253F2FD
}
DFF_Header_Type;

typedef struct {
	DFF_Header_Type type;
	Number32        size;
	Number32        version;
}
DFF_Header;

typedef enum {
	DFF_TRISTRIP              = 0x0001,
	DFF_POSITIONS             = 0x0002,
	DFF_TEXTURED              = 0x0004,
	DFF_PRELIT                = 0x0008,
	DFF_NORMALS               = 0x0010,
	DFF_LIGHT                 = 0x0020,
	DFF_MODULATEMATERIALCOLOR = 0x0040,
	DFF_TEXTURED2             = 0x0080
}
DFF_Geometry_Flag;

typedef struct {
	Number         number_of_vertieces;
	Real_Number32* vertieces;

	Number         number_of_normals;
	Real_Number32* normals;

	Number         number_of_triangles;
	Number*        triangles;
}
DFF_Object;

typedef struct {
	struct {
		DFF_Header_Type type;
		Number32        size;
		Number32        version;
	}
	header;

	Number      number_of_objects;
	DFF_Object* objects;

	DFF_Object* current_object;
}
DFF_Model;


Boolean read_DFF_section(DFF_Model* model, Reader* reader, DFF_Header_Type type)
{
	Number     i;
	Number     j;

	read_bytes(reader, &model->header, sizeof(model->header));

	if(model->header.type != type) {
		print("%d %d %d\n", model->header.type, model->header.size, model->header.version);
		goto error;
	}

	model->header.version = (model->header.version & 0xFFFF0000)
		? (((model->header.version >> 14) & 0x3FF00) + 0x30000) | (model->header.version >> 16) & 0x3F
		: (model->header.version << 8);

	//print("%d %d %d\n", header.type, header.size, header.version);

	switch(model->header.type) {
		case DFF_CLUMP: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number32 atomic_count = read_binary_Number32(reader);

			if(!read_DFF_section(model, reader, DFF_FRAMELIST))
				goto error;

			if(!read_DFF_section(model, reader, DFF_GEOMETRYLIST))
				goto error;
			break;
		}

		case DFF_FRAMELIST: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number32 frame_count = read_binary_Number32(reader);

			for(i = 0; i < frame_count; ++i) {
				printf("rot [%f %f %f\n%f %f %f\n%f %f %f]\n",
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),

					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),

					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader)
				);

				printf("pos %f %f %f\n",
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader),
					read_binary_Real_Number32(reader)
				);

				print("parent %d\n", read_binary_Number32(reader));
				print("flags %d\n\n", read_binary_Number32(reader));
			}

			for(i = 0; i < frame_count; ++i) {
				if(!read_DFF_section(model, reader, DFF_EXTENSION))
					goto error;
			}

			print("\n");

			break;
		}

		case DFF_GEOMETRYLIST: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number32 geometry_count = read_binary_Number32(reader);

			model->number_of_objects = geometry_count;
			model->objects = allocate_memory(geometry_count * sizeof(DFF_Object));

			for(i = 0; i < geometry_count; ++i) {
				model->current_object = model->objects + i;

				if(!read_DFF_section(model, reader, DFF_GEOMETRY))
					goto error;
			}

			break;
		}

		case DFF_GEOMETRY:
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number16 flags = read_binary_Number16(reader);
			Number16 textures_count = read_binary_Number16(reader);
			Number32 triangles_count = read_binary_Number32(reader);
			Number32 vertieces_count = read_binary_Number32(reader);
			Number32 morph_count = read_binary_Number32(reader);

			print("%d textures, %d triangles, %d vertieces\n", textures_count, triangles_count, vertieces_count);

			model->current_object->number_of_vertieces = vertieces_count;
			model->current_object->vertieces = allocate_memory(vertieces_count * 3 * sizeof(Real_Number32));

			model->current_object->number_of_triangles = triangles_count;
			model->current_object->triangles = allocate_memory(triangles_count * 3 * sizeof(Number));

			model->current_object->number_of_normals = 0;

			if(model->header.version < 0x34001) {
				Real_Number32 ambient = read_binary_Real_Number32(reader);
				Real_Number32 specular = read_binary_Real_Number32(reader);
				Real_Number32 diffuse = read_binary_Real_Number32(reader);
			}

			if(flags & DFF_PRELIT) {
				for(i = 0; i < vertieces_count; ++i) {
					//Number32 color = read_binary_Number32(reader); //RGBA
					print("prelit RGBA(%d, %d, %d, %d)\n", read_binary_Number8(reader), read_binary_Number8(reader), read_binary_Number8(reader), read_binary_Number8(reader));
				}
			}

			for(i = 0; i < textures_count; ++i) {
				for(j = 0; j < vertieces_count; ++j) {
					printf("uv: %f %f\n", read_binary_Real_Number32(reader), read_binary_Real_Number32(reader));
				}
			}

			for(i = 0; i < triangles_count; ++i) {
				Number16 c = read_binary_Number16(reader);
				Number16 b = read_binary_Number16(reader);
				Number16 mat = read_binary_Number16(reader);
				Number16 a = read_binary_Number16(reader);

				model->current_object->triangles[i * 3] = a;
				model->current_object->triangles[i * 3 + 1] = b;
				model->current_object->triangles[i * 3 + 2] = c;
			}

			if(morph_count != 1) {
				print("multiple frames not supported\n");
				goto error;
			}

			for(i = 0; i < morph_count; ++i) {
				Real_Number32 bx = read_binary_Real_Number32(reader);
				Real_Number32 by = read_binary_Real_Number32(reader);
				Real_Number32 bz = read_binary_Real_Number32(reader);
				Real_Number32 br = read_binary_Real_Number32(reader);
				Signed_Number32 has_verts = read_binary_Signed_Number32(reader);
				Signed_Number32 has_normals = read_binary_Signed_Number32(reader);

				if(has_verts) {
					for(j = 0; j < vertieces_count; ++j) {
						Real_Number32 x = read_binary_Real_Number32(reader);
						Real_Number32 y = read_binary_Real_Number32(reader);
						Real_Number32 z = read_binary_Real_Number32(reader);

						model->current_object->vertieces[j * 3] = x;
						model->current_object->vertieces[j * 3 + 1] = y;
						model->current_object->vertieces[j * 3 + 2] = z;
					}
				}

				if(has_normals) {
					model->current_object->number_of_normals = vertieces_count;
					model->current_object->normals = allocate_memory(vertieces_count * 3 * sizeof(Real_Number32));

					for(j = 0; j < vertieces_count; ++j) {
						Real_Number32 x = read_binary_Real_Number32(reader);
						Real_Number32 y = read_binary_Real_Number32(reader);
						Real_Number32 z = read_binary_Real_Number32(reader);

						model->current_object->normals[j * 3] = x;
						model->current_object->normals[j * 3 + 1] = y;
						model->current_object->normals[j * 3 + 2] = z;
					}
				}
			}

			if(!read_DFF_section(model, reader, DFF_MATERIALLIST))
				goto error;

			if(!read_DFF_section(model, reader, DFF_EXTENSION))
				goto error;

			break;

		case DFF_MATERIALLIST: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number32 material_count = read_binary_Number32(reader);
			Number32 junk;

			for(i = 0; i < material_count; ++i)
				junk = read_binary_Signed_Number32(reader);

			for(i = 0; i < material_count; ++i)
				if(!read_DFF_section(model, reader, DFF_MATERIAL))
					goto error;
			break;
		}

		case DFF_MATERIAL: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number32 flags = read_binary_Number32(reader);
			Number32 col = read_binary_Number32(reader);
			Number32 x = read_binary_Number32(reader);
			Number32 textured = read_binary_Number32(reader);
			Real_Number32 ambient = read_binary_Real_Number32(reader);
			Real_Number32 specular = read_binary_Real_Number32(reader);
			Real_Number32 diffuse = read_binary_Real_Number32(reader);

			if(textured) {
				if(!read_DFF_section(model, reader, DFF_TEXTURE))
					goto error;
			}

			if(!read_DFF_section(model, reader, DFF_EXTENSION))
				goto error;

			break;
		}

		case DFF_TEXTURE: {
			if(!read_DFF_section(model, reader, DFF_STRUCT))
				goto error;

			Number16 flags = read_binary_Number16(reader);
			Number16 x = read_binary_Number16(reader);

			//texture name
			if(!read_DFF_section(model, reader, DFF_STRING))
				goto error;

			//alpha name
			if(!read_DFF_section(model, reader, DFF_STRING))
				goto error;

			if(!read_DFF_section(model, reader, DFF_EXTENSION))
				goto error;

			break;
		}

		case DFF_EXTENSION: {
			for(i = 0; i < model->header.size; ++i) {
				Byte c = read_binary_Number8(reader);

				if(c >= 'a' && c <= 'z')
					print("%c", c);
			}

			print("\n");
			break;
		}

		case DFF_STRING: {
			Byte c;
			Boolean end_of_string;

			end_of_string = 0;
			for(i = 0; i < model->header.size; ++i) {
				c = read_binary_Number8(reader);

				if(!c)
					end_of_string = 1;

				if(!end_of_string && c >= 'a' && c <= 'z')
					print("%c", c);
			}
			print("\n");
			break;
		}

		case DFF_STRUCT:
			break;
	}

	return 1;

error:
	return 0;
}


Boolean read_DFF(DFF_Model* model, Reader* reader)
{
	if(!read_DFF_section(model, reader, DFF_CLUMP))
		goto error;

	return 1;

error:
	print("ошибка загрузки DFF\n");
	return 0;
}


void draw_DFF_model(DFF_Model* model, Number object_index)
{
	Number         i;
	Number*        triangle;
	Real_Number32* vertex;
	Real_Number32* normal;
	DFF_Object*    current_object;

	current_object = model->objects + object_index;

	glBegin(GL_TRIANGLES);
	for(i = 0; i < current_object->number_of_triangles; ++i) {
		triangle = current_object->triangles + i * 3;

		vertex = current_object->vertieces + triangle[0] * 3;
		normal = current_object->normals + triangle[0] * 3;
		glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);

		vertex = current_object->vertieces + triangle[1] * 3;
		normal = current_object->normals + triangle[1] * 3;
		glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);

		vertex = current_object->vertieces + triangle[2] * 3;
		normal = current_object->normals + triangle[2] * 3;
		glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);
	}
	glEnd();

	//for(;;);
}


#endif//GRAPHICS_3D_DFF_INCLUDED

/*
#include <file.c>
#include <window.c>
#include <graphics.c>


double sqrt(double n);


void rotate_around_quaternion(float x, float y, float z, float w)
{
	float rotate_matrix[16] = {
		1 - 2*y*y - 2*z*z, 2*x*y - 2*z*w, 2*x*z + 2*y*w, 0,
		2*x*y + 2*z*w, 1 - 2*x*x - 2*z*z, 2*y*z - 2*x*w, 0,
		2*x*z - 2*y*w, 2*y*z + 2*x*w, 1 - 2*x*x - 2*y*y, 0,
		0, 0, 0, 1
	};

	glMultMatrixf(rotate_matrix);
}


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
	DFF_Model  model;

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
		
		
		file = open_file("player.dff");
	
		if(!file) {
			return 1;
		}
		
		initialize_reader(&reader, file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
		read_DFF(&model, &reader);
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
			glScalef(2.0f * aspect_ratio, 2.0f, 2.0f);
			
			draw_DFF_model(&model, 6);
		}
		end_draw_3D(window_display);
		
		Sleep(10);
	}
	
	return 0;
}*/