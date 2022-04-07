#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_message_function(void *ptr);

int main(void){

	pthread_t thread1, thread2;

	char *message1 = "Hello World Thread1...";
	char *message2 = "Hello World Thread2...";

	pthread_create (&thread1, NULL, (void*) print_message_function, (void*) message1);

	pthread_create (&thread2, NULL, (void*) print_message_function, (void*) message2);


	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	exit(0);
}

void print_message_function(void *ptr){

	char *message;
	message = (char *) ptr;
	printf("%s \n", message);

}

