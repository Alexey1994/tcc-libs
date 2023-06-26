#ifndef SYSTEM_CONSOLE_INCLUDED
#define SYSTEM_CONSOLE_INCLUDED


#include <types.c>


typedef enum {
	CONSOLE_BLACK        = 0,
	CONSOLE_BLUE_DARK    = 1,
	CONSOLE_GREEN_DARK   = 2,
	CONSOLE_AZURE_DARK   = 3,
	CONSOLE_RED_DARK     = 4,
	CONSOLE_PINK_DARK    = 5,
	CONSOLE_YELLOW_DARK  = 6,
	CONSOLE_WHITE_DARK   = 7,

	CONSOLE_GRAY         = 8,
	CONSOLE_BLUE         = 9,
	CONSOLE_GREEN        = 10,
	CONSOLE_AZURE        = 11,
	CONSOLE_RED          = 12,
	CONSOLE_PINK         = 13,
	CONSOLE_YELLOW       = 14,
	CONSOLE_WHITE        = 15
}
Console_Color;


Byte* get_default_console_writer();
void  set_console_color(Byte* console, Console_Color text_color, Console_Color background_color);
void  write_in_console(Byte* console, Byte* charachters, Number number_of_charachters);
void  write_character_in_console(Byte* console, Number32 charachter);
Byte* get_default_console_reader();


#ifdef __WIN32__

#include <Windows/kernel32.c>


Byte* get_default_console_writer()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}


Byte* get_default_error_writer()
{
	return GetStdHandle(STD_ERROR_HANDLE);
}


static Number16 get_Windows_color(Console_Color color)
{
	switch(color) {
		case CONSOLE_BLACK: return 0;
		case CONSOLE_BLUE_DARK: return 1;
		case CONSOLE_GREEN_DARK: return 2;
		case CONSOLE_AZURE_DARK: return 3;
		case CONSOLE_RED_DARK: return 4;
		case CONSOLE_PINK_DARK: return 5;
		case CONSOLE_YELLOW_DARK: return 6;
		case CONSOLE_WHITE_DARK: return 7;
		case CONSOLE_GRAY: return 8;
		case CONSOLE_BLUE: return 9;
		case CONSOLE_GREEN: return 10;
		case CONSOLE_AZURE: return 11;
		case CONSOLE_RED: return 12;
		case CONSOLE_PINK: return 13;
		case CONSOLE_YELLOW: return 14;
		case CONSOLE_WHITE: return 15;
	}
}


void set_console_color(Byte* console, Console_Color text_color, Console_Color background_color)
{
	SetConsoleTextAttribute(console, get_Windows_color(text_color) + (get_Windows_color(background_color) << 4));
}


/*void write_in_console(Byte* console, Byte* charachters, Number number_of_charachters)
{
	Number32 bytes_written;
	WriteConsoleA(console, charachters, number_of_charachters, &bytes_written, 0);
}*/


void write_character_in_console(Byte* console, Number32 charachter)
{
	Number32 bytes_written;
	Byte     bytes[16];

	//WriteConsoleW(console, &charachter, 1, &bytes_written, 0);
	bytes_written = WideCharToMultiByte(GetConsoleOutputCP(), 0, &charachter, 1, bytes, sizeof(bytes), 0, 0);
	WriteFile(console, bytes, bytes_written, &bytes_written, 0);
}


Signed_Number write_bytes_in_console(Byte* console, Byte* bytes, Number number_of_bytes)
{
	Number32 bytes_written;

	if(!WriteFile(console, bytes, number_of_bytes, &bytes_written, 0)) {
		return 0;
	}
	
	return bytes_written;
}


Byte* get_default_console_reader()
{
	return GetStdHandle(STD_INPUT_HANDLE);
}

/*
Number32 read_character_from_console_keyboard(Byte* console, Byte* charachter)
{
	Number32 bytes_readed;

	if(!ReadConsoleInputA(console, charachter, 2, &bytes_readed)) {
		return 0;
	}
	
	return bytes_readed;
}*/


Number32 read_character_from_console(Byte* console, Byte* charachter)
{
	Number32 bytes_readed;

	if(!ReadFile(console, charachter, 1, &bytes_readed, 0)) {
		return 0;
	}
	
	return bytes_readed;
}


Signed_Number read_bytes_from_console(Byte* console, Byte* bytes, Number32 number_of_bytes)
{
	Number32 bytes_readed;

	if(!ReadFile(console, bytes, number_of_bytes, &bytes_readed, 0)) {
		return 0;
	}
	
	return bytes_readed;
}


void hide_console_scrollbars()
{
	Console_Screen_Buffer_Info buffer_info;
	GetConsoleScreenBufferInfo(get_default_console_writer(), &buffer_info);
	buffer_info.size.x = buffer_info.window.right + 1;
	buffer_info.size.y = buffer_info.window.bottom + 1;
	SetConsoleScreenBufferSize(get_default_console_writer(), buffer_info.size);
}


Number get_console_cursor_x()
{
	Console_Screen_Buffer_Info buffer_info;
	GetConsoleScreenBufferInfo(get_default_console_writer(), &buffer_info);
	return buffer_info.cursor_position.x;
}


Number get_console_cursor_y()
{
	Console_Screen_Buffer_Info buffer_info;
	GetConsoleScreenBufferInfo(get_default_console_writer(), &buffer_info);
	return buffer_info.cursor_position.y;
}


void set_console_cursor(Number x, Number y)
{
	Console_Coord coord = {x, y};
	SetConsoleCursorPosition(get_default_console_writer(), coord);
}


Number get_console_width()
{
	Console_Screen_Buffer_Info buffer_info;
	GetConsoleScreenBufferInfo(get_default_console_writer(), &buffer_info);
	return buffer_info.window.right + 1;
}


Number get_console_height()
{
	Console_Screen_Buffer_Info buffer_info;
	GetConsoleScreenBufferInfo(get_default_console_writer(), &buffer_info);
	return buffer_info.window.bottom + 1;
}


void clean_console_line(Number line)
{
	Number i;
	
	set_console_color(get_default_console_writer(), CONSOLE_WHITE_DARK, CONSOLE_BLACK);
	set_console_cursor(0, line);
	
	for(i = 0; i < get_console_width() - 1; ++i) {
		write_character_in_console(get_default_console_writer(), ' ');
	}
}


void copy_console_line(Number source_line, Number destination_line)
{
	Byte*     characters;
	Number16* attributes;
	Number    line_size;
	
	line_size = get_console_width() - 1;

	characters = allocate_memory(line_size * sizeof(*characters));
	attributes = allocate_memory(line_size * sizeof(*attributes));
	
	Console_Coord read_coord = {0, source_line};
	Number32 chars_readed;
	ReadConsoleOutputCharacterA(get_default_console_writer(), characters, line_size, read_coord, &chars_readed);
	
	Console_Coord write_coord = {0, destination_line};
	Number32 chars_written;
	WriteConsoleOutputCharacterA(get_default_console_writer(), characters, line_size, write_coord, &chars_written);

	ReadConsoleOutputAttribute(get_default_console_writer(), attributes, line_size, read_coord, &chars_readed);
	WriteConsoleOutputAttribute(get_default_console_writer(), attributes, line_size, write_coord, &chars_written);

	free_memory(characters);
	free_memory(attributes);
}


#endif//__WIN32__


#include <writer.c>


typedef struct {
	Number tail_size;
	Byte   tail[4];

	Byte* source;
	void (*write_character)(Byte* source, Number16 character);
}
Utf8_To_Unicode_Converter;

void initialize_Utf8_To_Unicode_Converter(
	Utf8_To_Unicode_Converter* converter,
	Byte* source,
	void (*write_character)(Byte* source, Number16 character)
)
{
	converter->tail_size       = 0;
	converter->source          = source;
	converter->write_character = write_character;
}

Number32 write_byte_in_utf8_converter(Utf8_To_Unicode_Converter* converter, Byte byte)
{
	converter->tail[converter->tail_size] = byte;
	++converter->tail_size;

	if(converter->tail[0] < 0x80) {
		converter->tail_size = 0;
		converter->write_character(converter->source, converter->tail[0]);
	}
	else if((converter->tail[0] & 0b11110000) && converter->tail_size == 4) {
		converter->tail_size = 0;
		converter->write_character(
			converter->source,
			((converter->tail[0] & 0b00000111) << 18) |
				((converter->tail[1] & 0b00111111) << 12) |
				((converter->tail[2] & 0b00111111) << 6) |
				(converter->tail[3] & 0b00111111)
		);
	}
	else if((converter->tail[0] & 0b11100000) && converter->tail_size == 3) {
		converter->tail_size = 0;
		converter->write_character(
			converter->source,
			((converter->tail[0] & 0b00001111) << 12) |
				((converter->tail[1] & 0b00111111) << 6) |
				(converter->tail[2] & 0b00111111)
		);
	}
	else if((converter->tail[0] & 0b11000000) && converter->tail_size == 2) {
		converter->tail_size = 0;
		converter->write_character(
			converter->source,
			((converter->tail[0] & 0b00011111) << 6) |
				(converter->tail[1] & 0b00111111)
		);
	}

	if(converter->tail_size > 4) {
		converter->tail_size = 0;
	}
}


void write_byte_in_console(Byte* console, Byte byte)
{
	write_bytes_in_console(console, &byte, 1);
}


void print(Byte* parameters, ...)
{
	print_in_source(get_default_console_writer(), &write_byte_in_console, parameters, &parameters + 1);
}


void print_utf8(Byte* parameters, ...)
{
	Utf8_To_Unicode_Converter converter;

	initialize_Utf8_To_Unicode_Converter(&converter, get_default_console_writer(), &write_character_in_console);
	print_in_source(&converter, &write_byte_in_utf8_converter, parameters, &parameters + 1);
}


void print_error(Byte* parameters, ...)
{
	Utf8_To_Unicode_Converter converter;

	initialize_Utf8_To_Unicode_Converter(&converter, get_default_error_writer(), &write_character_in_console);
	print_in_source(&converter, &write_byte_in_utf8_converter, parameters, &parameters + 1);
}


#endif//SYSTEM_CONSOLE_INCLUDED

/*
void main()
{
	Byte* console_output = get_default_console_writer();
	set_console_color(console_output, CONSOLE_WHITE, CONSOLE_BLACK);
	write_in_console(console_output, "Hi", 2);
}*/