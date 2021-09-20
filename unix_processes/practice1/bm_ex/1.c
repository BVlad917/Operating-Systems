#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int p2a[2], p2b[2], p2c[2];
	int a2p[2], b2p[2], c2p[2];
	int maximum, minimum, n, i, a[100];
	double avg;

	pipe(p2a); pipe(a2p);
	pipe(p2b); pipe(b2p);
	pipe(p2c); pipe(c2p);

	int pid = fork();
	if (pid == 0) {
		// Process A
		close(p2a[1]); close(a2p[0]);
		close(p2b[0]); close(p2b[1]); close(b2p[0]); close(b2p[1]);
		close(p2c[0]); close(p2c[1]); close(c2p[0]); close(c2p[1]);

		if (read(p2a[0], &n, sizeof(int)) <= 0) {
			perror("Error reading N in process A.\n");
			exit(1);
		}
		if (n == 0) {
			perror("Process A exits: No elements in the array.\n");
			exit(1);
		}
		read(p2a[0], &a[0], sizeof(int));
		maximum = a[0];
		for (i = 1; i < n; i++) {
			read(p2a[0], &a[i], sizeof(int));
			if (a[i] > maximum) {
				maximum = a[i];
			}
		}
		close(p2a[0]);
		write(a2p[1], &maximum, sizeof(int));
		close(a2p[1]);
		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		// Process B
		close(p2b[1]); close(b2p[0]);
		close(p2a[0]); close(p2a[1]); close(a2p[0]); close(a2p[1]);
		close(p2c[0]); close(p2c[1]); close(c2p[0]); close(c2p[1]);
		
		if (read(p2b[0], &n, sizeof(int)) <= 0) {
			perror("Error reading N in process B.\n");
			exit(1);
		}
		if (n == 0) {
			perror("Process B exits: No elements in the array.\n");
			exit(1);
		}
		read(p2b[0], &a[0], sizeof(int));
		minimum = a[0];
		for (i = 1; i < n; i++) {
			read(p2b[0], &a[i], sizeof(int));
			if (a[i] < minimum) {
				minimum = a[i];
			}
		}
		close(p2b[0]);
		write(b2p[1], &minimum, sizeof(int));
		close(b2p[1]);
		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		// Process C
		close(p2c[1]); close(c2p[0]);
		close(p2a[0]); close(p2a[1]); close(a2p[0]); close(a2p[1]);
		close(p2b[0]); close(p2b[1]); close(b2p[0]); close(b2p[1]);
		
		if (read(p2c[0], &n, sizeof(int)) <= 0) {
			perror("Error reading N in process C.\n");
			exit(1);
		}
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
	close(p2a[0]); close(p2b[0]); close(p2c[0]);
	close(a2p[1]); close(b2p[1]); close(c2p[1]);
	
	printf("n = ");
	scanf("%d", &n);
	printf("Give the numbers:\n");
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	
	// Send data to processes A, B, C
	write(p2a[1], &n, sizeof(int));
	write(p2b[1], &n, sizeof(int));
	write(p2c[1], &n, sizeof(int));

	for (i = 0; i < n; i++) {
		write(p2a[1], &a[i], sizeof(int));
		write(p2b[1], &a[i], sizeof(int));
		write(p2c[1], &a[i], sizeof(int));
	}
	close(p2a[1]);
	close(p2b[1]);
	close(p2c[1]);

	read(a2p[0], &maximum, sizeof(int));
	close(a2p[0]);

	read(b2p[0], &minimum, sizeof(int));
	close(b2p[0]);

	read(c2p[0], &avg, sizeof(double));
	close(c2p[0]);

	printf("The maximum is: %d\n", maximum);
	printf("The minimum is: %d\n", minimum);
	printf("The average is: %f\n", avg);

	return 0;
}
