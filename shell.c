/**
*
* @author sakirtemel
* @author omercayirtepe
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtinCommands.c"
#include "ioRedirection.c"
#include "process.c"
#include "signals.c"

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators


typedef struct process{
	pid_t proccessId;
	char *outputFilename;
	char *inputFilename;
	char *arguments[MAX_ARGS];
	int isBackground;
	int appendRedirect;
}process;

/* check the current line */
int checkCommands(char **commands){
	int i = 0;
	int argCount = 0;
	char cmd[50];
	int ilk = 1;
	writeToOutput = 0;
	readFromInput = 0;

	process proc; /* create a process struct instance */
	for(;commands[i]!=NULL;i++){ /* inspect each arg. */
		/* if there is a redirect, change redirect string */
		/* if background */
		/* if pipe */
		/* arguments */
		if( strcmp(commands[i], ">>") == 0 ){ /* REDIRECT OUTPUT */
			//if not give an error
			proc.outputFilename = commands[++i];
			proc.appendRedirect = 1;
		}
		else if( strcmp(commands[i], ">") == 0 ){ /* REDIRECT OUTPUT */
			//if not give an error
			proc.outputFilename = commands[++i];
		}
		else if( strcmp(commands[i], "<") == 0 ){ /* REDIRECT INPUT */
			//if not give an error
			proc.inputFilename = commands[++i];
		}
		else if( strcmp(commands[i], "&") == 0 ){ /* BACKGROUND */
			//if not give an error
			proc.isBackground = 1;
		}
		else if( strcmp(commands[i], "|") == 0 ){/* PIPE */
			/* run the previous program, create a new proc. */
			proc.arguments[argCount] = NULL;
			
			openPipe();
			if(ilk){
				readFromInput = 0;
				writeToOutput = 1;
				ilk = 0;	
			}else{
				readFromInput = 1;
				writeToOutput = 1;
			}
				strcpy(cmd, which(proc.arguments[0]));
				fprintf(stderr, "\n %s Pipes %d,%d\n", cmd,readFromInput, writeToOutput);
				runBackgroundProcess(cmd, proc.arguments);			
			//closePipes();
				
			argCount = 0;
		}
		else{/* ARGUMENTS */
			proc.arguments[argCount++] = commands[i];/* add the command line argument as the process argument*/
		}
	}

	proc.arguments[argCount] = NULL; /* end the arguments */

	if(ilk==0){
		//closePipes();
		readFromInput = 1;
		writeToOutput = 0;
	}
	/* run the last proc */
	
	switch(checkInternalCommand(proc.arguments)){/* chech if is that a internal command */
		case 1:/* YES */
			return 1; /* COMMAND EXECUTED, PROMPT ANOTHER COMMAND */
			break;
		case -1:
			return -1; /* EXIT COMMAND */
			break;
	}
	/* RETURNED 0, IT IS NOT AN INTERNAL COMMAND */
	
	strcpy(cmd, which(proc.arguments[0]));
	
	/*if(ilk==0){
		runBackgroundProcess(cmd, proc.arguments);
		closeAllPipes();
		while(wait(NULL)!=-1);
	}*/
	
	if(proc.isBackground == 1)
		runBackgroundProcess(cmd, proc.arguments);
	else
		runForegroundProcess(cmd, proc.arguments);


	return 1; /* COMMAND LINE EXECUTED SUCCESSFULLY */
}


int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "\nMoje Shell ==> " ;                    // shell prompt
	int checkCommandsResult = 0;
/* keep reading input until "quit" command or eof of redirected input */
     
     initSignals(); /* initialize the keyboard signals and process signals */
     initPipes(); /* initialize the pipes */
     
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

				checkCommandsResult = checkCommands(args); /* check the command */
				if(checkCommandsResult == -1){ /* if it is the exit code, then don't prompt again */
					break;
				}
				else if(checkCommandsResult == 1){ /* if the function worked correctly */
					continue;
				}
				else{/* else it's an unrecognized command */
					printf("Error.\n");
					continue;
				}
            }
        }
    }
    return 0; 
}
