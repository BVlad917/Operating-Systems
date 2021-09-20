#include <stdio.h>
#include <pthread.h>

int sum = 0;
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
pthread_mutex_t m;

void* f(void* arg) {
	int start_index = *((int*) arg);
	for (int i = start_index; i < start_index + 5; i++) {
		pthread_mutex_lock(&m);
		sum += a[i];
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	int start_t1 = 0, start_t2 = start_t1 + 5;
	pthread_mutex_init(&m, NULL);

	pthread_create(&t1, NULL, f, (void*) &start_t1);
	pthread_create(&t2, NULL, f, (void*) &start_t2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&m);

	printf("The sum is %d\n", sum);

	return 0;
}
