#include <stdio.h>
#include <pthread.h>

#define THREADS_NUM 5

pthread_mutex_t mtx;
pthread_barrier_t b;

void* f(void* arg) {
	int* s = (int*)arg;
	pthread_mutex_lock(&mtx);
	(*s)++;
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&b);
	printf("%d\n", *s);
	return NULL;
}

int main(int argc, char* argv[]) {
	int i, s = 0;
	pthread_t t[THREADS_NUM];
	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&b, NULL, THREADS_NUM);

	for (i = 0; i < THREADS_NUM; i++) {
		pthread_create(&t[i], NULL, f, (void*)&s);
	}

	for (i = 0; i < THREADS_NUM; i++) {
		pthread_join(t[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&b);
	printf("The sum is %d\n", s);
	return 0;
}
