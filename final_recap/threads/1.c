#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_DICE 6

int dice[NUM_DICE] = {0};
int status[NUM_DICE] = {0};
pthread_barrier_t wait_roll, wait_status_set;

void* f(void* arg) {
	int nr = rand() % 6 + 1;
	int index = *((int*) arg);

	dice[index] = nr;

	pthread_barrier_wait(&wait_roll);
	pthread_barrier_wait(&wait_status_set);

	if (status[index] == 1) {
		printf("Dice %d rolled %d: WON\n", index, nr);
	} else if (status[index] == 0) {
		printf("Dice %d rolled %d: LOST\n", index, nr);
	}

	free(arg);
	return NULL;
}

int main(int argc, char* argv[]) {
	int maximum = 0;
	pthread_t threads[NUM_DICE];

	pthread_barrier_init(&wait_roll, NULL, NUM_DICE + 1);
	pthread_barrier_init(&wait_status_set, NULL, NUM_DICE + 1);

	srand(time(NULL));
	for (int i = 0; i < NUM_DICE; i++) {
		int* index = (int*) malloc(sizeof(int));
		*index = i;
		pthread_create(&threads[i], NULL, f, (void*)index);
	}

	pthread_barrier_wait(&wait_roll);

	for (int i = 0; i < NUM_DICE; i++) {
		if (dice[i] > maximum) {
			maximum = dice[i];
		}
	}

	for (int i = 0; i < NUM_DICE; i++) {
		if (dice[i] == maximum) {
			status[i] = 1;
		} else {
			status[i] = 0;
		}
	}

	pthread_barrier_wait(&wait_status_set);

	for (int i = 0; i < NUM_DICE; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_barrier_destroy(&wait_roll);
	pthread_barrier_destroy(&wait_status_set);

	return 0;
}
