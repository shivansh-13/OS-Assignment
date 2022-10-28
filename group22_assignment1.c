#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
int N;
int FLAG;
int cX[]={ 2, 1, -1, -2, -2, -1,  1,  2 };
int cY[]={-1, 2, -2,  1, -1,  2, -2,  1 };

struct pair{
	short x;
	short y;
};
struct history{
	int i;
	int N;
	bool visited[50*50];
	struct pair path[50*50];
};

void print_path(struct pair path[],int k){
	for(int i=0;i<k;i++)
	{
		printf("%d,%d|",path[i].x,path[i].y);
	}
	printf("\n");
	fflush(stdout);
}
void  * solver(void * args)
{
	struct history * curr = (struct history *) args;
	int currI= curr->i;
	int currX=curr->path[currI].x;
	int currY=curr->path[currI].y;
	// unsigned long currVX=curr->visitedX;
	// unsigned long currVY=curr->visitedY;
	struct pair currP[50*50];
	bool currV[50*50];
	memcpy(currV,curr->visited,sizeof(curr->visited));
	memcpy(currP,curr->path,sizeof(curr->path));
	//printf("%d %ld %ld\n",currI,currVX,currVY);
	//print_path(currP,currI+1);
	//printf("\n");
	fflush(stdout);
	if(currI==(N*N-1)){
		FLAG=1;
		//printf("DONE\n");
		print_path(currP,N*N);
		fflush(stdout);
		free(curr);
		pthread_exit(NULL);
	}
	
	pthread_t ids[]= {-1,-1,-1,-1,-1,-1,-1,-1};
	if(FLAG)
	{
		free(curr);
		//printf("DONEHVSD");
		pthread_exit(NULL);
	}
	for(int p=0;p<8;p++)
	{
		int X=currX+cX[p];
		int Y=currY+cY[p];
		//int mask1=1<<X;
		//int mask2=1<<Y;
		
		if(X<N && X>-1 && Y>-1 && Y<N){
			if(currV[X+N*Y]) continue;
			struct history *temp=(struct history *)malloc(sizeof(struct history));
			struct pair currXY;
			//temp->visitedX=currVX^mask1;
			//temp->visitedY=currVY^mask2;
			currXY.x=X;
			currXY.y=Y;
			//printf("going %d,%d from %d,%d\n",X,Y,currX,currY);
			fflush(stdout);
			temp->i=currI+1;
			memcpy(temp->path,currP,sizeof(currP));
			memcpy(temp->visited,currV,sizeof(currV));
			temp->path[currI+1]=currXY;
			temp->visited[X+N*Y]=1;
			void * t=(void *)temp;
			pthread_create(&ids[p],NULL,solver,t);
		}
		for(int p=0;p<8;p++){
			if(ids[p]!=-1)
				pthread_join(ids[p],NULL);
		}
	}
	free(curr);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: ./Knight.out grid_size StartX StartY");
		exit(-1);
	}
	N = atoi(argv[1]);
	int startX=atoi(argv[2]);
	int startY=atoi(argv[3]);
	int path[2*N*N]; // Declared the path array
	

	
	/* Do your thing here */
	struct history *t=(struct history *)malloc(sizeof(struct history));
	struct pair temp;
//	printf("HEYY\n");
	fflush(stdout);
	temp.x=startX;
	temp.y=startY;
	t->path[0].x=0;
	t->path[0].x=temp.x;
	t->path[0].y=temp.y;
	t->i=0;
	for(int i = 0; i < 50*50; i++) {
    		t->visited[i] = 0; // Path array initialise to -1;
	}
	//struct pair arr[N*N];
	//t->visitedX=1<<startX;
	//t->visitedY=1<<startY;
//	printf("HEYY2\n");
	//t->path=arr;
	t->visited[startX+N*startY]=1;
	fflush(stdout);
	solver((void *)t);
	if(FLAG==0)
	{
		printf("No Possible Tour");
	}
	return 0;
}
