#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int fuel = 0;
pthread_mutex_t m;
pthread_cond_t c;

void* refill(void* arg) {
	for (int i = 0; i < 5; i++) {
		pthread_mutex_lock(&m);
		fuel += 15;
		printf("Refilled...%d\n", fuel);
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c);
		sleep(1);
	}
	return NULL;
}

void* car(void* arg) {
	pthread_mutex_lock(&m);
	while (fuel < 40) {
		pthread_cond_wait(&c, &m);
	}
	fuel -= 40;
	printf("Car got fuel. Remaining %d\n", fuel);
	pthread_mutex_unlock(&m);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&c, NULL);

	//pthread_create(&t1, NULL, refill, NULL);
	pthread_create(&t2, NULL, car, NULL);
	pthread_create(&t1, NULL, refill, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);

	return 0;
}
