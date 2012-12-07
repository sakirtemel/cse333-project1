#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtinCommands.c"
#include "ioRedirection.c"
#include "process.c"

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators


int checkCommands(char **commands){

	int i, cvp;
	char cmd[50];
	i=0;
	cvp = 0;
	int redirectOut = 0;
	while(commands[i]!=NULL){
		if(strcmp(commands[i],">")==0 && commands[i+1]!=NULL){
			saveOut();
			redirectOutput(commands[i+1]);
			redirectOut = 1;
			break;
		}
		i++;
	}
	cvp = checkInternalCommand(commands);
	
	if(cvp==0){
		strcpy(cmd, "/bin/");
		strcat(cmd, commands[0]);
		runForegroundProcess(cmd);
		cvp=1;
	}
	
	
	if(redirectOut == 1){
		loadOut();
	}
	return cvp;
}

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "Moje Shell ==>" ;                    // shell prompt
	int checkCommandsResult = 0;
/* keep reading input until "quit" command or eof of redirected input */
     
    while (!feof(stdin)) { 
    
/* get command line from input */
  
        fputs (prompt, stdout);                // write prompt
        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
        
/* tokenize the input into args array */

            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenize input
            while ((*arg++ = strtok(NULL,SEPARATORS)));
                                               // last entry will be NULL 
 
            if (args[0]) {                     // if there's anything there
            
/* check for internal/external command */

				checkCommandsResult = checkCommands(args);
				if(checkCommandsResult == -1){
					break;
				}
				else if(checkCommandsResult == 1){
					continue;
				}
				else{
					printf("Unrecognized command.\n");
					continue;
				}


            }
        }
    }
    return 0; 
}
