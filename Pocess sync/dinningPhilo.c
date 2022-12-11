#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t chop[5];
sem_t mutex;
char status[6] = {'-','-','-','-','-'};

void printStatus(){
	printf("\n");
	for(int i = 0;i<5;i++){
		printf("   %c", status[i]);
	}
}

void *Philosopher(void * arg){
	long int num = (long int) arg;
	//philosopher is hungry
	status[num]='H';
	printStatus();
	//Aquire the left and right chop
	
	//Lock the critical section
	sem_wait(&mutex);
	sem_wait(&chop[num]);
	sleep(1);
	sem_wait(&chop[(num+1)%5]);
	
	
	//Philosopher is eating
	status[num]='E';
	printStatus();
	sleep(1);
	
	//Release the chop
	sem_post(&chop[(num+1)%5]);
	sem_post(&chop[num]);
	
	//unlock the critical section
	sem_post(&mutex);
	
	//Philosopher is thinking
	status[num]='T';
	printStatus();
	pthread_exit(NULL);
}


int main(){
	pthread_t phil[5];
	long int i,j;
	
	//initilazinze semaphore
	for (i=0;i<5;i++){
		sem_init(&chop[i],0,1);
	}
	
	sem_init(&mutex,0,1);
	
	//Pinting heading of tabel
	printf("\n");
	for(int i = 0;i<5;i++){
		printf(" P[%ld]", i);
	}
	
	//Create threads of philosopher
	for(i=0;i<5;i++){
		pthread_create(&phil[i],NULL,Philosopher,(void *)i);
	}
	
	//Joining threads
	for(j=0;j<5;j++){
		pthread_join(phil[j],NULL);
	}
}
