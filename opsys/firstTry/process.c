#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;        // system error number 

void syserr(char * msg)   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   //abort(errno);
}
pid_t runProcess(const char *cmd){

   pid_t pid;            // process ID
   //int rc;               // return code
 	
   switch (pid = fork()) {
      case -1:
         //syserr("fork");
         ;
      case 0:             // execution in child process 
         execl(cmd, cmd, NULL);
        syserr("execl"); // error if return from exec
        printf("error");
   }
	return pid;
}

void runForegroundProcess(const char *cmd){
	pid_t pid;
	int status;

	pid = runProcess(cmd);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
}
pid_t runBackgroundProcess(const char *cmd){
	pid_t pid;
	pid = runProcess(cmd);
	return pid;
}


/* IO Redirection */
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
	canAccess = access(filename, W_OK);
	if(canAccess == 0){
		if(append==1)
			freopen(filename, "a", stdout);
		else
			freopen(filename, "w", stdout);
	}
	return 1;
}
int redirectOutput(const char *filename){
	return _redirectOutput(filename, 0);
}
/* /IO Redirection */
