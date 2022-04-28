#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	double *a;
	double *b;
	double sum;
	int veclen;
}Estrutura;

#define NUMTHRDS 4
#define VECLEN 100000

Estrutura dados;
pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexsum;
void *geraProdutoVetores(void *arg);

int main(int argc, char *argv[]){
    long i;
    double *a, *b;
    void *status;
    pthread_attr_t attr;

    a = (double*) malloc (NUMTHRDS * VECLEN * sizeof(double));
    b = (double*) malloc (NUMTHRDS * VECLEN * sizeof(double));

    for(i = 0; i < VECLEN * NUMTHRDS; i++){
        a[i]=1;
        b[i]=a[i];
    }
    
    dados.veclen = VECLEN;
    dados.a = a;
    dados.b = b;
    dados.sum = 0;
    
    pthread_mutex_init(&mutexsum, NULL);
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i = 0; i < NUMTHRDS; i++){
    	pthread_join(callThd[i], &status);
	}
	printf("Sum = %f \n", dados.sum);
	free (a);
	free (b);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}

void *geraProdutoVetores(void *arg){
	int i, start, end, len;
	long offset;
	double mysum, *x, *y;
	offset = (long) arg;
	len = dados.veclen;
	start = offset * len;
	end = start + len;
	x = dados.a;
	y = dados.b;
	
	mysum = 0;
	
	for(i = start; i < end; i++){
		mysum += (x[i] * y[i]);
	}
	pthread_mutex_lock (&mutexsum);
	dados.sum += mysum;
	printf("Thread %ld did %d to %d: mysum = %f global sum = %f\n", offset, start, end, mysum, dados.sum);
	pthread_mutex_unlock (&mutexsum);
	pthread_exit(NULL);
}
