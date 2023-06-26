#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED


// unsigned number
typedef unsigned char          Number8;  // [0, 255]
typedef unsigned short int     Number16; // [0, 65 535]
typedef unsigned long int      Number32; // [0, 4 294 967 296]
typedef unsigned long long int Number64; // [0, 18 446 744 073 709 551 616]
typedef Number64               Number;

typedef char                   Signed_Number8;  // [-127, 127]
typedef short int              Signed_Number16; // [-32 767, 32 767]
typedef long int               Signed_Number32; // [-2 147 483 648, 2 147 483 648]
typedef long long int          Signed_Number64; // [-9 223 372 036 854 775 808, 9 223 372 036 854 775 808]
typedef Signed_Number64        Signed_Number;

typedef float                  Real_Number32;
typedef double                 Real_Number64;
typedef long double            Real_Number80;
typedef Real_Number64          Real_Number;

typedef Number8                Byte;
typedef Number                 Boolean;


#define stdcall __attribute__((__stdcall__))
#define cdecl   __attribute__((__cdecl__))
#define import  __attribute__((dllimport))
#define export  __attribute__((dllexport))


#pragma pack(push, 1) //no align for structs


//#include <log.c>


void memset(Byte* bytes, Number fill, Number size)
{
	Number system_size;
	Number remind_size;

	system_size = size / sizeof(Number);
	remind_size = size % sizeof(Number);

	while(system_size) {
		*((Number*)bytes) = fill;

		--system_size;
		bytes += sizeof(Number);
	}

	while(remind_size) {
		*bytes = 0;

		--remind_size;
		++bytes;
	}
}


typedef int Wtype;
typedef unsigned int UWtype;
typedef unsigned int USItype;
typedef long long DWtype;
typedef unsigned long long UDWtype;

struct DWstruct {
	Wtype low, high;
};

typedef union
{
	struct DWstruct s;
	DWtype ll;
} DWunion;

typedef long double XFtype;

union float_long {
	float f;
	unsigned int l;
};

union double_long {
	double d;
#if 1
	struct {
		unsigned int lower;
		int upper;
	} l;
#else
	struct {
		int upper;
		unsigned int lower;
	} l;
#endif
	long long ll;
};

#define EXCESS		126

#define HIDDEN		(1 << 23)
#define EXP(fp)		(((fp) >> 23) & 0xFF)
#define MANT(fp)	(((fp) & 0x7FFFFF) | HIDDEN)

#define EXCESSD		1022

#define HIDDEND		(1 << 20)

#define EXPD(fp)	(((fp.l.upper) >> 20) & 0x7FF)
#define MANTD(fp)	(((((fp.l.upper) & 0xFFFFF) | HIDDEND) << 10) | \
				(fp.l.lower >> 22))
#define HIDDEND_LL	((long long)1 << 52)
#define MANTD_LL(fp)	((fp.ll & (HIDDEND_LL-1)) | HIDDEND_LL)

// XXX: fix tcc's code generator to do this instead
float __floatundisf(unsigned long long a)
{
	DWunion uu; 
	XFtype r;

	uu.ll = a;
	if (uu.s.high >= 0) {
		return (float)uu.ll;
	}
	else {
		r = (XFtype)uu.ll;
		r += 18446744073709551616.0;
		return (float)r;
	}
}

double __floatundidf(unsigned long long a)
{
	DWunion uu; 
	XFtype r;

	uu.ll = a;
	if (uu.s.high >= 0) {
		return (double)uu.ll;
	} else {
		r = (XFtype)uu.ll;
		r += 18446744073709551616.0;
		return (double)r;
	}
}

unsigned long long __fixunssfdi (float a1)
{
	register union float_long fl1;
	register int exp;
	register unsigned long l;

	fl1.f = a1;

	if (fl1.l == 0)
	return (0);

	exp = EXP (fl1.l) - EXCESS - 24;

	l = MANT(fl1.l);
	if (exp >= 41)
		return (unsigned long long)-1;
	else if (exp >= 0)
		return (unsigned long long)l << exp;
	else if (exp >= -23)
		return l >> -exp;
	else
		return 0;
}

unsigned long long __fixunsdfdi (double a1)
{
	register union double_long dl1;
	register int exp;
	register unsigned long long l;

	dl1.d = a1;

	if (dl1.ll == 0)
		return (0);

	exp = EXPD (dl1) - EXCESSD - 53;

	l = MANTD_LL(dl1);

	if (exp >= 12)
		return (unsigned long long)-1;
	else if (exp >= 0)
		return l << exp;
	else if (exp >= -52)
		return l >> -exp;
	else
		return 0;
}


//#include <Windows/msvcrt.c>
#include <console.c>


#include <heap.c>
#include <string.c>
#include <Windows/shell32.c>


Number main(Number number_of_arguments, Byte** arguments);


void _start()
{
	Number          i;
	Number16**      arguments;
	Signed_Number32 number_of_arguments;
	Byte**          utf8_arguments;
	
	arguments = CommandLineToArgvW(GetCommandLineW(), &number_of_arguments);
	utf8_arguments = allocate_memory(number_of_arguments * sizeof(Byte*));
	
	for(i = 0; i < number_of_arguments; ++i) {
		utf8_arguments[i] = convert_unicode_to_utf8(arguments[i]);
	}
	
	ExitProcess(main(number_of_arguments, utf8_arguments));
	
	/*
	Number16* command_line;
	Byte*     utf8_command_line;
	
	command_line = GetCommandLineW();
	utf8_command_line = convert_unicode_to_utf8(command_line);
	print_utf8(utf8_command_line);
	
	Byte* t = "ept";
	main(1, &t);
	free_memory(utf8_command_line);*/
}

void _runmain()
{
	Number          i;
	Number16**      arguments;
	Signed_Number32 number_of_arguments;
	Byte**          utf8_arguments;
	
	arguments = CommandLineToArgvW(GetCommandLineW(), &number_of_arguments);
	utf8_arguments = allocate_memory(number_of_arguments * sizeof(Byte*));
	
	for(i = 0; i < number_of_arguments; ++i) {
		utf8_arguments[i] = convert_unicode_to_utf8(arguments[i]);
	}
	
	number_of_arguments -= 24;
	ExitProcess(main(number_of_arguments, utf8_arguments + 24));
}


#endif//TYPES_INCLUDED