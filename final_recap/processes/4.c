/*	4. Write a C program that will read from keyboard N numbers, for each number it will generate a child
 *	 process to whom it will send the number. The child process will check if the number is a prime number 
 *	 and it will return a response to the parent that will display it on the screen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int is_prime(int n) {
	if (n <= 1) {
		return 0;
	}
	if (n == 2) {
		return 1;
	}
	if (n % 2 == 0) {
		return 0;
	}
	for (int d = 3; d * d <= n; d += 2) {
		if (n % d == 0) {
			return 0;
		}
	}
	return 1;
}

struct obj {
	int num;
	int prime;
};

int main(int argc, char* argv[]) {
	struct obj a[100];
	int n, p2c[2], c2p[2];

	pipe(p2c); pipe(c2p);

	if (fork() == 0) {
		close(p2c[1]); close(c2p[0]);

		read(p2c[0], &n, sizeof(int));
		for (int i = 0; i < n; i++) {
			read(p2c[0], &a[i], sizeof(struct obj));
		}
		close(p2c[0]);

		for (int i = 0; i < n; i++) {
			a[i].prime = is_prime(a[i].num);
		}

		for (int i = 0; i < n; i++) {
			write(c2p[1], &a[i], sizeof(struct obj));
		}
		close(c2p[1]);
		exit(0);

	}
	close(p2c[0]); close(c2p[1]);
	printf("How many numbers: ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("a[%d] = ", i);
		scanf("%d", &a[i].num);
	}

	write(p2c[1], &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		write(p2c[1], &a[i], sizeof(struct obj));
	}
	close(p2c[1]);

	for (int i = 0; i < n; i++) {
		read(c2p[0], &a[i], sizeof(struct obj));
	}
	close(c2p[0]);

	for (int i = 0; i < n; i++) {
		if (a[i].prime == 0) {
			printf("%d is NOT prime.\n", a[i].num);
		}
		else if (a[i].prime == 1) {
			printf("%d is prime.\n", a[i].num);
		}
	}

	wait(NULL);

	return 0;
}
