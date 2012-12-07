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
