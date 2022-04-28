#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>


#define TAMANHO_BUFFER 10

void* funcProdutor(void *arg);
void* funcConsumidor(void *arg);

int numThreadsConsumidoras;
int numThreadsProdutoras;

pthread_mutex_t mutex;
pthread_cond_t podeProduzir, podeConsumir;

int buffer = 0;

int main(int argc, char *argv[]){
	
	if((argc != 3) || (atoi(argv[1]) == 0) || (atoi(argv[2]) == 0)){
		printf("\nErro! Uso correto: nome_programa num_produtores ""(int > 0) num_consumidores (int > 0)\n\n");
		
	}else{
		
		pthread_t autoIdsProdutoras[numThreadsProdutoras];
		pthread_t autoIdsConsumidoras[numThreadsConsumidoras];
		int userIdsProdutoras[numThreadsProdutoras];
		int userIdsConsumidoras[numThreadsConsumidoras];
		
		pthread_mutex_init(&mutex, NULL);
		
		pthread_cond_init(&podeProduzir, NULL);
		pthread_cond_init(&podeConsumir, NULL);
		
		numThreadsProdutoras = atoi(argv[1]);
		numThreadsConsumidoras = atoi(argv[2]);
		
		printf("\nTamanho do buffer: %d\n", TAMANHO_BUFFER);
		printf("Estado inicial do buffer: %d\n\n", buffer);
		
		for(int i = 1; i <= numThreadsProdutoras; i++){
			userIdsProdutoras[i] = i;
			pthread_create(&autoIdsProdutoras[i], NULL, &funcConsumidor, &userIdsProdutoras[i]);
		}
		for(int i = 1; i <= numThreadsConsumidoras; i++){
			userIdsProdutoras[i] = i;
			pthread_create(&autoIdsConsumidoras[i], NULL, &funcProdutor, &userIdsConsumidoras[i]);
		}
		pthread_exit(NULL);
	}
}

void* funcProdutor(void *arg){
	
	printf("Ola da thread produtora %d (%d)\n", *(int*)arg, (int) pthread_self());
	
	while(1){
		pthread_mutex_lock(&mutex);
		
		while(buffer == TAMANHO_BUFFER){
			printf("Thread produtora %d bloqueada\n", *(int*)arg);
			pthread_cond_wait(&podeProduzir, &mutex);
		}
		
		buffer++;
		printf("Thread produtora %d (++) - (antes: %d, depois: ""%d)\n", *(int*) arg, buffer - 1, buffer);
		
		usleep(((unsigned int)rand() % 500) * 1000);
		
		pthread_cond_signal(&podeConsumir);
		
		pthread_mutex_unlock(&mutex);
	}
}

void* funcConsumidor(void *arg){
	
	printf("Ola da thread consumidora %d (%d)\n", *(int*)arg, (int) pthread_self());
	
	while(1){
		pthread_mutex_lock(&mutex);
		
		while(buffer == 0){
			printf("Thread consumidora %d bloqueada\n", *(int*)arg);
			pthread_cond_wait(&podeConsumir, &mutex);
		}
		
		buffer--;
		printf("Thread consumidora %d (--) - (antes: %d, depois: ""%d)\n", *(int*) arg, buffer + 1, buffer);
		
		usleep(((unsigned int)rand() % 500) * 1000);
		
		pthread_cond_signal(&podeConsumir);
		
		pthread_mutex_unlock(&mutex);
	}
}









