#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int p2a[2], a2b[2], b2p[2];
	int pid, nr;
	pipe(p2a); pipe(a2b); pipe(b2p);

	pid = fork();
	if (pid == 0) {
		// Child process A
		close(p2a[1]);
		close(a2b[0]);
		close(b2p[0]); close(b2p[1]);
		while (1) {
			if (read(p2a[0], &nr, sizeof(int)) <= 0) {
				break;
			}
			if (nr == 0) {
				break;
			}
			printf("%d -> %d\n", nr, nr - 1);
			nr -= 1;
			write(a2b[1], &nr, sizeof(int));
		}
		close(p2a[0]);
		close(a2b[1]);
		exit(0);
	}

	pid = fork();
	if (pid == 0) {
		// Child process B
		close(a2b[1]);
		close(b2p[0]);
		close(p2a[0]); close(p2a[1]);
		while (1) {
			if (read(a2b[0], &nr, sizeof(int)) <= 0) {
				break;
			}
			if (nr == 0) {
				break;
			}
			printf("%d -> %d\n", nr, nr - 1);
			nr -= 1;
			write(b2p[1], &nr, sizeof(int));
		}
		close(a2b[0]);
		close(b2p[1]);
		exit(0);
	}

	// Parent process
	close(b2p[1]);
	close(p2a[0]);
	close(a2b[0]); close(a2b[1]);
	nr = 20;
	write(p2a[1], &nr, sizeof(int));
	while (1) {
		if (read(b2p[0], &nr, sizeof(int)) <= 0) {
			break;
		}
		if (nr == 0) {
			break;
		}
		printf("%d -> %d\n", nr, nr - 1);
		nr -= 1;
		write(p2a[1], &nr, sizeof(int));
	}
	close(p2a[1]);
	close(b2p[0]);
	wait(NULL); wait(NULL);

	return 0;
}
