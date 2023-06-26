#ifndef GRAPHICS_3D_ANIMATION_IFP_INCLUDED
#define GRAPHICS_3D_ANIMATION_IFP_INCLUDED


#include <reader.c>
#include <memory.c>


typedef struct {
	Number header_size;
}
IFP_Animation;


Boolean read_IFP_animation_header(Reader* reader, IFP_Animation* animation, Byte* header_name)
{
	Number size;

	if(!read_if(reader, header_name))
		goto error;

	animation->header_size = read_binary_Number32(reader);

	return 1;

	error: {
		print("получен заголовок %c%c%c\n", read_binary_Number8(reader), read_binary_Number8(reader), read_binary_Number8(reader), read_binary_Number8(reader));
		return 0;
	}
}


Boolean read_IFP_animation(Reader* reader, IFP_Animation* animation)
{
	Number number_of_animations;
	Number number_of_objects;
	Number number_of_frames;
	Number next_sibling;
	Number previous_sibling;
	Byte   b;
	Number i;
	Number j;
	Number k;
	Number l;

	if(!read_IFP_animation_header(reader, animation, "ANPK"))
		goto error;

	if(!read_IFP_animation_header(reader, animation, "INFO"))
		goto error;

	number_of_animations = read_binary_Number32(reader);

	print_error("внутреннее имя: ");
	for(;;) {
		b = read_binary_Number8(reader);

		if(!b)
			break;

		print("%c", b);
	}
	print("\n");

	if((animation->header_size % 4)) {
		for(i = 0; i < 4 - (animation->header_size % 4); ++i)
			read_binary_Number8(reader);
	}

	for(l = 0; l < number_of_animations; ++l) {
		if(!read_IFP_animation_header(reader, animation, "NAME"))
			goto error;
		
		print_error("имя анимации: ");
		for(i = 0; i < animation->header_size; ++i) {
			b = read_binary_Number8(reader);
			print("%c", b);
		}
		print("\n");

		if((animation->header_size % 4)) {
			for(i = 0; i < 4 - (animation->header_size % 4); ++i)
				read_binary_Number8(reader);
		}

		if(!read_IFP_animation_header(reader, animation, "DGAN"))
			goto error;

		if(!read_IFP_animation_header(reader, animation, "INFO"))
			goto error;

		number_of_objects = read_binary_Number32(reader);
		print_error("количество объектов: %d\n", number_of_objects);

		//if(read_binary_Number32(reader))
		//	goto error;
		read_binary_Number32(reader);

		for(i = 0; i < number_of_objects; ++i) {
			if(!read_IFP_animation_header(reader, animation, "CPAN"))
				goto error;

			if(!read_IFP_animation_header(reader, animation, "ANIM"))
				goto error;

			Number anim_header_size = animation->header_size;

			print_error("имя объекта: ");
			for(j = 0; j < 28; ++j) {
				b = read_binary_Number8(reader);
				print("%c", b);
			}
			print("\n");

			number_of_frames = read_binary_Number32(reader);

			//if(read_binary_Number32(reader))
			//	goto error;
			read_binary_Number32(reader);

			next_sibling = read_binary_Number32(reader);
			previous_sibling = read_binary_Number32(reader);

			for(j = 0; j < anim_header_size - 0x2C; ++j)
				read_binary_Number8(reader);

			//for(j = 0; j < number_of_frames; ++j)
			if(number_of_frames) {
				Byte frame_type[4];
				Number frame_data_size;
				float x;
				float y;
				float z;
				float w;
				float time;

				read_bytes(reader, frame_type, 4);
				frame_data_size = read_binary_Number32(reader);

				print_error("%c%c%c%c %d\n", frame_type[0], frame_type[1], frame_type[2], frame_type[3], frame_data_size);
				//R - Rotation
				//T - Translation
				//S - Scale
				//0 - None

				print_error("количество кадров: %d\n", number_of_frames);

				for(j = 0; j < number_of_frames; ++j) {
					for(k = 1; k < 4; ++k) {
						switch(frame_type[k]) {
							case 'R':
								x = read_binary_Real_Number32(reader);
								y = read_binary_Real_Number32(reader);
								z = read_binary_Real_Number32(reader);
								w = read_binary_Real_Number32(reader);
								break;

							case 'T':
								x = read_binary_Real_Number32(reader);
								y = read_binary_Real_Number32(reader);
								z = read_binary_Real_Number32(reader);
								break;

							case 'S':
								x = read_binary_Real_Number32(reader);
								y = read_binary_Real_Number32(reader);
								z = read_binary_Real_Number32(reader);
								break;
						}
					}

					time = read_binary_Real_Number32(reader);
					//printf("%f\n", time);
				}
			}
		}
	}

	return 1;

	error: {
		print_error("ошибка чтения IFP\n");
		return 0;
	}
}


#endif//GRAPHICS_3D_ANIMATION_IFP_INCLUDED


#include <file.c>


Number main(Number number_of_arguments, Byte** arguments)
{
	File          file;
	Reader        reader;
	Byte          reader_buffer[64];
	IFP_Animation animation;
	
	file = open_file("BET.ifp");
	
	if(!file) {
		return 1;
	}

	initialize_reader(&reader, file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
	read_IFP_animation(&reader, &animation);
	close_file(file);
	
	return 0;
}