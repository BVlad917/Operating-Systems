#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int i, j, p, p2;
	for (i = 0; i < 3; i++) {
		p = fork();
		if (p == 0) {
			for (j = 0; j < 3; j++) {
				p2 = fork();
				if (p2 == 0) {
					printf("PID=%d, PPID=%d\n", getpid(), getppid());
					exit(0);
				}
			}
			for (j = 0; j < 3; j++) {
				wait(NULL);
			}
		//	printf("\n");
			exit(0);
		}
	}
	for (i = 0; i < 3; i++) {
		wait(NULL);
	}
	return 0;
}
