#include <pthread.h>
#include <stdio.h>

void* thread_function (void* thread_arg) {
	for(int i = 0; i < 10001; i++)	
		printf("o");
}

int main () {
	pthread_attr_t attr;
	pthread_t thread;
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
	pthread_create (&thread, &attr, &thread_function, NULL);
	pthread_attr_destroy (&attr);
	int candidate = 2;
	while (candidate < 1001) {
		int factor;
		int is_prime = 1;
		// Test primality by successive division.
		for (factor = 2; factor < candidate; ++factor)
			if (candidate % factor == 0) {
				is_prime = 0;
				break;
			}
		// Is this the prime number we’re looking for?
		++candidate;
		if(is_prime = 1){
			printf("%d", candidate);
		}
	}
	// No need to join the second thread.
	return 0;
}