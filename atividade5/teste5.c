#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 6

void* funcaoDaThread(void* arg);

pthread_mutex_t mutex;

int var = 0;

int main(void){

	pthread_mutex_init(&mutex, NULL);
    pthread_t auto_ids[NUM_THREADS];
    int user_ids[NUM_THREADS];
    
    for(int i = 1; i <= NUM_THREADS; i++){
    	user_ids[i] = i;
    	pthread_create(&auto_ids[i], NULL, &funcaoDaThread, &user_ids[i]);
	}
	
	
	for(int i = 1; i <= NUM_THREADS; i++){
		pthread_join(auto_ids[i],NULL);
		printf("Main: Thread %d (%d) encerrada\n",user_ids[i], auto_ids[i]);
	}
	
	printf("Main: conteudo da secao critica: %d", var);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

void* funcaoDaThread(void* arg){
	int *id;
	
	id = (int*) arg;
	printf("Ola, eu sou a thread %d (%d) \n", *id, pthread_self());
	pthread_mutex_lock(&mutex);
	printf("Thread %d: Conteudo da secao critica (antes): %d\n", *id, var);
	var += *id;
	printf("Thread %d: Conteudo da secao critica (depois): %d\n", *id, var);
    pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
