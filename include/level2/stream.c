#ifndef STREAM_INCLUDED
#define STREAM_INCLUDED


#include <types.c>


Byte    head_data;
Number  head_size = 0;
Boolean end_of_stream = 0;

void read_next_from_stream()
{
	if(read_character_from_console(get_default_console_reader(), &head_data)) {
		++head_size;
	}
	else {
		head_data = 0;
		end_of_stream = 1;
	}
}

void next()
{
	if(head_size) {
		--head_size;
	}
	else {
		read_next_from_stream();
	}
}

Byte head()
{
	if(!head_size) {
		read_next_from_stream();
	}
	
	if(head_size) {
		return head_data;
	}
	else {
		return 0;
	}
}


#endif//STREAM_INCLUDED

/*
void main()
{
	Boolean is_first;
	
	is_first = 1;
	print("{");
	for(;;) {
		Byte byte;
		
		byte = head();
		
		if(end_of_stream) {
			break;
		}
		
		if(!is_first) {
			print(", ");
		}
		
		print("%d", byte);
		is_first = 0;
		
		next();
	}
	print("};");
}*/