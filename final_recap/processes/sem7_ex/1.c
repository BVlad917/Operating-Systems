#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int n, p2c[2], c2p[2];
	double avg;

	pipe(p2c); pipe(c2p);

	// Child
	if (fork() == 0) {
		close(p2c[1]); close(c2p[0]);

		read(p2c[0], &n, sizeof(int));
		int s = 0, x;
		for (int i = 0; i < n; i++) {
			read(p2c[0], &x, sizeof(int));
			printf("Child received %d\n", x);
			s += x;
		}
		close(p2c[0]);

		avg = (double) s / n;
		write(c2p[1], &avg, sizeof(double));
		close(c2p[1]);
		exit(0);
	}

	// Parent
	close(p2c[0]); close(c2p[1]);
	printf("How many numbers: ");
	scanf("%d", &n);
	srand(time(NULL));
	write(p2c[1], &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		int nr = rand() % 100 + 1;
		printf("Parent sends %d\n", nr);
		write(p2c[1], &nr, sizeof(int));
	}
	close(p2c[1]);

	read(c2p[0], &avg, sizeof(double));
	close(c2p[0]);
	printf("The average is: %f\n", avg);

	wait(NULL);

	return 0;
}
