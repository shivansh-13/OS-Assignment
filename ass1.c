/* Do not make any changes in the skeleton. Your submission will be invalidated if the skeleton is changed */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
// can be made local if required yes its local
int N;

// Helper struct, can utilize any other custom structs if needed 
typedef struct{
	int x,y,N;
	int path[2*N*N];
} pair;

// { 2, 1, -1, -2, -2, -1, 1, 2 };
// { 1, 2, 2, 1, -1, -2, -2, -1 };
int *function(void *arg){
	pthread_t thread_id;
	//Add x,y in path 
	if(x+2<N && y+1<N){
		//check if x+2 and y+1 isnt in thepath already .
		pthread_create(&thread_id, NULL, function, x+2, y+1, N, path);
		//pthread_join(&thread_id,NULL);
	}
	if(x+1<N && y+2<N){
		pthread_create(&thread_id, NULL, function, x+1, y+2, N, path);
	}
	if(x-1>=0 && y+2<N){
		pthread_create(&thread_id, NULL, function, x-1, y+2, N, path);
	}
	if(x-2>=0 && y+1<N){
		pthread_create(&thread_id, NULL, function, x-2, y+1, N, path);
	}
	if(x-2>=0 && y-1>=0){
		pthread_create(&thread_id, NULL, function, x-2, y-1, N, path);
	}
	if(x-1>=0 && y-2>=0){
		pthread_create(&thread_id, NULL, function, x-1, y-2, N, path);
	}
	if(x+1<N && y-2>=0){
		pthread_create(&thread_id, NULL, function, x+1, y-2, N, path);
	}
	if(x+2<N && y-1>=0){
		pthread_create(&thread_id, NULL, function, x+2, y-1, N, path);
	}
}

// Not necessary to use this function as long as same printing pattern is followed 
void print_path(pair path[], int n){
	for(int i=0;i<n;i++){
		printf("%d,%d|",path[i].x,path[i].y);
	}
}

int main(int argc, char *argv[]) {
	
	if (argc != 4) {
		printf("Usage: ./Knight.out grid_size StartX StartY");
		exit(-1);
	}
	
	N = atoi(argv[1]);
	int StartX=atoi(argv[2]);
	int StartY=atoi(argv[3]);
	int path[2*N*N]; // Declared the path array
	for(int i = 0; i < 2*N*N; i++) {
    path[i] = -1; // Path array initialise to -1;
	}

	/* Do your thing here */
	int ans = function(StartX,StartY,N, path[]);

	return 0;
}