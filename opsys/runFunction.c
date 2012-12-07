#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


extern int errno;        // system error number 

void syserr(char * msg)   // report error code and abort
{
   fprintf(stderr,"%s: %s", strerror(errno), msg);
   //abort(errno);
}

pid_t run(const char *cmd){

   pid_t pid;            // process ID
   int rc;               // return code
 	
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


int main(int argc, char *argv[]){
	
	
	run("/bin/ls");
	
	return 0;
}
