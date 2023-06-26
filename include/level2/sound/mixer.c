#ifndef AUDIO_MIXER_INCLUDED
#define AUDIO_MIXER_INCLUDED


#include <sound.c>
#include <reader.c>


#define MAX_NUMBER_OF_SOUND_READERS 16
//Reader* mixed_readers[MAX_NUMBER_OF_SOUND_READERS];
void**  mixed_readers[MAX_NUMBER_OF_SOUND_READERS];
Number  number_of_mixed_readers = 0;

Number16 sound_mixer_data[SOUND_BUFFER_SIZE / 2];


void play_sound(void* source)
{
	mixed_readers[number_of_mixed_readers] = source;
	++number_of_mixed_readers;
}


static Number mix_sound(
	Byte* source,
	Signed_Number (*read_bytes)(Byte* source, Byte* bytes, Number number_of_bytes),
	Number16* sound_buffer,
	Number size_of_sound_buffer
)
{
	Signed_Number32 sound_mixer_data_temp[SOUND_BUFFER_SIZE / 2];
	Signed_Number16 current_sound_mixer_data[SOUND_BUFFER_SIZE / 2];
	Number          i;
	Number          j;

	clean_bytes(sound_mixer_data_temp, SOUND_BUFFER_SIZE * 2);
	
	for(i = 0; i < number_of_mixed_readers; ++i) {
		clean_bytes(current_sound_mixer_data, size_of_sound_buffer);
		//Number readed_bytes = read_bytes(mixed_readers[i], current_sound_mixer_data, size_of_sound_buffer);
		Number readed_bytes = read_bytes(mixed_readers[i], current_sound_mixer_data, size_of_sound_buffer);

		if(readed_bytes < size_of_sound_buffer) {
			--number_of_mixed_readers;
			for(j = i; j < number_of_mixed_readers; ++j) {
				mixed_readers[j] = mixed_readers[j + 1];
			}
		}

		for(j = 0; j < SOUND_BUFFER_SIZE / 2; ++j) {
			sound_mixer_data_temp[j] += current_sound_mixer_data[j];
		}
	}

	if(number_of_mixed_readers) {
		for(i = 0; i < SOUND_BUFFER_SIZE / 2; ++i) {
			if(sound_mixer_data_temp[i] > 32767) {
				sound_buffer[i] = 32767;
			}
			else if(sound_mixer_data_temp[i] < -32768) {
				sound_buffer[i] = -32768;
			}
			else {
				sound_buffer[i] = sound_mixer_data_temp[i];
			}
		}
	}
	else {
		for(i = 0; i < SOUND_BUFFER_SIZE / 2; ++i) {
			sound_buffer[i] = sound_mixer_data_temp[i];
		}
	}
}

/*
Sound_Out* create_sound_mixer()
{
	number_of_mixed_readers = 0;
	return create_sound_out(0, &mix_sound);
}*/


#endif//AUDIO_MIXER_INCLUDED

/*
#include <audio/WAV.c>
#include <system/keyboard.c>
#include <file.c>


void main()
{
	Sound* sound;

	WAV    wav;
	Reader reader;

	WAV    wav2;
	Reader reader2;

	sound = create_sound_mixer();

	for(;;) {
		if(pressed_key(27))
			break;

		if(pressed_key('N')) {
			initialize_file_reader(&reader, "a.wav");
			read_WAV(&wav, &reader);

			play_sound(&reader);
			Sleep(1000);
		}

		if(pressed_key('M')) {
			initialize_file_reader(&reader2, "a.wav");
			read_WAV(&wav2, &reader2);
			
			play_sound(&reader2);
			Sleep(1000);
		}
	}

	destroy_sound_out(sound);
}*/