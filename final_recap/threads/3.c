#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int stack[100];
int n = 0;
pthread_cond_t c1;

void* producer(void* arg) {

	return NULL;
}

void* consumer(void* arg) {

	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t prod, cons;

	pthread_cond_init(&c1, NULL);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	pthread_cond_destroy(&c1);

	return 0;
}
