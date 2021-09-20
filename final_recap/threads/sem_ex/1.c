#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* f(void* arg) {
	char* str = (char*)arg;
	int n = strlen(str);
	for (int i = 0; i < n; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = 'A' + str[i] - 'a';
		}
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1));

	for (int i = 1; i < argc; i++) {
		pthread_create(&threads[i - 1], NULL, f, (void*)argv[i]);
	}

	for (int i = 1; i < argc; i++) {
		pthread_join(threads[i - 1], NULL);
	}

	for (int i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	free(threads);

	return 0;
}
