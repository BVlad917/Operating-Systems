#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int a[] = {1, 2, 3, 4};
	int p[2], pid;
	pipe(p);
	close(p[1]);
	pid = fork();

	if (pid == 0) {
		close(p[0]);
		a[2] += a[3];
		write(p[1], &a[2], sizeof(int));
		close(p[1]);
		exit(0);
	}
	
	//close(p[1]);
	a[0] += a[1];
	read(p[0], &a[2], sizeof(int));
	close(p[0]);
	a[0] += a[2];
	printf("The sum is: %d\n", a[0]);
	wait(NULL);
	return 0;
}
