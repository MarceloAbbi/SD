#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *imprimeOla(void *param);

int main(void){
    pthread_t thid;
    int rc;
    rc = pthread_create(&thid, NULL, imprimeOla, NULL);
    if (rc){
        printf("Error! Return code from pthread_create( is %d.\n", rc);
        exit(-1);
    }
    printf("Main(): criada thread %d\n", (int) thid);
    pthread_join(thid, NULL);
    printf("Main(): A thread %d ja terminou.\n", (int) thid);
    pthread_exit(NULL);
}

void *imprimeOla (void *param){
    printf("Ola! Eu sou a thread %d\n", (int) pthread_self());
    pthread_exit(NULL);
}
