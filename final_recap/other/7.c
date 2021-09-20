#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int s = 0;
//pthread_mutex_t mtx_a, mtx_b;
pthread_barrier_t bar;
pthread_rwlock_t rwlock_a, rwlock_b;

void* f(void* arg) {
	int index = *((int*)arg);
	int subtracted = 0;

	int A = rand() % 10 + 1;
	pthread_rwlock_wrlock(&rwlock_a);
	s += A;
	pthread_rwlock_unlock(&rwlock_a);

	pthread_barrier_wait(&bar);

	int B = rand() % 15 + 1;
	pthread_rwlock_wrlock(&rwlock_b);
	if (s >= B) {
		s -= B;
		subtracted = 1;
	}
	pthread_rwlock_unlock(&rwlock_b);
	
	if (subtracted == 1) {
		printf("Thread %d; A = %d; B = %d; SUBTRACTED\n", index, A, B);
	} else {
		printf("Thread %d; A = %d; B = %d; DID NOT SUBTRACT\n", index, A, B);
	}

	free(arg);
	return NULL;
}

int main(int argc, char* argv[]) {
	int n;
	int* index;
	pthread_t* thrds;
	if (argc != 2) {
		printf("ERROR: Invalid argument given.\n");
		return 1;
	}
	n = atoi(argv[1]);
	if (n == 0) {
		printf("ERROR: N has to be a positive integer.\n");
		return 1;
	}

	thrds = (pthread_t*) malloc(sizeof(pthread_t) * n);

	//pthread_mutex_init(&mtx_a, NULL);
	//pthread_mutex_init(&mtx_b, NULL);

	pthread_rwlock_init(&rwlock_a, NULL);
	pthread_rwlock_init(&rwlock_b, NULL);

	pthread_barrier_init(&bar, NULL, n);
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		index = (int*) malloc(sizeof(int));
		*index = i;
		pthread_create(&thrds[i], NULL, f, (void*)index);
	}

	for (int i = 0; i < n; i++) {
		pthread_join(thrds[i], NULL);
	}
	printf("\nFinal sum = %d\n", s);

	//pthread_mutex_destroy(&mtx_a);
	//pthread_mutex_destroy(&mtx_b);
	
	pthread_rwlock_destroy(&rwlock_a);
	pthread_rwlock_destroy(&rwlock_b);
	
	pthread_barrier_destroy(&bar);
	free(thrds);

	return 0;
}
