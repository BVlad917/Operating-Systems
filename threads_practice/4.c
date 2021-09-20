#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* print_prime(void* arg) {
	int num = a[*((int*)arg)];
	printf("%d\n", num);
	free((int*)arg);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t t[10];
	int indices[10];

	for (int i = 0; i < 10; i++) {
		int* s = (int*)malloc(sizeof(int));
		*s = i;
		pthread_create(&t[i], NULL, print_prime, (void*)s);
	}

	for (int i = 0; i < 10; i++) {
		pthread_join(t[i], NULL);
	}

	return 0;
}
