#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define THREADS_NUM 5

pthread_t threads[THREADS_NUM];
int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int b[8] = {9, 10, 11, 12, 13, 14, 15, 16};
int c[8] = {0};

struct interval {
	int start;
	int end;
};

void* f(void* arg) {
	struct interval* interv = (struct interval*)arg;

	for (int i = interv->start; i < interv->end; i++) {
		c[i] = a[i] + b[i];
		printf("%d\n", i);
	}

	free(interv);
	return NULL;
}

int main(int argc, char* argv[]) {
	int start = 0, end = 0;
	int remainder = 8 % 5;
	int chunk_size = 8 / 5;
	for (int i = 0; i < THREADS_NUM; i++) {
		end = start + chunk_size;
		if (remainder > 0) {
			end++;
			remainder--;
		}
		//printf("Start: %d; End: %d\n", start, end);
		
		struct interval* new_interval = (struct interval*) malloc(sizeof(struct interval));
		new_interval->start = start;
		new_interval->end = end;

		pthread_create(&threads[i], NULL, f, (void*)new_interval);
		start = end;
	}

	for (int i = 0; i < THREADS_NUM; i++) {
		pthread_join(threads[i], NULL);
	}

	for (int i = 0; i < 8; i++) {
		printf("c[%d] = %d\n", i, c[i]);
	}

	return 0;
}
