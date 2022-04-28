#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5 //Define o numero de threads...

void *imprimeOla (void *param); //Prototipo da funcao da thread...

int main(int argc, char *argv[]){
	pthread_t threads [NUM_THREADS];
	int vetIDs[NUM_THREADS];
	int rc;
	for(int i = 0; i < NUM_THREADS; i++){
		vetIDs[i] = i;
		printf("Funcao main() criando a thread %d.\n", i);
		rc = pthread_create(&threads[i], NULL, imprimeOla, &vetIDs[i]);
		if (rc){
			printf("Error! Return code from pthread_create() is %d.\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}

void *imprimeOla(void *param){
	int *id;
	id = (int*) param;
	printf("Ola! eu sou a thread %d.\n", *id);
	pthread_exit(NULL);
}

