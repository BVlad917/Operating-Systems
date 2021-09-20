#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int fib[N] = {0}, flags[N] = {0};
pthread_mutex_t mtx;
pthread_cond_t cond;

void* f(void* arg) {
	int index = *((int*)arg);

	if (index == 0 || index == 1) {
		flags[index] = 1;
		fib[index] = index;
	} else {
		if (flags[index - 1] == 0) {
			pthread_mutex_lock(&mtx);
			pthread_cond_wait(&cond, &mtx);
			pthread_mutex_unlock(&mtx);
		}
		if (flags[index - 2] == 0) {
			pthread_mutex_lock(&mtx);
			pthread_cond_wait(&cond, &mtx);
			pthread_mutex_unlock(&mtx);
		}
		fib[index] = fib[index - 1] + fib[index - 2];
		flags[index] = 1;
		pthread_cond_signal(&cond);
	}

	free(arg);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t thrds[N + 1];
	int i, *index;

	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);
	for (i = 0; i <= N; i++) {
		index = (int*) malloc(sizeof(int));
		*index = i;
		pthread_create(&thrds[i], NULL, f, (void*)index);
	}

	for (i = 0; i <= N; i++) {
		pthread_join(thrds[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);

	printf("Fibonacci of %d is: %d\n", N, fib[N]);

	return 0;
}
