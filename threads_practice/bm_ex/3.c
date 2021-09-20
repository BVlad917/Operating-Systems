/*
 * 3. Scrieti un program care face suma elementelor dintr-un vector de numere intregi folosind P thread-uri.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;
int a[100];
pthread_mutex_t m;

void* f(void* f) {
	int* index = (int*)f;
	pthread_mutex_lock(&m);
	sum += a[*index];
	pthread_mutex_unlock(&m);
	free(index);
	return NULL;
}

int main(int argc, char* argv[]) {
	int p, i;
	pthread_t t[100];
	printf("Give the number of elements: ");
	scanf("%d", &p);
	printf("Give the %d elements:\n", p);
	for (i = 0; i < p; i++) {
		scanf("%d", &a[i]);
	}
	pthread_mutex_init(&m, NULL);
	
	for (i = 0; i < p; i++) {
		int* index = (int*)malloc(sizeof(int));
		*index = i;
		pthread_create(&t[i], NULL, f, (void*)index);
	}

	for (i = 0; i < p; i++) {
		pthread_join(t[i], NULL);
	}

	pthread_mutex_destroy(&m);
	printf("The sum is %d\n", sum);

	return 0;
}
