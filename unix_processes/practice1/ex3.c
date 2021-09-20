#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int r;
	r = fork();
	printf("PID=%d, PPID=%d, R=%d\n", getpid(), getppid(), r);
	wait(NULL);
	return 0;
}
