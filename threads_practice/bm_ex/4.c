/*
 * 4. La linia de comandă se dau n argumente, primul va fi consider un string iar urmatoarele N-1 vor fi considerate substringuri ce pot sa apara in stringul initial. (n sa fie maxim 20, ca sa nu creati prea multe thread-uri). 
         Pentru fiecare substring se va crea un nou thread care va verifica daca substringul respectiv apare in stringul principal si va incrementa o variabila globala. La sfarsit programul principal va face printa aceasta variabila globala.
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>

char* main_string;
int count = 0;
pthread_mutex_t m;

void* f(void* arg) {
	char* str = (char*)arg;
	if (strstr(main_string, str) != NULL) {
		pthread_mutex_lock(&m);
		count++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	int i;
	pthread_t t[20];
	if (argc > 20) {
		printf("Easy, now.\n");
		return 1;
	}

	main_string = argv[1];
	pthread_mutex_init(&m, NULL);
	
	for (i = 2; i < argc; i++) {
		pthread_create(&t[i - 2], NULL, f, (void*)argv[i]);	
	}

	for (i = 2; i < argc; i++) {
		pthread_join(t[i - 2], NULL);
	}

	pthread_mutex_destroy(&m);
	printf("The count is: %d\n", count);
	return 0;
}
