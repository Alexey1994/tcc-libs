#ifndef READER_INCLUDED
#define READER_INCLUDED


#include <types.c>
#include <queue.c>


typedef struct {
	Byte* source;
	Signed_Number (*read_bytes)(Byte* source, Byte* bytes, Number number_of_bytes);
	
	Boolean end_of_data;
	Queue   queue;
}
Reader;


void initialize_reader(
	Reader*         reader,
	Byte*           source,
	Signed_Number (*read_bytes)(Byte* source, Byte* bytes, Number number_of_bytes),
	Byte*           buffer,
	Number          buffer_size
)
{
	reader->source          = source;
	reader->read_bytes      = read_bytes;
	reader->end_of_data     = 0;
	initialize_queue(&reader->queue, buffer, buffer_size);
}


void read_next_byte(Reader* reader)
{
	Byte          bytes;
	Signed_Number bytes_readed;
	
	if(reader->queue.size) {
		remove_bytes_from_queue(&reader->queue, &bytes, sizeof(bytes));
	}
	else {
		if(reader->end_of_data) {
			return;
		}
		
		bytes_readed = reader->read_bytes(reader->source, &bytes, sizeof(bytes));
		
		if(bytes_readed < sizeof(bytes)) {
			reader->end_of_data = 1;
		}
		
		if(bytes_readed < 0) {
			reader->queue.size = 0;
		}
		else {
			add_bytes_in_queue(&reader->queue, &bytes, sizeof(bytes));
		}
	}
}


Byte get_reader_byte(Reader* reader)
{
	if(!reader->queue.size) {
		read_next_byte(reader);
	}

	return reader->queue.buffer[reader->queue.start_index];
}


Boolean end_of_reader(Reader* reader)
{
	if(reader->queue.size) {
		return 0;
	}

	return reader->end_of_data;
}


Boolean read_if(Reader* reader, Byte* null_terminated_bytes)
{
	Number accumulated_index;
	Number accumulated_size;
	
	accumulated_index = reader->queue.start_index;
	accumulated_size = 0;
	
	while(*null_terminated_bytes) {
		if(get_reader_byte(reader) != *null_terminated_bytes) {
			reader->queue.start_index = accumulated_index;
			reader->queue.size += accumulated_size;
			return 0;
		}
		
		read_next_byte(reader);
		
		++null_terminated_bytes;
		++accumulated_size;
	}
	
	return 1;
}


Boolean read_if_bytes(Reader* reader, Byte* bytes, Number number_of_bytes)
{
	Number accumulated_index;
	Number accumulated_size;
	
	accumulated_index = reader->queue.start_index;
	accumulated_size = 0;
	
	while(number_of_bytes) {
		if(get_reader_byte(reader) != *bytes) {
			reader->queue.start_index = accumulated_index;
			reader->queue.size += accumulated_size;
			return 0;
		}
		
		read_next_byte(reader);
		
		++bytes;
		--number_of_bytes;
		++accumulated_size;
	}
	
	return 1;
}


Signed_Number read_bytes(Reader* reader, Byte* bytes, Number number_of_bytes)
{
	Signed_Number bytes_readed;

	bytes_readed = 0;

	while(number_of_bytes) {
		*bytes = get_reader_byte(reader);

		++bytes;
		++bytes_readed;
		--number_of_bytes;
		read_next_byte(reader);
	}

	return bytes_readed;
}


Number8 read_binary_Number8(Reader* reader)
{
	Number8 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Number16 read_binary_Number16(Reader* reader)
{
	Number16 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Number32 read_binary_Number32(Reader* reader)
{
	Number32 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Number64 read_binary_Number64(Reader* reader)
{
	Number64 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Signed_Number8 read_binary_Signed_Number8 (Reader* reader)
{
	Signed_Number8 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Signed_Number16 read_binary_Signed_Number16 (Reader* reader)
{
	Signed_Number16 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Signed_Number32 read_binary_Signed_Number32 (Reader* reader)
{
	Signed_Number32 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Real_Number32 read_binary_Real_Number32 (Reader* reader)
{
	Real_Number32 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Real_Number64 read_binary_Real_Number64 (Reader* reader)
{
	Real_Number64 number = 0;
	read_bytes(reader, &number, sizeof(number));
	return number;
}


Boolean is_number_character(char character)
{
	return character >= '0' && character <= '9';
}


Number read_Number(Reader* reader)
{
	Number number;

	number = 0;

	while(!end_of_reader(reader) && is_number_character(get_reader_byte(reader))) {
		number = number*10 + get_reader_byte(reader) - '0';
		read_next_byte(reader);
	}

	return number;
}


Signed_Number read_Signed_Number(Reader* reader)
{
	if(get_reader_byte(reader) == '-') {
		read_next_byte(reader);
		return -(Signed_Number)read_Number(reader);
	}

	return read_Number(reader);
}


Real_Number32 read_Real_Number(Reader* reader)
{
	Boolean        is_negative;
	Real_Number32 decimal;
	Real_Number32 fractional;
	Real_Number32 basis;
	
	is_negative = get_reader_byte(reader) == '-';
	
	if(is_negative) {
		read_next_byte(reader);
	}

	decimal = read_Number(reader);

	if(get_reader_byte(reader) != '.') {
		return decimal;
	}

	read_next_byte(reader);
	
	fractional = 0.0f;
	basis = 0.1f;
	while(!end_of_reader(reader) && is_number_character(get_reader_byte(reader))) {
		fractional += (Real_Number32)(get_reader_byte(reader) - '0') * basis;
		basis /= 10.0f;
		read_next_byte(reader);
	}

	if(is_negative) {
		return -(decimal + fractional);
	}
	else {
		return decimal + fractional;
	}
}


Number32 read_UTF_8_character(Reader* reader)
{
	Byte     current_byte;
	Number   number_of_bytes;
	Number32 character;
	Number   i;

	current_byte = get_reader_byte(reader);
	read_next_byte(reader);

	if(!(current_byte & 0b10000000))
		return current_byte;

	if((current_byte & 0b11110000) == 0b11110000) {
		number_of_bytes = 4;
		character = (current_byte & 0b00001111) << 18;
	}
	else if((current_byte & 0b11100000) == 0b11100000) {
		number_of_bytes = 3;
		character = (current_byte & 0b00011111) << 12;
	}
	else if((current_byte & 0b11000000) == 0b11000000) {
		number_of_bytes = 2;
		character = (current_byte & 0b00111111) << 6;
	}
	else
		goto error;

	for(i = 0; i < number_of_bytes - 1; ++i) {
		current_byte = get_reader_byte(reader);
		read_next_byte(reader);
		character |= (current_byte & 0b00111111) << ((number_of_bytes - 2 - i) * 6);
	}

	return character;

	error: {
		return 1;
	}
}


Boolean is_space_character(char character)
{
	return character == ' ' || character == '\r' || character == '\n' || character == '\t';
}


void read_spaces(Reader* reader)
{
	while(!end_of_reader(reader) && is_space_character(get_reader_byte(reader))) {
		read_next_byte(reader);
	}
}


Boolean is_line_break_character(char character)
{
	return character == '\r' || character == '\n';
}


void read_line(Reader* reader)
{
	while(!end_of_reader(reader) && !is_line_break_character(get_reader_byte(reader))) {
		read_next_byte(reader);
	}

	if(get_reader_byte(reader) == '\r') {
		read_next_byte(reader);
	}

	if(get_reader_byte(reader) == '\n') {
		read_next_byte(reader);
	}
}


Byte read_character_from_bytes(Byte** source)
{
	Number character;

	character = **source;
	
	if(character) {
		++*source;
	}
	
	return character;
}


Signed_Number read_from_bytes(Byte** source, Byte* buffer, Number buffer_size)
{
	Signed_Number bytes_readed;
	
	bytes_readed = 0;
	
	while(buffer_size) {
		*buffer = read_character_from_bytes(source);
		
		if(!*buffer) {
			break;
		}
		
		++bytes_readed;
		++buffer;
		--buffer_size;
	}
	
	return bytes_readed;
}


#endif//READER_INCLUDED

/*
Number main(Number number_of_bytes, Byte** bytes)
{
	Reader reader;
	Byte   buffer[256];
	Byte*  s;
	
	s = "hello5.3 my friend";
	initialize_reader(&reader, &s, &read_from_bytes, buffer, sizeof(buffer));
	
	if(!read_if(&reader, "hellou")) {
		
	}
	
	if(!read_if(&reader, "hello")) {
		
	}
	
	printf("%f\n", read_Real_Number(&reader));
	
	while(!end_of_reader(&reader)) {
		print("%c", get_reader_byte(&reader));
		read_next_byte(&reader);
	}
	
	return 0;
}*/