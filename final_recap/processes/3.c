/*
 * 3. Write a C program that will read from keyboard a string of characters, will generate a child process and to whom it will send the input. The child process will sort all the charcters alphabetically and it will return the results to the parent 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char a[101], aux;
	int n, p2c[2], c2p[2];

	pipe(p2c); pipe(c2p);

	if (fork() == 0) {
		close(p2c[1]); close(c2p[0]);

		read(p2c[0], &n, sizeof(int));
		for (int i = 0; i < n; i++) {
			read(p2c[0], &a[i], sizeof(char));
		}
		close(p2c[0]);

		for (int i = 0; i < n - 1; i++) {
			for (int j = (i + 1); j < n; j++) {
				if (a[i] > a[j]) {
					aux = a[i];
					a[i] = a[j];
					a[j] = aux;		
				}
			}
		}

		for (int i = 0; i < n; i++) {
			write(c2p[1], &a[i], sizeof(char));
		}
		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]); close(c2p[1]);

	printf("Give the string: ");
	scanf("%s", a);
	n = strlen(a);
	write(p2c[1], &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		write(p2c[1], &a[i], sizeof(char));
	}
	close(p2c[1]);

	for (int i = 0; i < n; i++) {
		read(c2p[0], &a[i], sizeof(char));
	}
	close(c2p[0]);

	printf("The sorted string is: ");
	for (int i = 0; i < n; i++) {
		printf("%c", a[i]);
	}
	printf("\n");

	wait(NULL);

	return 0;
}
