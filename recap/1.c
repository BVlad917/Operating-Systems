#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

key_t k = 4;

int main(int argc, char* argv[]) {
	//printf("Hello world!\n");
	int sem_id = semget(k, 1, IPC_CREAT);
	if (sem_id < 0) {
		printf("ERROR\n");
		return 1;
	}
	int fd = open("a.txt", O_WRONLY);
	int i = 200;
	while (i) {
		int n = rand() % 100 + 1;
		sem_wait((sem_t*)&sem_id);
		write(fd, &n, sizeof(int));
		sem_post((sem_t*)&sem_id);
		i--;
	}
	close(fd);
	sem_destroy((sem_t*)&sem_id);
	return 0;
}
