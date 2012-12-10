#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int *lastPipe = NULL;
int *currentPipe = NULL;

int *newPipe(){
	lastPipe = currentPipe;
	int *pipee;
	pipee = malloc(sizeof(int)*2);
	pipe(pipee);
	if(lastPipe==NULL){
		lastPipe = pipee;
	}
	return pipee;
}

int main(){
//int status;
enum PIPES {
    READ, WRITE
};


	currentPipe = newPipe(); // new pipe
    pid_t pid = fork();
    if (pid == 0) {
        dup2(currentPipe[WRITE], 1);
        close(currentPipe[WRITE]);
        execl("/bin/ls","ls","-l",NULL); 
        exit(0);
    } 
    else {
		//while(wait(NULL)!=-1);
       close(currentPipe[1]);
        fprintf(stderr, "\n-%d-\n", currentPipe[1]);
    }
	
	fprintf(stderr, "\n-%d-\n", lastPipe[0]);

	currentPipe = newPipe();
    pid = fork();
    if (pid == 0) {
    dup2(lastPipe[READ], 0);
    dup2(currentPipe[WRITE], 1);
	close(currentPipe[WRITE]);

        execl("/usr/bin/sort","sort",NULL);       
    }
    else {
		//while(wait(NULL)!=-1);
        close(currentPipe[1]);
        fprintf(stderr, "\n-%d-\n", currentPipe[1]);
    }
	
//	pipee = newPipe();
    pid = fork();
    if (pid == 0) {
        //close(lastPipe[READ]);
        dup2(lastPipe[READ], 0);
            execl("/usr/bin/wc","wc","-l", NULL);
    }

    //waitpid(pid, &status, 0);
    wait(NULL);
	//while(wait(NULL)!=-1);
	fprintf(stderr, "print");
	return 0;
}
