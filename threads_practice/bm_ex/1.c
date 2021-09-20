/* 1. La linia de comandă se dau n argumente despre care se presupune ca sunt numere întregi si pozitive. (n sa fie maxim 20, ca sa nu creati prea multe thread-uri).
    Pentru fiecare argument se va crea un nou thread care va verifica daca argumentul respectiv este un numar impar si va printa pe ecren un mesaj.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* f(void* arg) {
	int nr = *((int*)arg);
	if (nr % 2 == 0) {
		printf("The number %d is even.\n", nr);
	}
	else {
		printf("The number %d is odd.\n", nr);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	int nrs[21];
	pthread_t t[21];
	if (argc < 2) {
		perror("No arguments given.\n");
		return 1;
	}
	if (argc > 20) {
		perror("Easy, now.\n");
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		nrs[i - 1] = atoi(argv[i]);
	}
	for (int i = 0; i < argc - 1; i++) {
		pthread_create(&t[i], NULL, f, (void*)&nrs[i]);
	}
	for (int i = 0; i < argc - 1; i++) {
		pthread_join(t[i], NULL);
	}
	return 0;
}
