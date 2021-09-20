#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int a2b, b2a, n, end_5;
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	scanf("%d", &n);
	int* a = (int*) malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < n; i++) {
		write(a2b, &a[i], sizeof(int));
	}
	close(a2b);

	read(b2a, &end_5, sizeof(int));
	close(b2a);
	printf("Numbers that end in 5: %d\n", end_5);

	return 0;
}
