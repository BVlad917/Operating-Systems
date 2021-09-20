#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int p2c[2], c2p[2];
	int pid, a, b, s, p;
	pipe(p2c); pipe(c2p);

	pid = fork();
	if (pid == 0) {
		// Child process
		close(c2p[0]);
		close(p2c[1]);
		while (1) {
			scanf("%d %d", &a, &b);
			write(c2p[1], &a, sizeof(int));
			write(c2p[1], &b, sizeof(int));
			read(p2c[0], &s, sizeof(int));
			read(p2c[0], &p, sizeof(int));
			if (s == p) {
				break;
			}
		}
		close(c2p[1]);
		close(p2c[0]);
		exit(0);
	}

	// Parent process
	close(p2c[0]);
	close(c2p[1]);
	while (1) {
		if (read(c2p[0], &a, sizeof(int)) <= 0) {
			printf("Sum = Product = %d\n", s);
			break;
		}
		read(c2p[0], &b, sizeof(int));
		s = a + b;
		p = a * b;
		write(p2c[1], &s, sizeof(int));
		write(p2c[1], &p, sizeof(int));
	}
	close(c2p[0]);
	close(p2c[1]);
	wait(NULL);

	return 0;
}
