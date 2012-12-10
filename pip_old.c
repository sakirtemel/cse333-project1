#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int *lastPipe = NULL;
int *currentPipe = NULL;

int readFromInput = 0;
int writeToOutput = 0;

int *newPipe(){
	lastPipe = currentPipe;
	int *pipee;
	pipee = malloc(sizeof(int)*2);
	pipe(pipee);
	return pipee;
}

enum PIPES {
    READ, WRITE
};
void readInput(){
    dup2(lastPipe[READ], 0);
    //readFromInput = 0;
}
void writeOutput(){
	dup2(currentPipe[WRITE], 1);
	//writeToOutput = 0;
}
void closePipes(){
        close(currentPipe[1]);
}
void openPipe(){
	currentPipe = newPipe(); // new pipe
	if(lastPipe == NULL){
		lastPipe = currentPipe;
	}

	if(!currentPipe)
		fprintf(stderr, "\n current pipe is null");
	if(!lastPipe)
		fprintf(stderr, "\n last pipe is null");


}
