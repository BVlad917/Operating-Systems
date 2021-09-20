#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* roll_dice(void* arg) {
	srand(time(NULL));
	int* res = (int*) malloc(sizeof(int));
	*res = rand() % 6 + 1;
	return (void*)res;
}

int main(int argc, char* argv[]) {
	pthread_t t[6];
	int* res[6];

	for (int i = 0; i < 6; i++) {
		pthread_create(&t[i], NULL, roll_dice, NULL);
	}
	for (int i = 0; i < 6; i++) {
		pthread_join(t[i], (void*)&res[i]);
	}
	for (int i = 0; i < 6; i++) {
		printf("Dice: %d\n", *(res[i]));
	}
	for (int i = 0; i < 6; i++) {
		free(res[i]);
	}

	return 0;
}
