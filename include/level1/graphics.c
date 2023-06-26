#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED


#include <Windows/gdi32.c>
#include <Windows/opengl32.c>
#include <string.c>


typedef struct {
	Number32 x;
	Number32 y;
}
Point;


Byte* get_main_display(Number display_index)
{
	//return CreateDCW(L"DISPLAY", 0, 0, 0);
	return GetDC(display_index);
}


Byte* create_display(Byte* parent_display, Number width, Number height)
{
	Byte* display;
	Byte* bitmap;

	display = CreateCompatibleDC(parent_display);
	bitmap = CreateCompatibleBitmap(parent_display, width, height);
	SelectObject(display, bitmap);

	return display;
}


void draw_pixel(Byte* display, Number x, Number y, Number32 color)
{
	Byte* pen;

	pen = CreatePen(0, 1, color);
	SetPixel(display, x, y, color);

	DeleteObject(pen);
}


void draw_line(Byte* display, Number x1, Number y1, Number x2, Number y2, Number32 color)
{
	Byte* pen;

	pen = CreatePen(0, 1, color);
	SelectObject(display, pen);

	MoveToEx(display, x1, y1, 0);
	LineTo(display, x2, y2);

	DeleteObject(pen);
}


void draw_rectangle(Byte* display, Number x, Number y, Number width, Number height, Number32 color)
{
	Byte* brush;

	brush = CreateSolidBrush(color);
	SelectObject(display, brush);

	BeginPath(display);
	{
		Rectangle(display, x, y, x + width, y + height);
	}
	EndPath(display);
	FillPath(display);

	DeleteObject(brush);
}


void draw_polygon(Byte* display, Point* points, Number number_of_points, Number32 color)
{
	Byte* brush;

	brush = CreateSolidBrush(color);
	SelectObject(display, brush);
	BeginPath(display);
	{
		Polygon(display, points, number_of_points);
	}
	EndPath(display);
	FillPath(display);
	DeleteObject(brush);
}


void draw_polygon_Bezier(Byte* display, Point* points, Number number_of_points, Number32 color)
{
	Byte* brush;

	brush = CreateSolidBrush(color);
	SelectObject(display, brush);
	BeginPath(display);
	{
		PolyBezier(display, points, number_of_points);
	}
	EndPath(display);
	FillPath(display);
	DeleteObject(brush);
}


void draw_text(Byte* display, Byte* text, Number x, Number y, Number32 color)
{
	Number16* unicode_text;
	Number16* unicode_text_copy;
	Number    unicode_text_size;

	unicode_text = convert_utf8_to_unicode(text);
	
	unicode_text_copy = unicode_text;
	for(unicode_text_size = 0; *unicode_text_copy; ++unicode_text_copy)
		++unicode_text_size;

	SetBkMode(display, TRANSPARENT);
	SetTextColor(display, color);
	TextOutW(display, x, y, unicode_text, unicode_text_size);

	free_memory(unicode_text);
}


void draw_image(Byte* display, Number x, Number y, Byte* image, Number image_width, Number image_height)
{
	Bitmap_Info bmi = {sizeof(Bitmap_Info), image_width, -image_height, 1, 32};
	SetDIBitsToDevice(display, x, y, image_width, image_height, 0, 0, 0, image_height, image, &bmi, 0);
}


void calculate_text_size(Byte* display, Byte* text, Number* width, Number* height)
{
	Number16* unicode_text;
	Number16* unicode_text_copy;
	Number    unicode_text_size;
	struct {Number32 width; Number32 height;} size;

	unicode_text = convert_utf8_to_unicode(text);
	
	unicode_text_copy = unicode_text;
	for(unicode_text_size = 0; *unicode_text_copy; ++unicode_text_copy)
		++unicode_text_size;
	
	GetTextExtentPoint32W(display, unicode_text, unicode_text_size, &size);
	
	*width = size.width;
	*height = size.height;
	
	free_memory(unicode_text);
}


Byte* create_display3D(Byte* display)
{
	Byte* display3D;

	Windows_Pixel_Format_Descriptor pixel_format_descriptor = {
		.size            = sizeof(Windows_Pixel_Format_Descriptor),
		.nVersion        = 1,
		.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType      = PFD_TYPE_RGBA,
		.cColorBits      = 32,
		.cRedBits        = 0,
		.cRedShift       = 0,
		.cGreenBits      = 0,
		.cGreenShift     = 0,
		.cBlueBits       = 0,
		.cBlueShift      = 0,
		.cAlphaBits      = 0,
		.cAlphaShift     = 0,
		.cAccumBits      = 0,
		.cAccumRedBits   = 0,
		.cAccumGreenBits = 0,
		.cAccumBlueBits  = 0,
		.cAccumAlphaBits = 0,
		.cDepthBits      = 16,
		.cStencilBits    = 0,
		.cAuxBuffers     = 0,
		.iLayerType      = PFD_MAIN_PLANE,
		.bReserved       = 0,
		.dwLayerMask     = 0,
		.dwVisibleMask   = 0,
		.dwDamageMask    = 0
	};
	
	if(!SetPixelFormat(display, ChoosePixelFormat(display, &pixel_format_descriptor), &pixel_format_descriptor)) {
		print_error("SetPixelFormat");
		goto error;
	}
	
	display3D = wglCreateContext(display);
	if(!display3D) {
		print_error("wglCreateContext");
		goto error;
	}
	
	return display3D;
	
	error: {
		return 0;
	}
}

void begin_draw_3D(Byte* display, Byte* display3D)
{
	if(!wglMakeCurrent(display, display3D)) {
		print_error("wglMakeCurrent");
	}

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	float diffuse_color[]  = {1, 1, 1, 1};
	float specular_color[] = {1, 1, 1, 1};
	float ambient_color[]  = {0.9, 0.9, 0.9, 0};
	float light_position[] = {0.0, 0.0, -10000.0, 0};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 2);
	//glOrtho(2.0, 2.0, 2.0, 2.0, 1, 2);
	//glFrustum(-2.0, 2.0, -2.0, 2.0, 0.1, 2);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//glFrustum(2.0, 2.0, 2.0, 2.0, 1, 2);
	glMatrixMode(GL_MODELVIEW);
}


void end_draw_3D(Byte* display)
{
	SwapBuffers(display);
}


void destroy_display3D(Byte* display3D)
{
	wglDeleteContext(display3D);
}


#endif //GRAPHICS_INCLUDED

/*
#include <Windows/opengl32.c>
#include <window.c>


Byte* handle_messages(Window* window)
{
	return 0;
}


void test_2D()
{
	Window window;
	Byte*  main_display;
	Byte*  display;

	//window.parent = 0;
	//window.handler = &handle_messages;
	initialize_window(&window, 0, &handle_messages);
	set_window_name(&window, "WXВовкаWX");
	set_window_position(&window, 0, 0, 600, 600);
	show_window(&window);
	
	//main_display = get_main_display(0);
	main_display = get_window_display(&window);
	display = create_display(main_display, 300, 300);
	
	for(;;) {
		while(pop_window_message()) {
			
		}
		
		draw_pixel(display, 300, 300, 255 << 8);
		draw_line(display, 0, 0, 50, 50, 255);
		draw_rectangle(display, 0, 0, 100, 100, 255 << 8);
		//Arc(display, 0, 0, 100, 100, 300, 300, 300, 300);
		
		{
			Point points[3] = {
				200, 100,
				250, 0,
				300, 100
			};

			draw_polygon(display, points, sizeof(points) / sizeof(Point), 255);
		}

		{
			Point bezier_points[] = {
				0, 100,
				100, 0,
				100, 0,
				200, 100
			};

			draw_polygon_Bezier(display, bezier_points, sizeof(bezier_points) / sizeof(Point), 255);
		}

		draw_text(display, "Жопка", 100, 100, 255 + (255 << 8));

		BitBlt(main_display, 0, 0, 300, 300, display, 0, 0, SRCCOPY);

		Sleep(4);
	}
	
	stop: {
		deinitialize_window(&window);
	}
}


void test_3D()
{
	Window window;
	Byte*  main_display;
	Byte*  display;
	Byte*  display3D;

	//window.parent = 0;
	//window.handler = &handle_messages;
	initialize_window(&window, 0, &handle_messages);
	set_window_name(&window, "WXВовкаWX");
	set_window_position(&window, 0, 0, 200, 200);
	show_window(&window);

	//main_display = get_main_display(0);
	main_display = get_window_display(&window);
	display = create_display(main_display, 300, 300);
	display3D = create_display3D(main_display);
	
	for(;;) {
		while(pop_window_message()) {

		}

		begin_draw_3D(main_display, display3D);
		glClear(GL_COLOR_BUFFER_BIT);
		end_draw_3D(main_display);

		Sleep(4);
	}
	
	stop: {
		deinitialize_window(&window);
	}
}


Number main(Number number_of_arguments, Byte** arguments)
{
	//test_2D();
	test_3D();
	
	return 0;
}*/