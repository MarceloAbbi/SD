#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *imprimeOla(void *param);

typedef struct{
	char *nome;
	int idade;
	char sexo;
}funcionario;

int main(void){
	pthread_t threads;
	int rc;
	
	funcionario structFuncionario; //Declarando struct;
	structFuncionario.nome = "Leonardo Amaral"; //Inicializando struct;
	structFuncionario.idade = 44;
	structFuncionario.sexo = 'M';
	
	printf("Main-> criando a thread e enviando mensagem!\n");
	rc = pthread_create(&threads, NULL, imprimeOla, &structFuncionario);
	if(rc){
		printf("Error! return code from pthread_create() is %d.\n", rc);
		exit(-1);
	}
	pthread_exit(NULL);
}

void *imprimeOla(void *param){
	funcionario *msgm;
	msgm = (funcionario *) param;
	printf("Thread criada! Mensagem recebida: \n%s\n%d\n%c\n", msgm->nome, msgm->idade, msgm->sexo);
	pthread_exit(NULL);
}
