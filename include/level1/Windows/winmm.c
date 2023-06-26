#ifndef WINDOWS_WINMM_INCLUDED
#define WINDOWS_WINMM_INCLUDED


#include <types.c>


#define CALLBACK_THREAD     0x20000
#define CALLBACK_FUNCTION   0x30000
#define CALLBACK_EVENT      0x50000
#define WHDR_BEGINLOOP      4

typedef enum {
	MM_WOM_OPEN  = 0x3BB,
	MM_WOM_CLOSE = 0x3BC,
	MM_WOM_DONE  = 0x3BD,
}
Sound_Out_Message;

typedef enum {
	WAVERR_STILLPLAYING = 33
}
Sound_Out_Unprepare_Header_Error_Message;

typedef enum {
	MM_WIM_OPEN  = 0x3BE,
	MM_WIM_CLOSE = 0x3BF,
	MM_WIM_DATA  = 0x3C0,
}
Sound_In_Message;

#define PCM_WAVE_FORMAT     1

typedef struct {
	Number16 format;
	Number16 number_of_channels;
	Number32 samples_per_seconds;
	Number32 bytes_per_seconds;
	Number16 block_align;
	Number16 bits_per_sample;
	Number16 size_of_appended_information;
}
Sound_Format;

typedef struct Windows_Sound_Buffer {
	Byte*                        data;
	Number32                     buffer_length;
	Number32                     bytes_recorded;
	Byte*                        user;
	Number32                     flags;
	Number32                     loops;
	struct Windows_Sound_Buffer* next;
	Byte*                        reserved;
}
Sound_Buffer;


import stdcall Number32 waveOutOpen(
	Byte**        sound_device,
	Number32      device_ID,
	Sound_Format* format,
	void        (*on_buffer_end)(Byte *sound_device, Byte *message, Byte *arguments, Byte *parameter1, Byte *parameter2),
	Byte*         arguments,
	Number32      flags
);

import stdcall Number32 waveOutClose(Byte* sound_device);

import stdcall Number32 waveOutReset(Byte* sound_device);

import stdcall Number32 waveOutPrepareHeader(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);

import stdcall Number32 waveOutUnprepareHeader(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);

import stdcall Number32 waveOutWrite(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);


import stdcall Number32 waveInOpen(
	Byte**        sound_device,
	Number32      device_ID,
	Sound_Format* format,
	void        (*on_buffer_end)(Byte *sound_device, Byte *message, Byte *arguments, Byte *parameter1, Byte *parameter2),
	Byte*         arguments,
	Number32      flags
);

import stdcall Number32 waveInClose(Byte* sound_device);

import stdcall Number32 waveInPrepareHeader(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);

import stdcall Number32 waveInUnprepareHeader(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);

import stdcall Number32 waveInAddBuffer(
	Byte*         sound_device,
	Sound_Buffer* buffer,
	Number32      size_of_struct_buffer
);

import stdcall Number32 waveInStart(Byte* sound_device);
import stdcall Number32 waveInStop(Byte* sound_device);


#endif //WINDOWS_WINMM_INCLUDED