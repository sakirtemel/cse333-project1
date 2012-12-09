#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int *lastPipe;
int *currentPipe;

int *newPipe(){
	lastPipe = currentPipe;
	int *pipee;
	pipee = malloc(sizeof(int)*2);
	pipe(pipee);
	return pipee;
}

int main(){

enum PIPES {
    READ, WRITE
};


	currentPipe = newPipe(); // new pipe
    pid_t pid = fork();
    if (pid == 0) {
        dup2(currentPipe[WRITE], 1);
        execl("/bin/ls","ls","-l",NULL); 
        exit(0);
    } 
    else {
        close(currentPipe[1]);
    }

	currentPipe = newPipe();
    pid = fork();
    if (pid == 0) {
    dup2(lastPipe[READ], 0);
    dup2(currentPipe[WRITE], 1);
        execl("/usr/bin/sort","sort",NULL);       
    }
    else {
        close(currentPipe[1]);
    }
	
//	pipee = newPipe();
    pid = fork();
    if (pid == 0) {
        dup2(lastPipe[READ], 0);
            execl("/usr/bin/wc","wc","-l", NULL);
    }

    //waitpid(pid, &status, 0);
	while(wait(NULL)!=-1);
	fprintf(stderr, "print");
	return 0;
}
