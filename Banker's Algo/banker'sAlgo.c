#include <stdio.h>
int n, m, i, j, k;
int alloc[10][10];
int max[10][10];
int need[10][10];
int avail[10];

void display_matrix(int matrix[10][10]){
	int i,j;
	for(i=0;i<n;i++){
		printf("\n P%d ",i);
		for(j=0;j<m;j++){
			printf(" %d", matrix[i][j]);
		}
	}
}

void cal_need(){
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<m;j++){
		need[i][j] = max[i][j] - alloc[i][j];
	}
}

void banker(){
	int i,j,k=0,flag;
	int finish[10],safe_seq[10];
	for(i=0;i<n;i++){
		finish[i]=0;
	}
	for(i=0;i<n;i++){
		flag=0;
		if(finish[i] == 0){
			for(j=0;j<m;j++){
				if(need[i][j]>avail[j]){
					flag=1;
					break;
				}
			}
			if(flag==0){
				finish[i]=1;
				safe_seq[k]=i;
				k++;
				for(j=0;j<m;j++)
					avail[j] += alloc[i][j];
				i=-1;
			}
		}
	}
	flag=0;
	for(i=0;i<n;i++){
		if(finish[i]==0){
			printf("The system is in deadlock");
			flag=1;
			break;
		}
	}
		if(flag==0){
		printf("The system is in safe state and\n");
		printf("the safe sequence is: ");
		for(i=0;i<n;i++)
			printf("P%d ", safe_seq[i]);
		
		}
}

int main(){
	
	printf("Enter the no. of process: ");
	scanf("%d", &n);
	printf("Enter thr no. of resources: ");
	scanf("%d", &m);
	printf("Enter initial allocation matrix:\n");
	for(int i = 0; i<n; i++){
		for(int j = 0; j<m; j++){
			scanf("%d", &alloc[i][j]);
		}
	}
	
	printf("Enter max req matrix:\n");
	for(int i = 0; i<n; i++){
		for(int j = 0; j<m; j++){
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("Enter the available resources: ");
	for(int i = 0; i<m; i++){
		scanf("%d", &avail[i]);
	}
	
	printf("The elements in alloc matrix are : \n");
	display_matrix(alloc);
	
	printf("\n");
	
	printf("The elements in max matrix are : \n");
	display_matrix(max);
	
	printf("\n");
	
	printf("The elements in available matrix are: \n");
	for(int i = 0; i<m; i++){
		printf("%d", avail[i]);
	}
	
	cal_need();
	printf("\n\n\nNeed is \n");
	display_matrix(need);
	
	printf("\n\n\n");
	
	banker();
	
	return (0);
}






