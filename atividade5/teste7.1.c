#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int num_Repeticoes;
static int counter = 0;

static void *funcao_incrementa(void* arg);
static void *funcao_decrementa(void* arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){
	int num_Threads, i;
	
	if((argc != 3) || (atoi(argv[1]) % 2 != 0)){
		printf("\nErro! Uso correto: nome_programa num_Threads " "(int par) num_repeticoes_de_cada_thread (int <=1000 \n\n)");
	}else{
		num_Threads = atoi(argv[1]);
		num_Repeticoes = atoi(argv[2]);
		pthread_t threads[num_Threads];
		int threadsIds[num_Threads];
		
		printf("Valor de counter eh: %d\n", counter);
		printf("Thread principal iniciando criacao das threads...\n");
		
		for(i = 0; i < num_Threads;i++){
			threadsIds[i] = i;
		}
		
		for(i = 0; i < num_Threads; i +=2){
			pthread_create(&threads[i], NULL, funcao_incrementa, &threadsIds[i]);
			pthread_create(&threads[i + 1], NULL, funcao_decrementa, &threadsIds[i + 1]);
		}
		
		printf("Thread principal a esperar a terminacao das threads criadas.\n");
		for(i = 0; i < num_Threads; i++){
			pthread_join(threads[i], NULL);
		}
		
		printf("Valor de counter eh: %d\n", counter);
		printf("Thread principal encerrada.\n");
		pthread_exit(NULL);
	}
}

static void *funcao_incrementa(void* arg){
	int *id;
	id = (int*) arg;
	for(int i = 0; i < num_Repeticoes; i++){
		pthread_mutex_lock(&mutex);
		printf("Thread %d (++) repeticao %d -> counter antes (%d) | counter ""Depois ++ = %d\n", *id, i + 1, counter, counter +=1);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

static void *funcao_decrementa(void* arg){
	int *id;
	id = (int*) arg;
	pthread_mutex_lock(&mutex);
	for(int i = 0; i < num_Repeticoes; i++){
		printf("Thread %d (--) repeticao %d -> counter antes (%d) | counter ""Depois -- = %d\n", *id, i + 1, counter, counter -=1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

