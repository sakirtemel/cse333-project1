#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
/* IO Redirection */
int stdOut;

void saveOut(){
	dup2(STDOUT_FILENO, stdOut);
}
void loadOut(){
	dup2(stdOut, STDOUT_FILENO);
}

int redirectInput(const char *filename){
	int canAccess = 0;
	canAccess = access(filename, R_OK);
	if(canAccess == 0){
		freopen(filename, "r", stdin);
	}
	return 1;
}

int _redirectOutput(const char *filename, int append){
	int canAccess;
	int fd;
	canAccess = access(filename, W_OK);
	if(canAccess == 0){
		if(append==1)
			fd = open(filename, O_CREAT | O_WRONLY, 0777);
		else
			fd = open(filename, O_CREAT | O_WRONLY, 0777);
	}
	dup2(fd,STDOUT_FILENO);
	close(fd);
	return 1;
}
int redirectOutput(const char *filename){
	return _redirectOutput(filename, 0);
}
/* /IO Redirection */

