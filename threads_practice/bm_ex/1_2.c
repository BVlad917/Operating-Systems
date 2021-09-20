/* 1. La linia de comandă se dau n argumente despre care se presupune ca sunt numere întregi si pozitive. (n sa fie maxim 20, ca sa nu creati prea multe thread-uri).
 *     Pentru fiecare argument se va crea un nou thread care va verifica daca argumentul respectiv este un numar impar si va printa pe ecren un mesaj.
 *     */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nr[21];

void* f(void* arg) {
	int index = *((int*)arg);
	if (nr[index] % 2 == 0) {
		printf("The number %d is even.\n", nr[index]);
	}
	else {
		printf("The number %d is odd.\n", nr[index]);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	int indices[20];
	pthread_t t[20];
	for (int i = 1; i < argc; i++) {
		nr[i - 1] = atoi(argv[i]);
	}
	for (int i = 0; i < argc - 1; i++) {
		indices[i] = i;
		pthread_create(&t[i], NULL, f, (void*)&indices[i]);
	}
	for (int i = 0; i < argc - 1; i++) {
		pthread_join(t[i], NULL);
	}
	return 0;
}
