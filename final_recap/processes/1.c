/* C program that will read from keyboard an array of N numbers and it will generate 3 child processes. The main process will send to each of the child processes the array which will do the following:
   - c1: compute maximum 
   - c2: compute minimum 
   - c3: compute average
   The results of the child processes will be returned to the part that will display them on the screen.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int p2a[2], p2b[2], p2c[2];
	int a2p[2], b2p[2], c2p[2];
	int max, min, n, a[100];
	double avg;

	pipe(p2a); pipe(a2p);
	pipe(p2b); pipe(b2p);
	pipe(p2c); pipe(c2p);

	// Process A
	if (fork() == 0) {
		close(p2a[1]); close(a2p[0]);
		close(p2b[0]); close(p2b[1]); close(p2c[0]); close(p2c[1]);
		close(b2p[0]); close(b2p[1]); close(c2p[0]); close(c2p[1]);
		if (read(p2a[0], &n, sizeof(int)) <= 0) {
			printf("No N provided to process A.\n");
			exit(1);
		}
		if (n <= 0) {
			printf("Invalid N provided to process A.\n");
			exit(1);
		}
		for (int i = 0; i < n; i++) {
			read(p2a[0], &a[i], sizeof(int));
			if (i == 0) {
				max = a[i];
			}
			else {
				if (a[i] > max) {
					max = a[i];
				}
			}
		}
		close(p2a[0]);
		write(a2p[1], &max, sizeof(int));
		close(a2p[1]);
		exit(0);
	}

	// Process B
	if (fork() == 0) {
		close(p2b[1]); close(b2p[0]);
		close(p2a[0]); close(p2a[1]); close(p2c[0]); close(p2c[1]);
		close(a2p[0]); close(a2p[1]); close(c2p[0]); close(c2p[1]);
		if (read(p2b[0], &n, sizeof(int)) <= 0) {
			printf("Failed to read N in process B.\n");
			exit(1);
		}
		if (n <= 0) {
			printf("Invalid N given in process B.\n");
			exit(1);
		}
		for (int i = 0; i < n; i++) {
			read(p2b[0], &a[i], sizeof(int));
			if (i == 0) {
				min = a[i];
			}
			else {
				if (a[i] < min) {
					min = a[i];
				}
			}
		}
		close(p2b[0]);
		write(b2p[1], &min, sizeof(int));
		close(b2p[1]);
		exit(0);
	}

	// Process C
	if (fork() == 0) {
		close(p2c[1]); close(c2p[0]);
		close(a2p[0]); close(a2p[1]); close(b2p[0]); close(b2p[1]);
		close(p2a[0]); close(p2a[1]); close(p2b[0]); close(p2b[1]);
		if (read(p2c[0], &n, sizeof(int)) <= 0) {
			printf("Failed to read N in process C.\n");
			exit(1);
		}
		if (n <= 0) {
			printf("Invalid N given in process C.\n");
			exit(1);
		}
		int s = 0;
		for (int i = 0; i < n; i++) {
			read(p2c[0], &a[i], sizeof(int));
			s += a[i];
		}
		close(p2c[0]);
		avg = (double) s / (double) n;
		write(c2p[1], &avg, sizeof(double));
		close(c2p[1]);
		exit(0);
	}

	// Parent
	close(p2a[0]); close(a2p[1]);
	close(p2b[0]); close(b2p[1]);
	close(p2c[0]); close(c2p[1]);

	printf("Give N: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Give a[%d]: ", i);
		scanf("%d", &a[i]);
	}
	
	write(p2a[1], &n, sizeof(int));
	write(p2b[1], &n, sizeof(int));
	write(p2c[1], &n, sizeof(int));
	
	for (int i = 0; i < n; i++) {
		write(p2a[1], &a[i], sizeof(int));
		write(p2b[1], &a[i], sizeof(int));
		write(p2c[1], &a[i], sizeof(int));
	}

	close(p2a[1]); close(p2b[1]); close(p2c[1]);

	read(a2p[0], &max, sizeof(int));
	close(a2p[0]);

	read(b2p[0], &min, sizeof(int));
	close(b2p[0]);
	
	read(c2p[0], &avg, sizeof(double));
	close(c2p[0]);

	printf("The maximum is %d\n", max);
	printf("The minimum is %d\n", min);
	printf("The average is %f\n", avg);

	wait(NULL); wait(NULL); wait(NULL);
	return 0;
}
