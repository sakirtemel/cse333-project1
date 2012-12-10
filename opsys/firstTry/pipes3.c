#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipes[5][2];
void shutTheFuckUp(){
	int i=0;
	for(;i<5;i++){
		close(pipes[i][0]);close(pipes[i][1]);
	}
}
int main(){
	pipe(pipes[0]);
	pipe(pipes[1]);
	pipe(pipes[2]);
	pipe(pipes[3]);
	pipe(pipes[4]);


	if(fork()==0){
		dup2(pipes[0][1], STDOUT_FILENO);
		shutTheFuckUp();
		execl("/bin/ls", "ls", "-l",NULL);
	}
	if(fork()==0){
		dup2(pipes[0][0], STDIN_FILENO);
		dup2(pipes[1][1], STDOUT_FILENO);
		shutTheFuckUp();
		execl("/usr/bin/sort", "sort",NULL);
	}
	if(fork()==0){
		dup2(pipes[1][0], STDIN_FILENO);
		shutTheFuckUp();
		execl("/usr/bin/wc", "wc","-l",NULL);
	}
	
	shutTheFuckUp();
	
	while(wait(NULL)!=-1);
	
	
	printf("hello");
	return 0;
}
void readInput(){
    dup2(leftPipe[READ], 0);
    //closeAllPipes();
    //readFromInput = 0;
}
void writeOutput(){
	dup2(rightPipe[WRITE], 1);
	//closeAllPipes();
	//writeToOutput = 0;
}
