/*
3. Write a C program that creates two child processes. The two child processes will alternate sending random integers between 1 and 10(inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int a2b[2], b2a[2];
	int pid;

	pipe(a2b); pipe(b2a);
	pid = fork();
	if (pid == 0) {
		// Child process A
		close(a2b[0]); close(b2a[1]);
		srandom(time(NULL));

		int x = random() % 10 + 1;
		printf("A sends to B %d\n", x);
		write(a2b[1], &x, sizeof(int));

		read(b2a[0], &x, sizeof(int));

		close(a2b[1]);
		close(b2a[0]);

		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		// Child process B
		close(b2a[0]); close(a2b[1]);
		srandom(time(NULL));
		int x, y;

		read(a2b[0], &x, sizeof(int));

		//printf("Before change %d\n", x);
		y = (int) random() % 10 + 1;
		printf("B sends to A %d\n", y);
		write(b2a[1], &x, sizeof(int));

		close(a2b[0]);
		close(b2a[1]);

		exit(0);
	}

	// Parent process
	wait(NULL); wait(NULL);

	return 0;
}
