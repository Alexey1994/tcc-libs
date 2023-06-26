#ifndef GRAPHICS_IMAGE
#define GRAPHICS_IMAGE


#include <types.c>
#include <graphics.c>


typedef struct {
	Number width;
	Number height;
	Number bits_per_pixel;
	Byte*  pixels;
}
Image;


void deinitialize_image(Image* image)
{
	if(image->pixels) {
		free_memory(image->pixels);
		image->pixels = 0;
	}
}


Number32 create_texture_from_Image(Image* image)
{
	Number32 texture_id;
	
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image->width,
		image->height,
		0,
		image->bits_per_pixel == 24
			? GL_BGR
			: GL_BGRA,
		GL_UNSIGNED_BYTE,
		image->pixels
	);

	return texture_id;
}


#endif//GRAPHICS_IMAGE