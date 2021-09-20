#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	execlp("grep", "grep", "-E", "mere", "./a.txt", NULL);
	printf("If grep is in the PATH, then execlp succeds and this will never be printed\n");
	return 0;
}
