#ifndef THREAD_INCLUDED
#define THREAD_INCLUDED


#include <types.c>


Number run_thread   (void (*thread_function)(), Byte* argument);
void   sleep_thread (Number milliseconds);


#ifdef __WIN32__

#include <Windows/kernel32.c>


Number run_thread(void (*thread_function)(), Byte* argument)
{
	Number32 thread_id;

	CreateThread(0, 0, thread_function, argument, 0, &thread_id);

	return thread_id;
}


void sleep_thread(Number milliseconds)
{
	Sleep(milliseconds);
}

#endif//__WIN32__


#ifdef __linux__

#include <pthread.h>


Number run_thread (procedure (*thread_function)(), Byte *arg)
{
	pthread_t thread;
	pthread_create(&thread, 0, thread_function, arg);
}


void sleep_thread (N_32 milliseconds)
{
	usleep(milliseconds * 1000);
}

#endif//__linux__


#endif//THREAD_INCLUDED

/*
void a()
{
	for(;;) {
		printf("a");
		sleep_thread(1);
	}
}


void b()
{
	for(;;) {
		printf("b");
		sleep_thread(1);
	}
}


void main()
{
	printf("\nthread ID %d\n", run_thread(a, 0));
	printf("\nthread ID %d\n", run_thread(b, 0));
	run_thread(a, 0);

	for(;;);
}*/