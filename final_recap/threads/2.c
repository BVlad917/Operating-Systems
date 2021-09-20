#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int s = 0;
pthread_mutex_t ma, mb;
pthread_barrier_t b;

void* f(void* arg) {
	int subtracted = 0;
	int index = *((int*)arg);

	int A = rand() % 10 + 1;

	pthread_mutex_lock(&ma);
	s += A;
	pthread_mutex_unlock(&ma);

	pthread_barrier_wait(&b);

	int B = rand() % 15 + 1;

	pthread_mutex_lock(&mb);
	if (s >= B) {
		s -= B;
		subtracted = 1;
	}
	pthread_mutex_unlock(&mb);

	if (subtracted == 1) {
		printf("Thread %d: A = %d; B = %d; SUBTRACTED\n", index, A, B);
	} else if (subtracted == 0) {
		printf("Thread %d: A = %d; B = %d; DID NOT SUBTRACT\n", index, A, B);
	}

	free(arg);
	return NULL;
}

int main(int argc, char* argv[]) {
	int n;
	if (argc != 2) {
		printf("ERROR: Invalid number of arguments given\n");
		return 1;
	}
	n = atoi(argv[1]);
	if (n == 0) {
		printf("ERROR: N should be a positive integer.\n");
		return 1;
	}
	pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * n);

	srand(time(NULL));
	pthread_mutex_init(&ma, NULL);
	pthread_mutex_init(&mb, NULL);
	pthread_barrier_init(&b, NULL, n);

	for (int i = 0; i < n; i++) {
		int* index = (int*)malloc(sizeof(int));
		*index = i;
		pthread_create(&threads[i], NULL, f, (void*)index);
	}

	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&ma);
	pthread_mutex_destroy(&mb);
	pthread_barrier_destroy(&b);

	printf("\nAt the end the sum is: %d\n", s);

	free(threads);

	return 0;
}
