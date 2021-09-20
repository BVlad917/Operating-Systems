#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void fn(int p2c[]) {
	int pid = fork();
	
	if (pid == 0) {
		int m, n;
		read(p2c[0], &m, sizeof(int));
		read(p2c[0], &n, sizeof(int));
		if (m >= 1) {
			m -= 1;
			n += 1;
			write(p2c[1], &m, sizeof(int));
			write(p2c[1], &n, sizeof(int));
			fn(p2c);
		}
		else if (m == 0) {
			printf("Final number is: %d\n", n);
		}
		exit(0);
	}
	wait(NULL);
}

int main(int argc, char* argv[]) {
	int n, m;
	printf("Give n: ");
	scanf("%d", &n);
	printf("Give m: ");
	scanf("%d", &m);

	if (m < 1) {
		printf("Nothing.\n");
		return 0;
	}

	int p2c[2];
	pipe(p2c);
	int pid = fork();

	if (pid == 0) {
		// Child process
		fn(p2c);
		exit(0);
	}

	// Parent process
	close(p2c[0]);
	write(p2c[1], &m, sizeof(int));
	write(p2c[1], &n, sizeof(int));
	close(p2c[1]);
	wait(NULL);
	return 0;
}
