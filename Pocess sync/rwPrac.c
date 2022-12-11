#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t wr, mutex;
int a = 10;
int readcount = 0;

void * reader(int * arg){
    long int num;
    num = (long int) arg;
    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);

    if(readcount == 1){
        pthread_mutex_lock(&wr);
    }

    printf("Reader no. %ld is in critical section and reading data %d", num, a);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);

    if(readcount == 0){
        pthread_mutex_unlock(&wr);
    }

    printf("Reader no. %ld has left the critical section.", num);

}


void * writer(int * arg){
    long int num;
    num = (long int) arg;

    pthread_mutex_lock(&wr);
    printf("Writer no. %ld is in critical section and written data has %d", num, a++);
    sleep(1);
    pthread_mutex_unlock(&wr);
    printf("Writer no. %ld has left the critical section.", num);
}


int main(){
    pthread_t r[10], w[10];
    long int i,j;
    int nor, now;

    pthread_mutex_init(&wr, NULL);
    pthread_mutex_init(&mutex, NULL);

    printf("Enter the no. of readers and writers: ");
    scanf("%d %d", &nor, &now);

    for(i=0; i<nor; i++){
        pthread_create(&r[i], NULL, reader, (void *)i);
    }

    for(j = 0; j<now; j++){
        pthread_create(&w[j], NULL, writer, (void *)j);
    }

    for(i=0; i<nor; i++){
        pthread_join(&r[i], NULL);
    }

    for(j=0; j<now; j++){
        pthread_join(&w[j], NULL);
    }

    return 0;
}