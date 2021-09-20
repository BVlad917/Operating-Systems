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

	int semid = semget(key, 0, 0);
	if (semid < 0)
	{
		perror("semget(): ");
		exit(EXIT_FAILURE);
	}

	int pd = open("hello", O_RDONLY);
	if (pd < 0)
	{
		perror("open(): ");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		int n1, n2;

		sem_wait((sem_t *) &semid);
		read(pd, &n1, sizeof(int));
		read(pd, &n2, sizeof(int));

		printf("Suma: %d\n", n1 + n2);
		sem_post((sem_t *) &semid);
	}

	close(pd);
	sem_destroy((sem_t *)&semid);

	return 0;
}

