#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
void *print_tid(void *ptr)
{
	printf("Hello from thread: %d at pid %d\n", *(int *)(ptr), getpid());
	return ptr;
}
int main(void)
{
	int pid[8];
	pthread_t pt[8];
	int i;

	i = -1;
	while (++i < 8)
	{
		pid[i] = pthread_create(&pt[i], NULL, print_tid, i);
	}
	sleep(1);
}