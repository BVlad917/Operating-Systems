#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 1000

int n = 0;
pthread_mutex_t mtx;

void* f(void* arg) {
	for (int i = 0; i < 1000; i++) {
		pthread_mutex_lock(&mtx);
		n++;
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t thrds[THREAD_NUM];
	
	pthread_mutex_init(&mtx, NULL);
	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_create(&thrds[i], NULL, f, NULL);
	}

	for (int i = 0; i < THREAD_NUM; i++) {
		pthread_join(thrds[i], NULL);
	}

	printf("%d\n", n);

	return 0;
}
