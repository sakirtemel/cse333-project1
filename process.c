#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.c"
extern int errno;        // system error number 

void syserr(char * msg)   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   //abort(errno);
}
pid_t runProcess(const char *cmd, char *args[]){

   pid_t pid;            // process ID
   //int rc;               // return code
	
   switch (pid = fork()) {
      case -1:
         //syserr("fork");
         ;
      case 0:             // execution in child process 
		if(readFromInput)
			readInput();
		if(writeToOutput)
			writeOutput();
        execv(cmd,args);
        syserr("execl"); // error if return from exec
        printf("error");
   }
	return pid;
}

void runForegroundProcess(const char *cmd, char *args[]){
	pid_t pid;
	int status;
	
	

	pid = runProcess(cmd, args);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
}
pid_t runBackgroundProcess(const char *cmd){
	pid_t pid;
	//pid = runProcess(cmd);
	pid = 2;
	return pid;
}
char* which(char *filename){
		char *path,*path2;
		char *d;
		
		char temp[50];
		
		if(strchr(filename, '/')!=NULL){
			if(access(filename, X_OK)==0)
				return filename;
		}
		
		
		path = getenv("PATH");
		path2 = malloc(strlen(path)+1);
		strcpy(path2, path);
		
		while((d = strsep(&path2, ":"))!=NULL){
			if(*d=='\0')
				d=".";
			snprintf(temp, sizeof(temp), "%s/%s", d, filename);
			if(access(temp,X_OK)==0){
				char *temp2;
				temp2 = malloc(strlen(temp)+1);
				strcpy(temp2, temp);
				return temp2;
			}
		}
		return 0;
	return NULL;
}
