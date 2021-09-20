#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
	int p2c[2], c2p[2], pid;
	int a[100], i, n;
	double avg;

	if (pipe(p2c) == -1) {
		perror("ERROR: Could not open pipe.\n");
		return 1;
	}
	if (pipe(c2p) == -1) {
		close(p2c[0]); close(p2c[1]);
		perror("ERROR: Could not open pipe.\n");
		return 1;
	}
	pid = fork();

	if (pid == -1) {
		close(p2c[0]); close(p2c[1]);
		close(c2p[0]); close(c2p[1]);
		perror("ERROR: Unsuccessful fork.\n");
		return 1;
	}

	if (pid == 0) {
		// Child process
		close(p2c[1]); close(c2p[0]);
		read(p2c[0], &n, sizeof(int));
		int sum = 0;
		for (i = 0; i < n; i++) {
			read(p2c[0], &a[i], sizeof(int));
			sum += a[i];
		}
		close(p2c[0]);
		avg = (double) sum / n;
		write(c2p[1], &avg, sizeof(double));
		close(c2p[1]);
		exit(0);
	}

	// Parent process
	close(p2c[0]); close(c2p[1]);
	printf("n = ");
	scanf("%d", &n);
	srandom(time(NULL));
	for (i = 0; i < n; i++) {
		a[i] = random() % 100;
		printf("%d ", a[i]);
	}
	printf("\n");

	write(p2c[1], &n, sizeof(int));
	for (i = 0; i < n; i++) {
		write(p2c[1], &a[i], sizeof(int));
	}
	close(p2c[1]);
	read(c2p[0], &avg, sizeof(double));
	close(c2p[0]);

	printf("The average is: %f\n", avg);
	
	return 0;
}
