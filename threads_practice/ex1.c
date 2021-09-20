#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		perror("ERROR: Invalid number of arguments given.\n");
		return 1;
	}
	printf("%d\n", atoi(argv[1]));
	return 0;
}
