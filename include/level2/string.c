#ifndef UTF_8_INCLUDED
#define UTF_8_INCLUDED


#include <types.c>
#include <heap.c>


Number32 read_UTF8_character(Number8** string)
{
	Number8  current_byte;
	Number   number_of_bytes;
	Number32 result;
	Number   i;

	current_byte = **string;
	++*string;

	if(!(current_byte & 0b10000000))
		return current_byte;

	if((current_byte & 0b11110000) == 0b11110000) {
		number_of_bytes = 4;
		result = (current_byte & 0b00001111) << 18;
	}
	else if((current_byte & 0b11100000) == 0b11100000) {
		number_of_bytes = 3;
		result = (current_byte & 0b00011111) << 12;
	}
	else if((current_byte & 0b11000000) == 0b11000000) {
		number_of_bytes = 2;
		result = (current_byte & 0b00111111) << 6;
	}
	else
		goto error;

	for(i = 0; i < number_of_bytes - 1; ++i) {
		current_byte = **string;
		++*string;
		result |= (current_byte & 0b00111111) << ((number_of_bytes - 2 - i) * 6);
	}

	return result;

	error: {
		return 1;
	}
}


void write_UTF8_character(Byte** string, Number32 character)
{
	if(character < 0x80) {
		**string = character;
		++*string;
	}
	else if(character < 0x800) {
		**string = 0b11000000 | ((character >> 6) & 0b00011111);
		++*string;

		**string = 0b10000000 | ((character) & 0b00111111);
		++*string;
	}
	else if(character < 0x10000) {
		**string = 0b11100000 | ((character >> 12) & 0b00001111);
		++*string;

		**string = 0b10000000 | ((character >> 6) & 0b00111111);
		++*string;

		**string = 0b10000000 | ((character) & 0b00111111);
		++*string;
	}
	else if(character < 0x11000) {
		**string = 0b11110000 | ((character >> 15) & 0b00000111);
		++*string;

		**string = 0b10000000 | ((character >> 12) & 0b00111111);
		++*string;

		**string = 0b10000000 | ((character >> 6) & 0b00111111);
		++*string;

		**string = 0b10000000 | ((character) & 0b00111111);
		++*string;
	}
}

/*
Signed_Number compare_UTF_8_strings(Byte* string1, Byte* string2)
{
	Signed_Number character1;
	Signed_Number character2;
	Signed_Number result;

	for(;;) {
		character1 = read_UTF8_character(&string1);
		character2 = read_UTF8_character(&string2);
		result = character1 - character2;

		if(result || !(character1 && character2))
			return result;
	}
}


Signed_Number compare_long_string_and_UTF_8_string(Number16* string1, Number number_of_characters_in_string1, Byte* string2)
{
	Signed_Number character1;
	Signed_Number character2;
	Signed_Number result;

	for(; number_of_characters_in_string1; --number_of_characters_in_string1, ++string1) {
		character1 = *string1;
		character2 = read_UTF8_character(&string2);
		result = character1 - character2;

		if(result || !(number_of_characters_in_string1 && character2))
			return result;
	}

	if(number_of_characters_in_string1)
		return *string1;
	else {
		character2 = read_UTF8_character(&string2);
		return -character2;
	}
}


Signed_Number compare_long_strings(Number16* string1, Number number_of_characters_in_string1, Number16* string2, Number number_of_characters_in_string2)
{
	Signed_Number character1;
	Signed_Number character2;
	Signed_Number result;

	for(; number_of_characters_in_string1 && number_of_characters_in_string2; --number_of_characters_in_string1, ++string1, --number_of_characters_in_string2, ++string2) {
		result = *string1 - *string2;

		if(result || !(number_of_characters_in_string1 && number_of_characters_in_string2))
			return result;
	}

	if(number_of_characters_in_string1)
		return *string1;
	else if(number_of_characters_in_string2) {
		character2 = *string2;
		return -character2;
	}
	else
		return 0;
}*/


Number16* convert_utf8_to_unicode(Byte* utf8)
{
	Number    size;
	Number    index;
	Number16* unicode;

	for(size = 0; utf8[size]; ++size);
	++size;

	unicode = allocate_memory(size * sizeof(Number16));

	for(index = 0; ; ++index) {
		unicode[index] = read_UTF8_character(&utf8);

		if(!unicode[index]) {
			break;
		}
	}

	return unicode;
}


Byte* convert_unicode_to_utf8(Number16* unicode)
{
	Number size;
	Number index;
	Byte*  utf8;
	Byte*  utf8_ref;

	for(size = 0; unicode[size]; ++size);
	++size;

	utf8 = allocate_memory(size * 4);
	utf8_ref = utf8;

	for(index = 0; ; ++index) {
		write_UTF8_character(&utf8_ref, unicode[index]);

		if(!unicode[index]) {
			break;
		}
	}

	return utf8;
}

/*
#ifdef __WIN32__

Byte* get_utf8_argument(Byte* argument)
{
	Number    argument_size;
	Number16* unicode_string;
	Number    unicode_string_size;
	Number    index;
	Byte*     utf8_string;

	for(argument_size = 0; argument[argument_size]; ++argument_size);
	++argument_size;

	unicode_string_size = argument_size * 2;
	unicode_string = allocate_memory(argument_size * 2);

	MultiByteToWideChar(CP_ACP, 0, argument, argument_size - 1, unicode_string, unicode_string_size);
	unicode_string[unicode_string_size / 2 - 1] = '\0';
	utf8_string = convert_unicode_to_utf8(unicode_string);
	free_memory(unicode_string);

	return utf8_string;
}

#endif
*/

#endif//UTF_8_INCLUDED

/*
void main()
{
	printf("%d\n", compare_UTF_8_strings("aa", "aa"));
	printf("%d\n", compare_long_string_and_UTF_8_string(L"ab", 2, "aa"));
	printf("%d\n", compare_long_strings(L"ab", 2, L"ac", 2));
}*/