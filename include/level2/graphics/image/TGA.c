#ifndef GRAPHICS_IMAGE_TGA_INCLUDED
#define GRAPHICS_IMAGE_TGA_INCLUDED


#include "image.c"
#include <memory.c>
#include <graphics.c>


Boolean read_TGA_image(
	void* source,
	Signed_Number (*read_bytes)(void* source, Byte* bytes, Number number_of_bytes),
	Image* image
)
{
	Byte     header[12];
	Number16 width;
	Number16 height;
	Number8  bits_per_pixel;
	Number8  maybe_reserved;
	Number8  number_of_chunks;
	
	Number   bytes_per_pixel;
	Number   number_of_pixels;
	Number   number_of_bytes;
	Boolean  is_compressed;
	
	Byte*    pixels;
	Byte     repeatable_pixels[4];
	
	if(read_bytes(source, header, sizeof(header)) < sizeof(header)) {
		goto error;
	}
	
	if(header[2] == 10) {
		is_compressed = 1;
	}
	else if(header[2] == 2) {
		is_compressed = 0;
	}
	else {
		goto error;
	}
	
	if(read_bytes(source, &width, sizeof(width)) < sizeof(width)) {
		goto error;
	}
	
	if(read_bytes(source, &height, sizeof(height)) < sizeof(height)) {
		goto error;
	}
	
	if(read_bytes(source, &bits_per_pixel, sizeof(bits_per_pixel)) < sizeof(bits_per_pixel)) {
		goto error;
	}
	
	if(read_bytes(source, &maybe_reserved, sizeof(maybe_reserved)) < sizeof(maybe_reserved)) {
		goto error;
	}
	
	bytes_per_pixel = bits_per_pixel / 8;
	number_of_pixels = width * height;
	
	if(bytes_per_pixel > 4) {
		goto error;
	}
	
	number_of_bytes = number_of_pixels * bytes_per_pixel;
	pixels = allocate_memory(number_of_bytes);
	
	if(is_compressed) {
		while(number_of_pixels) {
			if(read_bytes(source, &number_of_chunks, sizeof(number_of_chunks)) < sizeof(number_of_chunks)) {
				goto error_and_free;
			}
			
			if(number_of_chunks < 128) {
				++number_of_chunks;
				
				if(number_of_pixels < number_of_chunks) {
					goto error_and_free;
				}
				
				number_of_pixels -= number_of_chunks;
				
				if(read_bytes(source, pixels, number_of_chunks * bytes_per_pixel) < number_of_chunks * bytes_per_pixel) {
					goto error_and_free;
				}
				
				pixels += number_of_chunks * bytes_per_pixel;
			}
			else {
				number_of_chunks -= 127;
				
				if(number_of_pixels < number_of_chunks) {
					goto error_and_free;
				}
				
				number_of_pixels -= number_of_chunks;
				
				if(read_bytes(source, repeatable_pixels, bytes_per_pixel) < bytes_per_pixel) {
					goto error_and_free;
				}

				while(number_of_chunks) {
					copy_bytes(pixels, repeatable_pixels, bytes_per_pixel);
					pixels += bytes_per_pixel;
					--number_of_chunks;
				}
			}
		}
	}
	else {
		if(read_bytes(source, pixels, number_of_bytes) < number_of_bytes) {
			goto error_and_free;
		}
	}
	
	image->width = width;
	image->height = height;
	image->bits_per_pixel = bits_per_pixel;
	image->pixels = pixels;
	
	return 1;
	
	error_and_free: {
		free_memory(pixels);	
	}
	
	error: {
		image->width = 0;
		image->height = 0;
		image->bits_per_pixel = 0;
		image->pixels = 0;
		
		return 0;
	}
}


#endif//GRAPHICS_IMAGE_TGA_INCLUDED

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
	Image image;
	File tga_file;
	
	tga_file = open_file("a.tga");
	if(!read_TGA_image(tga_file, &read_bytes_from_file, &image)) {
		return 1;
	}
	
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
		
		texture_id = create_texture_from_Image(&image);
		deinitialize_image(&image);
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
			glBindTexture(GL_TEXTURE_2D, texture_id);
			
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 0);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,  1, 0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1,  1, 0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1, -1, 0);
			}
			glEnd();
		}
		end_draw_3D(window_display);
		
		Sleep(10);
	}
	
	return 0;
}*/