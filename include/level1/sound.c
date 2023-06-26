#ifndef SOUND_INCLUDED
#define SOUND_INCLUDED


#include <types.c>


typedef struct {
	Signed_Number16 left;
	Signed_Number16 right;	
}
Sound_Data;


#ifdef __WIN32__

#include <Windows/winmm.c>
#include <heap.c>
#include <memory.c>


#define SOUND_BUFFER_SIZE 8192//8820 // in bytes


typedef struct {
	Byte*         device;
	Sound_Buffer  buffer1;
	Sound_Buffer  buffer2;
	Number        current_buffer_index;
	Number        number_of_loaded_buffers;
}
Sound_Out;


static stdcall void sound_out_message_handler(Byte* sound_device, Number32 message, Sound_Out* sound_out, Number32* parameter1, Number32* parameter2)
{
	switch(message) {
		case MM_WOM_OPEN: {
			break;
		}
		
		case MM_WOM_DONE: {
			--sound_out->number_of_loaded_buffers;
			break;
		}
		
		case MM_WOM_CLOSE: {
			break;
		}
	}
}


Boolean initialize_sound_out(Sound_Out* sound_out)
{
	Sound_Format sound_format;
	
	sound_out->current_buffer_index     = 0;
	sound_out->number_of_loaded_buffers = 0;
	
	sound_out->buffer1.buffer_length  = SOUND_BUFFER_SIZE;
	sound_out->buffer1.bytes_recorded = 0;
	sound_out->buffer1.flags          = 0;
	sound_out->buffer1.loops          = 0;

	sound_out->buffer2.buffer_length  = SOUND_BUFFER_SIZE;
	sound_out->buffer2.bytes_recorded = 0;
	sound_out->buffer2.flags          = 0;
	sound_out->buffer2.loops          = 0;
	
	sound_format.format                       = PCM_WAVE_FORMAT;
	sound_format.number_of_channels           = 2;
	sound_format.samples_per_seconds          = 44100;
	sound_format.bits_per_sample              = 16;
	sound_format.block_align                  = sound_format.bits_per_sample / 8 * sound_format.number_of_channels;
	sound_format.bytes_per_seconds            = sound_format.samples_per_seconds * sound_format.block_align;
	sound_format.size_of_appended_information = 0;
	
	if(waveOutOpen(&sound_out->device, -1, &sound_format, &sound_out_message_handler, sound_out, CALLBACK_FUNCTION)){
		goto error;
	}
	
	if(waveOutPrepareHeader(sound_out->device, &sound_out->buffer1, sizeof(Sound_Buffer))) {
		waveOutClose(sound_out->device);
		goto error;
	}
	
	if(waveOutPrepareHeader(sound_out->device, &sound_out->buffer2, sizeof(Sound_Buffer))) {
		waveOutUnprepareHeader(sound_out->device, &sound_out->buffer1, sizeof(Sound_Buffer));
		waveOutClose(sound_out->device);
		goto error;
	}
	
	return 1;
	
	error: {
		return 0;
	}
}


Number write_in_sound(Sound_Out* sound_out, Byte buffer[SOUND_BUFFER_SIZE])
{
	while(sound_out->number_of_loaded_buffers >= 2) {
		Sleep(1);
	}
	
	++sound_out->number_of_loaded_buffers;
	
	if(sound_out->current_buffer_index) {
		sound_out->buffer2.data = buffer;
		waveOutWrite(sound_out->device, &sound_out->buffer2, SOUND_BUFFER_SIZE);
	}
	else {
		sound_out->buffer1.data = buffer;
		waveOutWrite(sound_out->device, &sound_out->buffer1, SOUND_BUFFER_SIZE);
	}

	sound_out->current_buffer_index = !sound_out->current_buffer_index;
}


void deinitialize_sound_out(Sound_Out* sound_out)
{
	waveOutReset(sound_out->device);
	waveOutUnprepareHeader(sound_out->device, &sound_out->buffer1, sizeof(Sound_Buffer));
	waveOutUnprepareHeader(sound_out->device, &sound_out->buffer2, sizeof(Sound_Buffer));
	waveOutClose(sound_out->device);
}


typedef struct {
	Byte*         device;
	Sound_Buffer  buffer1;
	Byte          buffer1_data[SOUND_BUFFER_SIZE];
	Sound_Buffer  buffer2;
	Byte          buffer2_data[SOUND_BUFFER_SIZE];
	Number        current_buffer_index;
	Number        number_of_loaded_buffers;
}
Sound_In;


static stdcall void sound_in_message_handler(Byte* sound_device, Number32 message, Sound_In* sound_in, Number32* parameter1, Number32* parameter2)
{
	switch(message) {
		case MM_WIM_OPEN: {
			break;
		}

		case MM_WIM_DATA: {
			while(sound_in->number_of_loaded_buffers >= 2) {
				Sleep(1);
			}
			
			if(sound_in->current_buffer_index) {
				waveInAddBuffer(sound_in->device, &sound_in->buffer2, sizeof(Sound_Buffer));
			}
			else {
				waveInAddBuffer(sound_in->device, &sound_in->buffer1, sizeof(Sound_Buffer));
			}

			sound_in->current_buffer_index = !sound_in->current_buffer_index;
			
			++sound_in->number_of_loaded_buffers;
			
			break;
		}

		case MM_WIM_CLOSE: {
			break;
		}
	}
}


Boolean initialize_sound_in(Sound_In* sound_in)
{
	Sound_Format sound_format;
	
	sound_in->current_buffer_index     = 0;
	sound_in->number_of_loaded_buffers = 0;
	
	sound_in->buffer1.data           = sound_in->buffer1_data;
	sound_in->buffer1.buffer_length  = sizeof(sound_in->buffer1_data);
	sound_in->buffer1.bytes_recorded = 0;
	sound_in->buffer1.flags          = 0;
	sound_in->buffer1.loops          = 0;

	sound_in->buffer2.data           = sound_in->buffer2_data;
	sound_in->buffer2.buffer_length  = sizeof(sound_in->buffer2_data);
	sound_in->buffer2.bytes_recorded = 0;
	sound_in->buffer2.flags          = 0;
	sound_in->buffer2.loops          = 0;
	
	sound_format.format                       = PCM_WAVE_FORMAT;
	sound_format.number_of_channels           = 2;
	sound_format.samples_per_seconds          = 44100;
	sound_format.bits_per_sample              = 16;
	sound_format.block_align                  = sound_format.bits_per_sample / 8 * sound_format.number_of_channels;
	sound_format.bytes_per_seconds            = sound_format.samples_per_seconds * sound_format.block_align;
	sound_format.size_of_appended_information = 0;
	
	if(waveInOpen(&sound_in->device, -1, &sound_format, &sound_in_message_handler, sound_in, CALLBACK_FUNCTION)){
		goto error;
	}
	
	if(waveInPrepareHeader(sound_in->device, &sound_in->buffer1, sizeof(Sound_Buffer))) {
		waveInClose(sound_in->device);
		goto error;
	}
	
	if(waveInPrepareHeader(sound_in->device, &sound_in->buffer2, sizeof(Sound_Buffer))) {
		waveInUnprepareHeader(sound_in->device, &sound_in->buffer1, sizeof(Sound_Buffer));
		waveInClose(sound_in->device);
		goto error;
	}
	
	waveInAddBuffer(sound_in->device, &sound_in->buffer1, sizeof(Sound_Buffer));
	waveInAddBuffer(sound_in->device, &sound_in->buffer2, sizeof(Sound_Buffer));
	
	waveInStart(sound_in->device);
	
	return 1;
	
	error: {
		return 0;
	}
}


Byte* read_from_sound_in(Sound_In* sound_in)
{
	while(!sound_in->number_of_loaded_buffers) {
		Sleep(1);
	}
	
	if(sound_in->current_buffer_index) {
		return sound_in->buffer1_data;
	}
	else {
		return sound_in->buffer2_data;
	}
}


#endif//__WIN32__


#endif//SOUND_INCLUDED