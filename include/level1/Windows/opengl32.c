#ifndef SYSTEM_WINDOWS_OPENGL32_INCLUDED
#define SYSTEM_WINDOWS_OPENGL32_INCLUDED


#include <types.c>


typedef enum {
	GL_FALSE          = 0x0,
	GL_TRUE           = 0x1,
	GL_UNSIGNED_BYTE  = 0x1401,
	GL_SHORT          = 0x1402,
	GL_UNSIGNED_SHORT = 0x1403,
	GL_INT            = 0x1404,
	GL_UNSIGNED_INT   = 0x1405,
	GL_FLOAT          = 0x1406,
	GL_DOUBLE         = 0x140A,
	GL_2_BYTES        = 0x1407,
	GL_3_BYTES        = 0x1408,
	GL_4_BYTES        = 0x1409
}
GL_Data_Type;

typedef enum {
	GL_POINTS         = 0x0000,
	GL_LINES          = 0x0001,
	GL_LINE_LOOP      = 0x0002,
	GL_LINE_STRIP     = 0x0003,
	GL_TRIANGLES      = 0x0004,
	GL_TRIANGLE_STRIP = 0x0005,
	GL_TRIANGLE_FAN   = 0x0006,
	GL_QUADS          = 0x0007,
	GL_QUAD_STRIP     = 0x0008,
	GL_POLYGON        = 0x0009
}
GL_Begin_Mode;

typedef enum {
	GL_MATRIX_MODE = 0x0BA0,
	GL_MODELVIEW   = 0x1700,
	GL_PROJECTION  = 0x1701,
	GL_TEXTURE     = 0x1702
}
GL_Matrix_Mode;

typedef enum {
	GL_DEPTH_BUFFER_BIT = 0x00000100,
	GL_COLOR_BUFFER_BIT = 0x00004000
}
GL_Clear_Mode;

typedef enum {
	GL_RGB  = 0x1907,
	GL_BGR  = 0x80E0,
	GL_RGBA = 0x1908,
	GL_BGRA = 0x80E1,
	GL_ABGR = 0x8000
}
GL_Data_Format;

typedef enum {
	GL_DEPTH_TEST = 0x0B71,
	GL_BLEND      = 0x0BE2,
	GL_NORMALIZE  = 0x0BA1,
	GL_LIGHTING   = 0x0B50
}
GL_Option;

typedef enum {
	GL_NEVER    = 0x0200,
	GL_LESS     = 0x0201,
	GL_EQUAL    = 0x0202,
	GL_LEQUAL   = 0x0203,
	GL_GREATER  = 0x0204,
	GL_NOTEQUAL = 0x0205,
	GL_GEQUAL   = 0x0206,
	GL_ALWAYS   = 0x0207
}
GL_Depth_Func;

typedef enum {
	GL_LIGHT0                   = 0x4000,
	GL_LIGHT1                   = 0x4001,
	GL_LIGHT2                   = 0x4002,
	GL_LIGHT3                   = 0x4003,
	GL_LIGHT4                   = 0x4004,
	GL_LIGHT5                   = 0x4005,
	GL_LIGHT6                   = 0x4006,
	GL_LIGHT7                   = 0x4007
}
GL_Light;

typedef enum {
	GL_AMBIENT                  = 0x1200,
	GL_DIFFUSE                  = 0x1201,
	GL_SPECULAR                 = 0x1202,
	GL_SHININESS                = 0x1601,
	GL_EMISSION                 = 0x1600,
	GL_POSITION                 = 0x1203,
	GL_SPOT_DIRECTION           = 0x1204,
	GL_SPOT_EXPONENT            = 0x1205,
	GL_SPOT_CUTOFF              = 0x1206,
	GL_CONSTANT_ATTENUATION     = 0x1207,
	GL_LINEAR_ATTENUATION       = 0x1208,
	GL_QUADRATIC_ATTENUATION    = 0x1209,
	GL_AMBIENT_AND_DIFFUSE      = 0x1602,
	GL_COLOR_INDEXES            = 0x1603,
	GL_LIGHT_MODEL_TWO_SIDE     = 0x0B52,
	GL_LIGHT_MODEL_LOCAL_VIEWER = 0x0B51,
	GL_LIGHT_MODEL_AMBIENT      = 0x0B53,
	GL_FRONT_AND_BACK           = 0x0408,
	GL_SHADE_MODEL              = 0x0B54,
	GL_FLAT                     = 0x1D00,
	GL_SMOOTH                   = 0x1D01,
	GL_COLOR_MATERIAL           = 0x0B57,
	GL_COLOR_MATERIAL_FACE      = 0x0B55,
	GL_COLOR_MATERIAL_PARAMETER = 0x0B56
}
GL_Light_Parameter_Name;


typedef enum {
	GL_ZERO                     = 0x0,
	GL_ONE                      = 0x1,
	GL_SRC_COLOR                = 0x0300,
	GL_ONE_MINUS_SRC_COLOR      = 0x0301,
	GL_SRC_ALPHA                = 0x0302,
	GL_ONE_MINUS_SRC_ALPHA      = 0x0303,
	GL_DST_ALPHA                = 0x0304,
	GL_ONE_MINUS_DST_ALPHA      = 0x0305,
	GL_DST_COLOR                = 0x0306,
	GL_ONE_MINUS_DST_COLOR      = 0x0307,
	GL_SRC_ALPHA_SATURATE       = 0x0308,
	GL_CONSTANT_COLOR           = 0x8001,
	GL_ONE_MINUS_CONSTANT_COLOR = 0x8002,
	GL_CONSTANT_ALPHA           = 0x8003,
	GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004
}
GL_Blend_Factor;

typedef enum {
	GL_LINEAR                 = 0x2601,
	GL_TEXTURE_ENV            = 0x2300,
	GL_TEXTURE_ENV_MODE       = 0x2200,
	GL_TEXTURE_1D             = 0x0DE0,
	GL_TEXTURE_2D             = 0x0DE1,
	GL_TEXTURE_WRAP_S         = 0x2802,
	GL_TEXTURE_WRAP_T         = 0x2803,
	GL_TEXTURE_MAG_FILTER     = 0x2800,
	GL_TEXTURE_MIN_FILTER     = 0x2801,
	GL_TEXTURE_ENV_COLOR      = 0x2201,
	GL_TEXTURE_GEN_S          = 0x0C60,
	GL_TEXTURE_GEN_T          = 0x0C61,
	GL_TEXTURE_GEN_MODE       = 0x2500,
	GL_TEXTURE_BORDER_COLOR   = 0x1004,
	GL_TEXTURE_WIDTH          = 0x1000,
	GL_TEXTURE_HEIGHT         = 0x1001,
	GL_TEXTURE_BORDER         = 0x1005,
	GL_TEXTURE_COMPONENTS     = 0x1003,
	GL_TEXTURE_RED_SIZE       = 0x805C,
	GL_TEXTURE_GREEN_SIZE     = 0x805D,
	GL_TEXTURE_BLUE_SIZE      = 0x805E,
	GL_TEXTURE_ALPHA_SIZE     = 0x805F,
	GL_TEXTURE_LUMINANCE_SIZE = 0x8060,
	GL_TEXTURE_INTENSITY_SIZE = 0x8061,
	GL_NEAREST_MIPMAP_NEAREST = 0x2700,
	GL_NEAREST_MIPMAP_LINEAR  = 0x2702,
	GL_LINEAR_MIPMAP_NEAREST  = 0x2701,
	GL_LINEAR_MIPMAP_LINEAR   = 0x2703,
	GL_OBJECT_LINEAR          = 0x2401,
	GL_OBJECT_PLANE           = 0x2501,
	GL_EYE_LINEAR             = 0x2400,
	GL_EYE_PLANE              = 0x2502,
	GL_SPHERE_MAP             = 0x2402,
	GL_DECAL                  = 0x2101,
	GL_MODULATE               = 0x2100,
	GL_NEAREST                = 0x2600,
	GL_REPEAT                 = 0x2901,
	GL_CLAMP                  = 0x2900,
	GL_S                      = 0x2000,
	GL_T                      = 0x2001,
	GL_R                      = 0x2002,
	GL_Q                      = 0x2003,
	GL_TEXTURE_GEN_R          = 0x0C62,
	GL_TEXTURE_GEN_Q          = 0x0C63
}
GL_Texture;


import stdcall void glDrawPixels(Number32 width, Number32 height, GL_Data_Format format, GL_Data_Type type, Byte* pixels);
import stdcall void glRasterPos2f(Real_Number32 x, Real_Number32 y);

import stdcall void glEnable(GL_Option option);
import stdcall void glDisable(GL_Option option);

import stdcall void glBlendFunc(GL_Blend_Factor source_factor, GL_Blend_Factor destination_factor);

import stdcall void glDepthFunc(GL_Depth_Func func);

import stdcall void glBegin(GL_Begin_Mode mode);
import stdcall void glEnd();
import stdcall void glColor3f(Real_Number32 red, Real_Number32 green, Real_Number32 blue);
import stdcall void glColor3fv(Real_Number32* color);
import stdcall void glColor4f(Real_Number32 red, Real_Number32 green, Real_Number32 blue, Real_Number32 alpha);
import stdcall void glVertex3f(Real_Number32 x, Real_Number32 y, Real_Number32 z);
import stdcall void glVertex3fv(Real_Number32* vertex);
import stdcall void glNormal3f(Real_Number32 x, Real_Number32 y, Real_Number32 z);
import stdcall void glNormal3fv(Real_Number32* normal);
import stdcall void glTexCoord2f(Real_Number32 s, Real_Number32 t);
import stdcall void glTexCoord2fv(Real_Number32* coord);

import stdcall void glClear(GL_Clear_Mode mode);
import stdcall void glClearColor(Real_Number32 red, Real_Number32 green, Real_Number32 blue, Real_Number32 alpha);

import stdcall void glMatrixMode(GL_Matrix_Mode mode);
import stdcall void glPushMatrix();
import stdcall void glPopMatrix();
import stdcall void glLoadIdentity();
import stdcall void glLoadMatrixf(Real_Number32* matrix);
import stdcall void glOrtho(Real_Number64 left, Real_Number64 right, Real_Number64 bottom, Real_Number64 top, Real_Number64 near, Real_Number64 far);
import stdcall void glFrustum(Real_Number64 left, Real_Number64 right, Real_Number64 bottom, Real_Number64 top, Real_Number64 near, Real_Number64 far);
import stdcall void glMultMatrixf(Real_Number32* matrix);

import stdcall void glTranslatef(Real_Number32 x, Real_Number32 y, Real_Number32 z);
import stdcall void glScalef(Real_Number32 x, Real_Number32 y, Real_Number32 z);
import stdcall void glRotatef(Real_Number32 angle, Real_Number32 x, Real_Number32 y, Real_Number32 z);

import stdcall void glGenTextures(Number32 number_of_textures, Number32* textures);
import stdcall void glDeleteTextures(Number32 number_of_textures, Number32* textures);
import stdcall void glBindTexture(GL_Texture target, Number32 texture);
import stdcall void glTexParameteri(GL_Texture target, GL_Texture name, Signed_Number32 value);
import stdcall void glTexImage2D(
	GL_Texture     target,
	Number32       level,
	GL_Data_Format internal_format,
	Number32       width,
	Number32       height,
	Number32       border,
	GL_Data_Format format,
	GL_Data_Type   type,
	Byte*          pixels
);

import stdcall void glLightfv(GL_Light light, GL_Light_Parameter_Name parameter_name, Real_Number32* values);

import stdcall void glShadeModel(Number32 value);


import stdcall Byte*   wglCreateContext(Byte* context);
import stdcall Boolean wglDeleteContext(Byte* context);
import stdcall void    wglSwapBuffers(Byte* context);
import stdcall Boolean wglMakeCurrent(Byte* device_context, Byte* context);
import stdcall Byte*   wglGetCurrentDC();


#endif //SYSTEM_WINDOWS_OPENGL32_INCLUDED