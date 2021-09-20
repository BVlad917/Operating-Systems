#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void f(int n) {
	if (n > 0 || fork() == 0) {
		f(n - 1);
		exit(0);
	}
	wait(0);
}

int main(int argc, char* argv[]) {
	f(3);
	return 0;
}
