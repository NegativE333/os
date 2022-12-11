#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t empty, full;
pthread_mutex_t mutex;
int buffer[5];
int count = 0;

void * producer(void *arg){
    long int num = (long int) arg;
    sem_wait(&empty);

    pthread_mutex_lock(&mutex);

    buffer[count] = rand()%10;
    printf("\n Producer no. %ld produced %d", num+1, buffer[count]);
    count++;
    sleep(1);

    pthread_mutex_unlock(&mutex);

    sem_post(&full);
    pthread_exit(NULL);
}

void consumer(void * arg){
    long int num = (long int) arg;

    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    count--;
    printf("\n Consumer no. %ld consumed %d", num+1, buffer[count]);
    sleep(1);

    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
    pthread_exit(NULL);
}

int main(){
    int np, nc;
    pthread_t p[10],c[10];

    unsigned long int i,j,k,l;
    printf("Enter the no. of producer and consumers: ");
    scanf("%d %d", $np, &nc);

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i<nc; i++){
        pthread_create(&c[i], NULL, consumer, (void *)i);
    }
    for(j = 0; j<np; j++){
        pthread_create(&p[j], NULL, producer, (void *)j);
    }
    for(k = 0; k<nc; k++){
        pthread_join(c[k], NULL);
    }
    for(l = 0; l<np; l++){
        pthread_join(p[l], NULL);
    }
    return 0;
}