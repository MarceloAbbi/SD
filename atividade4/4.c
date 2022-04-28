#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *imprimeOla(void *param);

int main(void){
	pthread_t threads;
	int rc;
	char *mensagem1 = "teste"; //ou char mensagem1[] = "teste"...
	printf("Main-> criando thread e enviando a mensagem: %s\n", mensagem1);
	rc = pthread_create(&threads, NULL, imprimeOla, mensagem1);
	if(rc){
		printf("Error! Return code from pthread_create() is %d.\n", rc);
		exit(-1);
	}
	pthread_exit(NULL);
}

void *imprimeOla (void *param){
	char *msgm;
	msgm = (char*) param;
	printf("Thread Criada! Mensagem recebida: %s\n", msgm);
	pthread_exit(NULL);
}
