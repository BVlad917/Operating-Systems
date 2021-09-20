#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int pid = fork();
	if (pid == 0) {
		printf("Child-only code\n");
		exit(0);
	}
	printf("Parent-only code\n");
	wait(NULL);
	return 0;
}
