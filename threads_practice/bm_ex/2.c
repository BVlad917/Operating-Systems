/*
 * 2. Scrieti un program care face suma a 2 vectori de numere intregi folosind P thread-uri.
 */

#include <stdio.h>
#include <pthread.h>

int a[100], b[100], s[100];

void* f(void* arg) {
	int index = *((int*)arg);
	s[index] = a[index] + b[index];
	return NULL;
}

int main(int argc, char* argv[]) {
	int p, i, indices[100];
	pthread_t t[100];
	printf("How many numbers will the vectors have: ");
	scanf("%d", &p);
	printf("Give the %d numbers of a:\n", p);
	for (i = 0; i < p; i++) {
		scanf("%d", &a[i]);
	}
	printf("Give the %d numbers of b:\n", p);
	for (i = 0; i < p; i++) {
		scanf("%d", &b[i]);
	}
	for (i = 0; i < p; i++) {
		indices[i] = i;
		pthread_create(&t[i], NULL, f, (void*)&indices[i]);
	}
	for (i=0; i < p; i++) {
		pthread_join(t[i], NULL);
	}
	printf("The sum vector is:\n");
	for (i = 0; i < p; i++) {
		printf("%d ", s[i]);
	}
	printf("\n");
	return 0;
}
