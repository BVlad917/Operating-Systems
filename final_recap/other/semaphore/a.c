#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <unistd.h>

int main()
{
	key_t key = 999;   // key to pass to semget()

	int semid = semget(key, 1, IPC_CREAT | 0666); //get the semaphore stored in the shared memory with the key key – if does not exist it will be created.

	if (semid < 0)
	{
		perror("semget(): ");
		exit(EXIT_FAILURE);
	}

	int pd = open("hello", 1);
	if (pd < 0)
	{
		perror("open(): ");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	printf("Ana are mere\n");
	while (1)
	{
		int n1 = rand() % 100;
		int n2 = rand() % 100;

		sem_wait((sem_t *)&semid); //turn semaphore to “red” or wait if it is already red.
		write(pd, &n1, sizeof(int));
		write(pd, &n2, sizeof(int));
		sem_post((sem_t *) &semid); ////turn semaphore to “green” and signal the waiting processes/threads
	}

	close(pd);
	sem_destroy((sem_t *) &semid);

	return 0;
}

