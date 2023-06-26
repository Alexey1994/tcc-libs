#ifndef STACK_DATA_STRUCTURES_INCLUDED
#define STACK_DATA_STRUCTURES_INCLUDED


#include <heap.c>
#include <memory.c>


typedef struct {
	Number size;
	Number reserve;
	Byte*  data;
}
Stack;


void initialize_stack(Stack* stack, Number reserve)
{
	stack->size    = 0;
	stack->reserve = reserve;
	stack->data    = allocate_memory(stack->reserve);
}


void deinitialize_stack(Stack* stack)
{
	free_memory(stack->data);
}


Byte* reserve_bytes_in_stack(Stack* stack, Number number_of_bytes)
{
	Byte* bytes;

	while(stack->reserve - stack->size < number_of_bytes) {
		stack->reserve *= 2;
		stack->data = reallocate_memory(stack->data, stack->reserve);
	}

	bytes = stack->data + stack->size;

	return bytes;
}


Byte* allocate_bytes_in_stack(Stack* stack, Number number_of_bytes)
{
	Byte* bytes;

	bytes = reserve_bytes_in_stack(stack, number_of_bytes);
	stack->size += number_of_bytes;

	return bytes;
}


void add_bytes_in_stack(Stack* stack, Byte* bytes, Number number_of_bytes)
{
	copy_bytes(allocate_bytes_in_stack(stack, number_of_bytes), bytes, number_of_bytes);
}


void write_character_in_stack(Stack* stack, Number character)
{
	add_bytes_in_stack(stack, &character, 1);
}


Number remove_bytes_from_stack(Stack* stack, Byte* bytes, Number number_of_bytes)
{
	if(number_of_bytes > stack->size)
		number_of_bytes = stack->size;

	stack->size -= number_of_bytes;
	copy_bytes(bytes, stack->data + stack->size, number_of_bytes);

	return number_of_bytes;
}


void clean_stack(Stack* stack)
{
	stack->size = 0;
}


#endif//STACK_DATA_STRUCTURES_INCLUDED

/*
void main()
{
	Stack stack;
	Byte  data[256];

	initialize_stack(&stack, 1);
	add_bytes_in_stack(&stack, "Hi", 3);
	printf("%d bytes\n", remove_bytes_from_stack(&stack, data, 256));
	printf("%s\n", data);
	deinitialize_stack(&stack);
}*/