#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t empty,full;
pthread_mutex_t mutex;
int buffer[5];
int count = 0;

void *producer(void *arg){
	
	long int num =(long int) arg;
	
	//Producer is trying to produce data
	sem_wait(&empty);
	//Prodecer is allowed to produce data
	//Producer is waiting for his turn
	pthread_mutex_lock(&mutex);
	
	//Producer is producing a data;
	buffer[count]=rand()%10;
	printf("\n Producer : %ld produced : %d", num+1, buffer[count]);
	count++;
	sleep(1);
	
	//Producer have released lock on critical section.
	pthread_mutex_unlock(&mutex);
	
	//Poducer is incrementing full value
	sem_post(&full);
	pthread_exit(NULL);
}

void *consumer(void *arg){
	long int num =(long int) arg;
	
	//Consumer is trying to consume data
	sem_wait(&full);
	//Consumer is allowed to consume data
	//Consumer is waiting for his turn
	pthread_mutex_lock(&mutex);
	
	//Consumer is consumeing a data;
	count--;
	printf("\n Consumer : %ld consumed : %d", num+1, buffer[count]);
	sleep(1);
	
	//Consumer have released lock on critical section.
	pthread_mutex_unlock(&mutex);
	
	//Consumer is incrementing empty value
	sem_post(&empty);
	pthread_exit(NULL);
}



int main(){
	int np,nc;
	pthread_t p[10],c[10];
	
	unsigned long int i,j,k,l;
	//Read no. of producers and no. of consumers.
	printf("Enter the no. of producers and consumers: ");
	scanf("%d %d", &np, &nc);
	
	//initialise the semaohore variables.
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	
	//Declaration of mutex
	pthread_mutex_init(&mutex,NULL);
	
	//create producer threads
	for(i=0;i<np;i++){
		pthread_create(&p[i],NULL, producer,(void *)i);
	}
	
	//create consumer threads
	for(j=0;j<nc;j++){
		pthread_create(&c[j],NULL, consumer,(void *)j);
	}
	
	//Join producer threads
	for(k=0;k<np;k++){
		pthread_join(p[k],NULL);
	}
	
	//Join consumer therads
	for(l=0;l<nc;l++){
		pthread_join(c[l],NULL);
	}
	
	
}
