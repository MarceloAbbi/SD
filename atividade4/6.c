#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 8
void *PrintHello(void *threadarg);
char *messages[NUM_THREADS];

typedef struct {
    int thread_id;
    int sum;
    char *message;
}thread_data;

thread_data thread_data_array[NUM_THREADS];

int main(int argc, char *argv[]){
    pthread_t threads[NUM_THREADS];

    int rc, t, sum;

    sum = 0;
    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo!";
    messages[3] = "Portuguese: Ola, Mundo!";
    messages[4] = "German: Guten Tag, Welt!";
    messages[5] = "Russian: Zdravstvytye, mir!";
    messages[6] = "Japanese: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";

    for(t = 0; t < NUM_THREADS; t++) {
        sum = sum + t;
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        thread_data_array[t].message = messages[t];
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, &thread_data_array[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

void *PrintHello(void *threadarg){
    thread_data *my_data;
    sleep(1);
    my_data = (thread_data *) threadarg;
    printf("Thread %d: %s Sum=%d\n", my_data->thread_id, my_data->message, my_data->sum);
    pthread_exit(NULL);
}
