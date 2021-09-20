/*
2. Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int p2c[2], c2p[2], a[100];
	int pid, n, i;
	double avg;
	if (argc != 2) {
		perror("ERROR: Invalid number of arguments given.\n");
		return 1;
	}
	n = atoi(argv[1]);
	if (n == 0) {
		printf("Given N is 0 => the average is 0.\n");
		return 0;
	}

	pipe(p2c); pipe(c2p);

	pid = fork();
	if (pid == 0) {
		// Child process
		close(p2c[1]); close(c2p[0]);

		read(p2c[0], &n, sizeof(int));
		int sum = 0, x;
		for (i = 0; i < n; i++) {
			read(p2c[0], &x, sizeof(int));
			sum += x;
		}
		close(p2c[0]);
		avg = (double) sum / n;
		write(c2p[1], &avg, sizeof(double));
		close(c2p[1]);
		exit(0);
	}
	
	// Parent process
	close(p2c[0]); close(c2p[1]);
	write(p2c[1], &n, sizeof(int));

	srandom(time(NULL));
	printf("The numbers are: ");
	for (i = 0; i < n; i++) {
		a[i] = random() % 100;
		printf("%d ", a[i]);
		write(p2c[1], &a[i], sizeof(int));
	}
	printf("\n");
	close(p2c[1]);
	read(c2p[0], &avg, sizeof(double));
	close(c2p[0]);
	printf("The average is: %f\n", avg);
	wait(NULL);
	return 0;
}
