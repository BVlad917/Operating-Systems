#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	char a[101];
	int p2c[2], c2p[2], pid, n, i;
	pipe(p2c); pipe(c2p);

	pid = fork();
	if (pid == 0) {
		// Child process
		close(p2c[1]); close(c2p[0]);
		read(p2c[0], &n, sizeof(int));
		for (i = 0; i <= n; i++) {
			read(p2c[0], &a[i], sizeof(char));
		}
		close(p2c[0]);
		char aux;
		for (i = 0; i < strlen(a) - 1; i++) {
			for (int j = (i + 1); j < strlen(a); j++) {
				if (a[i] > a[j]) {
					aux = a[i];
					a[i] = a[j];
					a[j] = aux;		
				}
			}
		}
		// Send the whole string + the null terminating character (hence the '<=' instead of just '<')
		for (i = 0; i <= strlen(a); i++) {
			write(c2p[1], &a[i], sizeof(char));
		}
		close(c2p[1]);
		exit(0);
	}
	
	// Parent process
	close(p2c[0]); close(c2p[1]);

	fgets(a, 100, stdin);
	// Replace the newline character at the end with the NULL-terminating character
	a[strlen(a) - 1] = '\0';
	n = strlen(a);
	
	write(p2c[1], &n, sizeof(int));
	for (i = 0; i <= n; i++) {
		write(p2c[1], &a[i], sizeof(char));
	}
	close(p2c[1]);
	for (i = 0; i <= n; i++) {
		read(c2p[0], &a[i], sizeof(char));
	}
	close(c2p[0]);

	printf("The sorted string is: ");
	fputs(a, stdout);
	printf("\n");

	return 0;
}
