#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: FIFO file name not provided.\n");
		return 1;
	}
	int a2b, n, x;

	if (mkfifo(argv[1], 0600) < 0) {
		printf("ERROR: Failed to create FIFO.\n");
		return 1;
	}

	a2b = open(argv[1], O_WRONLY);

	printf("How many numbers: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Give number %d: ", i);
		scanf("%d", &x);
		write(a2b, &x, sizeof(int));
	}
	close(a2b);


	return 0;
}
