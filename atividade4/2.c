#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 //Define o número de threads

void *imprimeOla(void *param); //Protótipo da função da thread...

int main(int argc, char *argv[]){ //Função main()...
	pthread_t threads[NUM_THREADS];
	int i;
	int rc;
	
	for(int i = 0; i < NUM_THREADS; i++){
		printf("Funcao main() criando a thread %d.\n", i);
		rc = pthread_create(&threads[i], NULL, imprimeOla, &i);
		if (rc){
			printf("Error! Return code from pthread_create() is %d.\n", rc);
			exit(-1); //stdlib.h
		}
	}
	pthread_exit(NULL); //Ultima acao da thread...
}

void *imprimeOla(void *param){
	int *id;
	id = (int*) param;
	printf("Ola! eu sou a thread %d!.\n", *id);
	pthread_exit(NULL);
}
