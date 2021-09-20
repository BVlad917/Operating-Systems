#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int p2c[2], c2p[2];
	char a[101];
	int pid, n, i;

	pipe(p2c); pipe(c2p);
	pid = fork();

	if (pid == 0) {
		// Child process
		close(p2c[1]); close(c2p[0]);
		
		read(p2c[0], &n, sizeof(int));
		for (i = 0; i < n; i++) {
			read(p2c[0], &a[i], sizeof(char));
		}
		close(p2c[0]);

		for (i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (a[i] > a[j]) {
					char temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
		
		for (i = 0; i < n; i++) {
			write(c2p[1], &a[i], sizeof(char));
		}
		close(c2p[1]);
		exit(0);
	}

	// Parent process
	close(p2c[0]); close(c2p[1]);

	fgets(a, 100, stdin);
	a[strlen(a) - 1] = '\0';
	n = strlen(a);

	write(p2c[1], &n, sizeof(int));
	for (i = 0; i < n; i++) {
		write(p2c[1], &a[i], sizeof(char));
	}
	close(p2c[1]);

	for (i = 0; i < n; i++) {
		read(c2p[0], &a[i], sizeof(char));
	}
	close(c2p[0]);

	printf("The sorted string is: ");
	fputs(a, stdout);
	printf("\n");
	wait(NULL);
	return 0;
}
