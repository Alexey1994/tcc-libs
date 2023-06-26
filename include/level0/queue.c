#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED


#include <types.c>


typedef struct {
	Byte*  buffer;
	Number buffer_size;
	Number size;
	Number start_index;
}
Queue;


void initialize_queue(Queue* queue, Byte* buffer, Number buffer_size)
{
	queue->buffer = buffer;
	queue->buffer_size = buffer_size;
	queue->size = 0;
	queue->start_index = 0;
}


void add_bytes_in_queue(Queue* queue, Byte* bytes, Number number_of_bytes)
{
	Number end_index;
	
	if(queue->size + number_of_bytes > queue->buffer_size) {
		return;
	}
	
	while(number_of_bytes) {
		end_index = queue->start_index + queue->size;
		
		if(end_index >= queue->buffer_size) {
			end_index -= queue->buffer_size;
		}
		
		queue->buffer[end_index] = *bytes;
			
		++queue->size;
		++bytes;
		--number_of_bytes;
	}
}


void remove_bytes_from_queue(Queue* queue, Byte* bytes, Number number_of_bytes)
{
	if(queue->size < number_of_bytes) {
		return;
	}
	
	while(number_of_bytes) {
		*bytes = queue->buffer[queue->start_index];
		
		++queue->start_index;
		
		if(queue->start_index >= queue->buffer_size) {
			queue->start_index -= queue->buffer_size;
		}
			
		--queue->size;
		++bytes;
		--number_of_bytes;
	}
}


#endif//QUEUE_INCLUDED

/*
Number main(Number number_of_arguments, Byte** arguments)
{
	Queue queue;
	Byte  buffer[5];
	Byte  b;
	
	initialize_queue(&queue, buffer, sizeof(buffer));
	
	b = 1;
	add_bytes_in_queue(&queue, &b, 1);
	
	remove_bytes_from_queue(&queue, &b, 1);
	
	b = 2;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 3;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 4;
	add_bytes_in_queue(&queue, &b, 1);
	
	while(queue.size) {
		remove_bytes_from_queue(&queue, &b, 1);
		print("%d ", b);
	}
	
	print(" (start_index %d)\n", queue.start_index);
	
	
	b = 1;
	add_bytes_in_queue(&queue, &b, 1);
	
	remove_bytes_from_queue(&queue, &b, 1);
	
	b = 2;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 3;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 4;
	add_bytes_in_queue(&queue, &b, 1);
	
	while(queue.size) {
		remove_bytes_from_queue(&queue, &b, 1);
		print("%d ", b);
	}
	
	print(" (start_index %d)\n", queue.start_index);
	
	
	b = 1;
	add_bytes_in_queue(&queue, &b, 1);
	
	remove_bytes_from_queue(&queue, &b, 1);
	
	b = 2;
	add_bytes_in_queue(&queue, &b, 1);
	
	remove_bytes_from_queue(&queue, &b, 1);
	
	b = 3;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 4;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 5;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 6;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 7;
	add_bytes_in_queue(&queue, &b, 1);
	
	while(queue.size) {
		remove_bytes_from_queue(&queue, &b, 1);
		print("%d ", b);
	}
	
	print(" (start_index %d)\n", queue.start_index);
	
	
	b = 1;
	add_bytes_in_queue(&queue, &b, 1);
	
	remove_bytes_from_queue(&queue, &b, 1);
	
	b = 2;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 3;
	add_bytes_in_queue(&queue, &b, 1);
	
	b = 4;
	add_bytes_in_queue(&queue, &b, 1);
	
	while(queue.size) {
		remove_bytes_from_queue(&queue, &b, 1);
		print("%d ", b);
	}
	
	print(" (start_index %d)\n", queue.start_index);
	
	return 0;
}*/