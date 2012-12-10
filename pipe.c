#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef PIPE_C
#define PIPE_C

enum PIPES {
    READ, WRITE
};

int pipeNo = 0;

int readFromInput = 0;
int writeToOutput = 0;



int *leftPipe = NULL;
int *rightPipe = NULL;

int pipes[5][2];

void closeAllPipes(){
	int i=0;
	for(;i<5;i++){
		close(pipes[i][0]);close(pipes[i][1]);
	}
}
void initPipes(){
	pipe(pipes[0]);
	pipe(pipes[1]);
	pipe(pipes[2]);
	pipe(pipes[3]);
	pipe(pipes[4]);
}


void openPipe(){
	leftPipe = rightPipe;
	rightPipe = pipes[pipeNo];
	if(pipeNo == 0){
		leftPipe = rightPipe;
	}
	
	pipeNo++;
}
void readInput(){
    dup2(leftPipe[READ], 0);
    //readFromInput = 0;
}
void writeOutput(){
	dup2(rightPipe[WRITE], 1);
	//writeToOutput = 0;
}

#endif
