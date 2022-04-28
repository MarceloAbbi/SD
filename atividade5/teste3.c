#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 2

void* funcaoDaThread(void* arg);

int main(void){

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
    
    return 0;
}

void* funcaoDaThread(void* arg){
	int *id;
	
	id = (int*) arg;
	printf("Ola, eu sou a thread %d (%d) \n", *id, pthread_self());
    pthread_exit(NULL);
}
