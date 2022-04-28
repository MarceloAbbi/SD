#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* funcaoDaThread(void* arg);
int main(void){

    pthread_t thid;
    
    pthread_create(&thid, NULL, &funcaoDaThread, NULL);
    printf("Main(): Thread %d criada!\n",(int)thid); 

	
    pthread_create(&thid, NULL, &funcaoDaThread, NULL);
    printf("Main(): Thread %d criada!\n",(int)thid); 

    printf("Main(): Ultimo valor de thid: %d. Eh sempre o da ultima thread criada se não usar vetor de IDs\n",(int)thid);

    pthread_exit(NULL);
    
    return 0;
}

void* funcaoDaThread(void* arg){
    printf("Olá, eu sou a thread %d\n",(int)pthread_self());
    pthread_exit(NULL);
}
