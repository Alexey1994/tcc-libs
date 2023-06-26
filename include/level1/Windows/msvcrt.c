#ifndef SYSTEM_WINDOWS_MSVCRT_INCLUDED
#define SYSTEM_WINDOWS_MSVCRT_INCLUDED


#include <types.c>


import cdecl Number _getch();
import cdecl Number _getwch();
import cdecl void _putch(Number character);
import cdecl void _putwch(Number character);


#define PI 3.14159265358979323846


import cdecl Real_Number32 cosf(Real_Number32 angle);
import cdecl Real_Number32 sqrtf(Real_Number32 angle);

import cdecl Real_Number64 cos(Real_Number64 angle);
import cdecl Real_Number64 sin(Real_Number64 angle);


import cdecl void printf(Byte* message, ...);


#endif //SYSTEM_WINDOWS_MSVCRT_INCLUDED