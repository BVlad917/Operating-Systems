#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int a) {
	if (a <= 1) {
		return 0;
	}
	if (a == 2) {
		return 1;
	}
	if (a % 2 == 0) {
		return 0;
	}
	for (int d = 3; d * d <= a; d += 2) {
		if (a % d == 0) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[]) {
	int p2c[2], c2p[2], a[100];
	int n, i, x, pid, ok;

	printf("n = ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	for (i = 0; i < n; i++) {
		pipe(p2c); pipe(c2p);
		pid = fork();
		
		if (pid == 0) {
			// Child process
			close(p2c[1]); close(c2p[0]);

			read(p2c[0], &x, sizeof(int));
			close(p2c[0]);
			ok = is_prime(x);
			write(c2p[1], &ok, sizeof(int));
			close(c2p[1]);
			exit(0);
		}

		// Parent process
		close(p2c[0]); close(c2p[1]);
		
		write(p2c[1], &a[i], sizeof(int));
		close(p2c[1]);
		read(c2p[0], &ok, sizeof(int));
		close(c2p[0]);
		if (ok == 1) {
			printf("The number %d is a prime number.\n", a[i]);
		}
		else {
			printf("The number %d is NOT a prime number.\n", a[i]);
		}
	}

	for (i = 0; i < n; i++) {
		wait(NULL);
	}
	
	return 0;
}
