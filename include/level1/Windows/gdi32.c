#ifndef SYSTEM_WINDOWS_GDI32_INCLUDED
#define SYSTEM_WINDOWS_GDI32_INCLUDED


#include <types.c>


typedef struct {
	Signed_Number32 x;
	Signed_Number32 y;
}
Windows_Point;


typedef struct {
	struct {
		Number32        size_of_structure;
		Signed_Number32 width;
		Signed_Number32 height;
		Number16        planes;
		Number16        bit_count;
		Number32        compression;
		Number32        size_image;
		Signed_Number32 x_pels_per_meter;
		Signed_Number32 y_pels_per_meter;
		Number32        number_of_color_indexes;
		Number32        number_of_color_indexes_important;
	}
	header;
	Number32 color[1];
}
Bitmap_Info;


import stdcall Signed_Number32     SetDIBitsToDevice(
	Byte*           device,
	Signed_Number32 x,
	Signed_Number32 y,
	Number32        width,
	Number32        height,
	Signed_Number32 x_image,
	Signed_Number32 y_image,
	Number32        start_scan,
	Number32        scan_lines_length,
	Byte*           image,
	Bitmap_Info*    bitmap_info,
	Number32        color_type
);


typedef struct {
	Number16  size;
	Number16  nVersion;
	Number32  dwFlags;
	Number8   iPixelType;
	Number8   cColorBits;
	Number8   cRedBits;
	Number8   cRedShift;
	Number8   cGreenBits;
	Number8   cGreenShift;
	Number8   cBlueBits;
	Number8   cBlueShift;
	Number8   cAlphaBits;
	Number8   cAlphaShift;
	Number8   cAccumBits;
	Number8   cAccumRedBits;
	Number8   cAccumGreenBits;
	Number8   cAccumBlueBits;
	Number8   cAccumAlphaBits;
	Number8   cDepthBits;
	Number8   cStencilBits;
	Number8   cAuxBuffers;
	Number8   iLayerType;
	Number8   bReserved;
	Number32  dwLayerMask;
	Number32  dwVisibleMask;
	Number32  dwDamageMask;
}
Windows_Pixel_Format_Descriptor;

#define PFD_DRAW_TO_WINDOW  4
#define PFD_SUPPORT_OPENGL  32
#define PFD_DOUBLEBUFFER    1
#define PFD_TYPE_RGBA   0
#define PFD_MAIN_PLANE  0


import stdcall Number32 ChoosePixelFormat(Byte* device, Windows_Pixel_Format_Descriptor* format_descriptor);
import stdcall Number32 SetPixelFormat(Byte* device, Number32 format, Windows_Pixel_Format_Descriptor* format_descriptor);

import stdcall Byte*    CreateSolidBrush(Number32 color);
import stdcall Byte*    CreatePatternBrush(Byte* pattern);

import stdcall Number32 SwapBuffers(Byte* device);

import stdcall Number32 SetTextColor(Byte* device, Number32 color);
import stdcall Number32 TextOutA(Byte* device, Number32 x, Number32 y, Byte* text, Number32 text_length);
import stdcall Number32 TextOutW(Byte* device, Number32 x, Number32 y, Number16* text, Number32 text_length);
import stdcall Boolean  GetTextExtentPoint32W(Byte* device, Number16* string, Number32 string_length, struct {Number32 width; Number32 height;}* size);

typedef enum {
	FW_DONTCARE = 0,
	FW_THIN = 100,
	FW_EXTRALIGHT = 200,
	FW_LIGHT = 300,
	FW_NORMAL = 400
}
Font_Width;

typedef enum {
	DEFAULT_QUALITY        = 0,
	DRAFT_QUALITY          = 1,
	PROOF_QUALITY          = 2,
	NONANTIALIASED_QUALITY = 3,
	ANTIALIASED_QUALITY    = 4,
	CLEARTYPE_QUALITY      = 5
}
Font_Quality;

typedef enum {
	OUT_TT_PRECIS = 4
}
Font_Precision;

#define ANSI_CHARSET 1251

#define CLIP_DEFAULT_PRECIS 0
#define DEFAULT_PITCH 0
#define FF_DONTCARE 0

import stdcall Byte* CreateFontW(
	Number32 height,
	Number32 width,
	Number32 escapement,
	Number32 orientation,
	Number32 weight,
	Number32 italic,
	Number32 underline,
	Number32 strike_out,
	Number32 charset,
	Number32 out_precision,
	Number32 clip_precision,
	Number32 quality,
	Number32 pitch_and_family,
	Number16* face_name
);

import stdcall Number32 SelectObject(Byte* device, Byte* object);
import stdcall Boolean DeleteObject(Byte* object);

typedef enum {
	TRANSPARENT = 1,
	OPAQUE      = 2
}
Bk_Mode;

import stdcall Number32 SetBkMode(Byte* device, Number32 mode);




//import stdcall Byte* CreateDCW(Number16* driver, Number16* device, Number16* port, Dispaly_Mode* mode);
import stdcall Byte* CreateDCW(Number16* driver, Number16* device, Number16* port, Byte* mode);
import stdcall Byte* CreateCompatibleDC(Byte* device);
import stdcall Boolean DeleteDC(Byte* device);

import stdcall Byte* CreateBitmap(Signed_Number32 width, Signed_Number32 height, Number32 number_of_planes, Number32 bits_per_pixel, void* pixels);
import stdcall Byte* CreateCompatibleBitmap(Byte* device, Signed_Number32 width, Signed_Number32 height);

#define SRCCOPY 0x00CC0020
#define SRCPAINT 0x00EE0086
#define SRCAND 0x008800C6
#define WHITENESS 0x00FF0062
import stdcall Boolean BitBlt(Byte* device, int x, int y, int width, int height, Byte* source_device, int x1, int y1, Number32 rop);


//import stdcall Byte* CreateRectRgn(Signed_Number32 x1, Signed_Number32 y1, Signed_Number32 x2, Signed_Number32 y2);
//import stdcall Boolean FillRgn(Byte* device, Byte* region, Byte* brush);
import stdcall Boolean Rectangle(Byte* device, Number32 x1, Number32 y1, Number32 x2, Number32 y2);


#define DC_BRUSH 18
#define DC_PEN 19

import stdcall Byte* CreatePen(Number32 style, Signed_Number32 width, Number32 color);

import stdcall Boolean BeginPath(Byte* device);
import stdcall Boolean CloseFigure(Byte* device);
import stdcall Boolean EndPath(Byte* device);
import stdcall Boolean FillPath(Byte* device);
import stdcall Boolean StrokePath(Byte* device);
import stdcall Boolean StrokeAndFillPath(Byte* device);

import stdcall Number32 SetPixel(Byte* device, Signed_Number32 x, Signed_Number32 y, Number32 color);
import stdcall Boolean MoveToEx(Byte* device, Signed_Number32 x, Signed_Number32 y, Windows_Point* previouse_position);
import stdcall Boolean LineTo(Byte* device, Signed_Number32 x, Signed_Number32 y);
import stdcall Boolean Arc(
	Byte* device,
	Signed_Number32 x1,
	Signed_Number32 y1,
	Signed_Number32 x2,
	Signed_Number32 y2,
	Signed_Number32 x3,
	Signed_Number32 y3,
	Signed_Number32 x4,
	Signed_Number32 y4
);
import stdcall Boolean ArcTo(
	Byte* device,
	Signed_Number32 left,
	Signed_Number32 top,
	Signed_Number32 right,
	Signed_Number32 bottom,
	Signed_Number32 xr1,
	Signed_Number32 yr1,
	Signed_Number32 xr2,
	Signed_Number32 yr2
);

import stdcall Boolean Polygon(Byte* device, Windows_Point* points, Number32 number_of_points);

import stdcall Boolean PolyBezier(Byte* device, Windows_Point* points, Number32 number_of_points);
import stdcall Boolean PolyBezierTo(Byte* device, Windows_Point* points, Number32 number_of_points);


#endif //SYSTEM_WINDOWS_GDI32_INCLUDED