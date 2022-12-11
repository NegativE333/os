#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t wr, mutex;

int a = 10;
int readcount = 0;

void * reader(void *arg){
	long int num;
	num=(long int) arg;
	pthread_mutex_lock(&mutex);
	readcount++;
	pthread_mutex_unlock(&mutex);
	
	if(readcount == 1){
		pthread_mutex_lock(&wr);
	}
	
	printf("\n Reader %ld is in critical section", num);
	printf("\n Reader %ld is reading data %d", num, a);
	sleep(1);
	
	pthread_mutex_lock(&mutex);
	readcount--;
	pthread_mutex_unlock(&mutex);
	if(readcount==0){
		pthread_mutex_unlock(&wr);
	}
	
	printf("\n Reader %ld has left critical section.", num);
}

void * writer(void * arg){
	long int num;
	num = (long int) arg;
	
	//lock wr variable to enter critical section.
	pthread_mutex_lock(&wr);
	printf("\n Writer %ld is in critical section.", num);
	printf("\n Writer %ld have written data as %d", num, ++a);
	sleep(1);
	//writter releases lock
	pthread_mutex_unlock(&wr);
	printf("\n Writter %ld has left the critical section.", num);
}

int main(){
	pthread_t r[10],w[10];
	long int i,j;
	int nor, now;
	
	pthread_mutex_init(&wr, NULL);
	pthread_mutex_init(&mutex, NULL);
	
	printf("Enter no. of readers and writer: ");
	scanf("%d %d", &nor, &now);
	
	//creating reader and writer thread.
	for(i=0; i<nor;i++){
		pthread_create(&r[i], NULL, reader, (void *)i);
	}
	
	for(j=0; j<now;j++){
		pthread_create(&w[j], NULL, writer, (void *)j);
	}
	
	//joining the threads.
	for(i=0; i<nor;i++){
		pthread_join(r[i], NULL);
	}
	for(j=0; j<now;j++){
		pthread_join(w[j], NULL);
	}
	
	return 0;
}
