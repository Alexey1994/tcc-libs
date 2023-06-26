#ifndef INSERTION_SORT_INCLUDED
#define INSERTION_SORT_INCLUDED


#include <memory.c>


void insertion_sort(
	Byte*  array,
	Number element_size,
	Number number_of_elements,
	Signed_Number (*compare)(Byte* element1, Byte* element2)
)
{
	Number i;

	for(i = 0; i < number_of_elements; ++i) {
		Byte* target_element = array + i * element_size;
		Byte* previous_element = target_element - element_size;

		while(target_element != array && compare(target_element, previous_element) < 0) {
			swap_bytes(target_element, previous_element, element_size);
			target_element = previous_element;
			previous_element = target_element - element_size;
		}
	}
}


#endif//INSERTION_SORT_INCLUDED

/*
Signed_Number compare(Number8* number1, Number8* number2)
{
	return *number1 - *number2;
}


void main()
{
	Number i;
	Byte bytes[5] = {5, 4, 2, 3, 1};

	insertion_sort(bytes, 1, 5, &compare);
	print_bytes(bytes, 5);
}*/