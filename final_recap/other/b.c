#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int x, a2b, b2a, end_5 = 0;
	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	while (read(a2b, &x, sizeof(int)) > 0) {
		if (x % 10 == 5) {
			end_5 += 1;
		}
	}
	close(a2b);

	write(b2a, &end_5, sizeof(int));
	close(b2a);
	
	return 0;
}
