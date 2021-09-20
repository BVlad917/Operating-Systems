#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int multiples_7[100];
int n1 = 0;
int not_multiples_7[100];
int n2 = 0;
char strings[100][100];
int n3 = 0;

pthread_mutex_t mtx_for_sevens, mtx_for_not_sevens, mtx_for_strings;
sem_t semaphore;

struct obj {
	int num;
	char str[100];
};

void* f(void* arg) {
	sem_wait(&semaphore);
	sleep(2);

	struct obj* new_obj = (struct obj*)arg;

	if (new_obj->num % 7 == 0) {
		pthread_mutex_lock(&mtx_for_sevens);
		multiples_7[n1++] = new_obj->num;
		pthread_mutex_unlock(&mtx_for_sevens);

	} else {
		pthread_mutex_lock(&mtx_for_not_sevens);
		not_multiples_7[n2++] = new_obj->num;
		pthread_mutex_unlock(&mtx_for_not_sevens);
	}
	pthread_mutex_lock(&mtx_for_strings);
	strcpy(strings[n3++], new_obj->str);
	pthread_mutex_unlock(&mtx_for_strings);
	sem_post(&semaphore);

	return NULL;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid arguments.\n");
		return 1;
	}

	struct obj objects[100];
	pthread_t* thrds;
	int n = atoi(argv[1]);
	thrds = (pthread_t*) malloc(sizeof(pthread_t) * n);


	for (int i = 0; i < n; i++) {
		printf("Give number for thread %d: ", i + 1);
		scanf("%d", &objects[i].num);
		printf("Give string for thread %d: ", i + 1);
		scanf("%s", objects[i].str);
	}

	pthread_mutex_init(&mtx_for_sevens, NULL);
	pthread_mutex_init(&mtx_for_not_sevens, NULL);
	pthread_mutex_init(&mtx_for_strings, NULL);
	sem_init(&semaphore, 0, 4);
	for (int i = 0; i < n; i++) {
		pthread_create(&thrds[i], NULL, f, (void*)&objects[i]);
	}

	for (int i = 0; i < n; i++) {
		pthread_join(thrds[i], NULL);
	}
	pthread_mutex_destroy(&mtx_for_sevens);
	pthread_mutex_destroy(&mtx_for_not_sevens);
	pthread_mutex_destroy(&mtx_for_strings);
	sem_destroy(&semaphore);

	free(thrds);

	printf("Multiples of 7: ");
		for (int i = 0; i < n1; i++) {
			printf("%d ", multiples_7[i]);
		}
	printf("\n");

	printf("Non-multiples of 7: ");
	for (int i = 0; i < n2; i++) {
		printf("%d ", not_multiples_7[i]);
	}
	printf("\n");

	printf("Strings: ");
	for (int i = 0; i < n3; i++) {
		printf("%s ", strings[i]);
	}
	printf("\n");

	return 0;
}
