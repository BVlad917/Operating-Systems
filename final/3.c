#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int r, n, k = 10;
	r = open("abc", O_WRONLY);
	n = write(r, &k, sizeof(int));
	printf("%d\n", n);
	return 0;
}
