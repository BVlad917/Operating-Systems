#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int n, x, p2c[2], c2p[2];
	char s[31];
	srand(time(NULL));
	
	pipe(p2c); pipe(c2p);

	if (fork() == 0) {
		close(p2c[1]); close(c2p[0]);

		read(p2c[0], &n, sizeof(int));
		read(p2c[0], s, sizeof(char) * n);
		for (int i = 0; i < n; i++) {
			x = rand() % 25;
			//printf("Generated %d\n", x);
			s[i] += x;
			write(c2p[1], &x, sizeof(int));
		}
		close(p2c[0]);
		write(c2p[1], s, sizeof(char) * n);
		close(c2p[1]);
		exit(0);
	}
	
	close(p2c[0]); close(c2p[1]);

	n = rand() % 21 + 10;
	for (int i = 0; i < n; i++) {
		s[i] = 'a';
	}
	s[n] = '\0';

	printf("%s\n", s);
	write(p2c[1], &n, sizeof(int));
	write(p2c[1], s, sizeof(char) * n);
	close(p2c[1]);

	for (int i = 0; i < n; i++) {
		read(c2p[0], &x, sizeof(int));
		printf("Generated %d\n", x);
	}
	read(c2p[0], s, sizeof(char) * n);
	close(c2p[0]);

	printf("%s\n", s);

	wait(NULL);

	return 0;
}
