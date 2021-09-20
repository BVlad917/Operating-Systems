#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int p[2];
	char buf[10];
	int n;
	pipe(p);
	close(p[1]);
	n = read(p[0], buf, 10);
	printf("%d\n", n);
	return 0;
}
