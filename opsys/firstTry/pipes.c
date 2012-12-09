#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
   int fd[3][2];

int readInput(int pipeNo){
	if (dup2(fd[pipeNo][0], STDIN_FILENO) == -1)               /* sort is the parent */
       perror("Failed to redirect stdin of sort");
   else if ((close(fd[pipeNo][0]) == -1) || (close(fd[pipeNo][1]) == -1)) 
       perror("Failed to close extra pipe file descriptors on sort"); 
   else
	return 1;
	
return 0;
}
int writeOutput(int pipeNo){
	  if (dup2(fd[pipeNo][1], STDOUT_FILENO) == -1)
         perror("Failed to redirect stdout of ls");
      else if ((close(fd[pipeNo][0]) == -1) || (close(fd[pipeNo][1]) == -1)) 
         perror("Failed to close extra pipe descriptors on ls");
      else
			return 1;
return 0;
}

int main(void) {

   int i = 0;
   for(i=0;i<3;i++){
	   if ((pipe(fd[i]) == -1)) {
		  perror("Failed to setup pipeline");
		  return 1;
	   }
	}
	
		if(fork()==0){
			writeOutput(0);
			execl("/bin/ls", "ls", "-l",NULL);
		}
		if(fork()==0){
			readInput(0);
		//	writeOutput(1);
			execl("/usr/bin/sort", "sort",NULL);
		}
	
	
   return 1; 
}
