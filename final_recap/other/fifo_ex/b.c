#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: FIFO file name not provided.\n");
		return 1;
	}
	int s = 0, p[2];

	pipe(p);
	// Process P1
	if (fork() == 0) {
		close(p[0]);
		int a2b, x;

		a2b = open(argv[1], O_RDONLY);

		while (read(a2b, &x, sizeof(int)) > 0) {
			//printf("%d\n", x);
			s += x;
		}
		close(a2b);
		unlink(argv[1]);

		write(p[1], &s, sizeof(int));
		close(p[1]);

		exit(0);
	}

	// Process P2
	if (fork() == 0) {
		close(p[1]);
		
		read(p[0], &s, sizeof(int));
		close(p[0]);
		//printf("%d\n", s);
		
		printf("Divisors of %d:\n", s);
		for (int i = 1; i <= s; i++) {
			if (s % i == 0) {
				printf("%d\n", i);
			}
		}

		exit(0);
	}

	close(p[0]); close(p[1]); // The parent doesn't need/use the pipe
	
	wait(NULL);
	wait(NULL);

	return 0;
}
