/*
 * 5. Vom create N thread-uri considerate consumatori, si M thread-uri considerate producatori.
 *     Un producator va insera un numar de X mesaje (pot fi orice, numere, charactere etc.) intr-o coada globala. De fiecare data cand coada se umple (adica atinge o limita L) producatorii vor trebui sa astepte pana cand se elibereaza cel putin un loc in coada.
 *         Un consumator va extrage mesaje din aceeasi coada globala. De fiecare data cand coada este goala, consumatorii vor trebui sa astepte pana cad se adauga cel putin un element. 
 *
 *             Se doreste implementarea acestor mecanisme de asteptare/notificare folosind variabile conditionale. 
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 2	// Number of consumers
#define M 1	// Number of producers
#define L 10	// Maximum size of queue

int queue[L];
int size = 0;
pthread_mutex_t mtx;
pthread_cond_t wait_for_producer, wait_for_consumer;

void* producer(void* arg) {
	while (1) {
		int x = rand() % 100;
		pthread_mutex_lock(&mtx);
	
		while (size == L) {
			pthread_cond_wait(&wait_for_consumer, &mtx);
		}

		queue[size] = x;
		size++;
	
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&wait_for_producer);
	}
	return NULL;
}

void* consumer(void* arg) {
	while (1) {
		pthread_mutex_lock(&mtx);

		while (size == 0) {
			pthread_cond_wait(&wait_for_producer, &mtx);
		}

		int x = queue[0];
		printf("Consumer got %d\n", x);
		for (int i = 0; i < size - 1; i++) {
			queue[i] = queue[i + 1];
		}
		size--;
		sleep(1);

		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&wait_for_consumer);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	int i;
	pthread_t t[20];
	srand(time(NULL));
	
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&wait_for_producer, NULL);
	pthread_cond_init(&wait_for_consumer, NULL);


	for (i = 0; i < N; i++) {
		pthread_create(&t[i], NULL, producer, NULL);
	}
	for (i = N; i < N + M; i++) {
		pthread_create(&t[i], NULL, consumer, NULL);
	}

	for (i = 0; i < N + M; i++) {
		pthread_join(t[i], NULL);
	}
	pthread_cond_destroy(&wait_for_consumer);
	pthread_cond_destroy(&wait_for_producer);
	pthread_mutex_destroy(&mtx);

	return 0;
}
