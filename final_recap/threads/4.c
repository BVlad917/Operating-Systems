#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS_NUM 5

int n;
int* a;
int* b;
int* c;

struct interval {
	int start;
	int end;
};

void* f(void* arg) {
	struct interval* interv = (struct interval*)arg;

	for (int i = interv->start; i < interv->end; i++) {
		c[i] = a[i] + b[i];
	}

	free(interv);
	return NULL;
}

int main(int argc, char* argv[]) {
	int start = 0, end = 0, chunk_size, remainder;
	pthread_t thrds[THREADS_NUM];
	
	printf("How many numbers: ");
	scanf("%d", &n);

	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);
	c = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		printf("a[%d]: ", i);
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		printf("b[%d]: ", i);
		scanf("%d", &b[i]);
	}

	chunk_size = n / THREADS_NUM;
	remainder = n % THREADS_NUM;

	for (int i = 0; i < THREADS_NUM; i++) {
		end = start + chunk_size;
		if (remainder > 0) {
			end += 1;
			remainder -= 1;
		}
		
		struct interval* interv = (struct interval*) malloc(sizeof(struct interval));
		interv->start = start;
		interv->end = end;
		pthread_create(&thrds[i], NULL, f, (void*)interv); 

		start = end;
	}

	for (int i = 0; i < THREADS_NUM; i++) {
		pthread_join(thrds[i], NULL);
	}

	for (int i = 0; i < n; i++) {
		printf("c[%d] = %d\n", i, c[i]);
	}

	free(a);
	free(b);
	free(c);

	return 0;
}
