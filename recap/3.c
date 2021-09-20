#include <stdio.h>
#include <pthread.h>

pthread_t t;
pthread_rwlock_t rwlock;

void* f(void* arg) {
	printf("Before first write lock\n");
	pthread_rwlock_wrlock(&rwlock);
	printf("After first write lock\n");
	pthread_rwlock_unlock(&rwlock);
	return NULL;
}

int main(int argc, char* argv[]) {
	if (pthread_rwlock_init(&rwlock, NULL) < 0) {
		printf("ERROR\n");
		return 1;
	}

	printf("Before first read lock\n");
	pthread_rwlock_rdlock(&rwlock);
	printf("After first read lock\n");

	printf("Before second read lock\n");
	pthread_rwlock_rdlock(&rwlock);
	printf("After second read lock\n");

	pthread_create(&t, NULL, f, NULL);

	printf("Before first unlock\n");
	pthread_rwlock_unlock(&rwlock);
	printf("After first unlock\n");
	pthread_rwlock_unlock(&rwlock);
	printf("After second unlock\n");

	pthread_join(t, NULL);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
