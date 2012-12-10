#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.c"
#include "signals.c"

extern int errno;        // system error number 

void syserr(char * msg)   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   //abort(errno);
}
pid_t runProcess(char *args[]){
   pid_t pid;            // process ID
   //int rc;               // return code
	char cmd[50];
   /* check the second arg for execl */
   /* try to find it */
   strcpy(cmd, which(proc.arguments[0]));
   if(cmd == NULL)/* process not found */
		return;

   switch (pid = fork()) {
      case -1:
         syserr("fork");
         break;
      case 0:             // execution in child process 
		if(readFromInput){
			readInput();
			closeAllPipes();
			
		}
		if(writeToOutput){
			writeOutput();
			if(!readFromInput){
				closeAllPipes();
			}
		}
        execv(cmd,args);
        syserr("execl"); // error if return from exec
        printf("error");
   }
	return pid;
}

void runForegroundProcess(const char *cmd, char *args[]){
	pid_t pid;
	int status;
	pid = runProcess(args);
	if(pid){
	   lastForegroundProcessId = pid;
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
	}
	//WUNTRACED | WCONTINUED
}
pid_t runBackgroundProcess(const char *cmd, char *args[]){
	pid_t pid;
	pid = runProcess(args);/* RUN THE PROCESS */
	if(pid)
		addProcess(pid, args[0]);/* ADD IT TO THE BACKGRUND QUEUE */
	return pid;
}
/* FIND THE PATH OF COMMAND */
char* which(char *filename){
		char *path,*path2;
		char *d;
		
		char temp[50];
		
		if(strchr(filename, '/')!=NULL){ /* IF THE PATH WAS ALREADY GIVEN */
			if(access(filename, X_OK)==0)/* JUST TRY IF IT IS EXECUTABLE OR NOT */
				return filename;/* IT IS */
			else
				return NULL;
		}
		path = getenv("PATH"); /* GET THE PATH STRING */
		path2 = malloc(strlen(path)+1); /* AND DUPLICATE IT */
		strcpy(path2, path);
		
		while((d = strsep(&path2, ":"))!=NULL){/* TRY TO FIND IT IN ONE OF THE PATH DIRECTORIES */
			if(*d=='\0')
				d=".";
			snprintf(temp, sizeof(temp), "%s/%s", d, filename);
			if(access(temp,X_OK)==0){/* IF FOUND */
				char *temp2;
				temp2 = malloc(strlen(temp)+1);
				strcpy(temp2, temp);
				return temp2;
			}
		}
	return NULL; /* NOT FOUND */
}
