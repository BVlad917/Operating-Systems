#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
pthread_mutex_t m;

void* fa(void* arg) {
	int start = *((int*)arg);
	int* sum = (int*)malloc(sizeof(int));
	*sum = 0;
	for (int i = start; i < start + 5; i++) {
		*sum += a[i];
	}
	return (void*)sum;
}

void* fb(void* arg) {
	int start = *((int*)arg);
	int* sum = (int*)malloc(sizeof(int));
	*sum = 0;
	for (int i = 0; i < start + 5; i++) {
		*sum += a[i];
	}
	return (void*)sum;
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	int sum = 0;
	int start_fa = 0, start_fb = start_fa + 5;
	int* result_a;
	int* result_b;

	pthread_create(&t1, NULL, fa, (void*) &start_fa);
	pthread_create(&t2, NULL, fa, (void*) &start_fb);

	pthread_join(t1, (void*)&result_a);
	pthread_join(t2, (void*)&result_b);

	sum = *(result_a) + *(result_b);	

	free(result_a);
	free(result_b);

	printf("The sum of the array is %d\n", sum);

	return 0;
}
