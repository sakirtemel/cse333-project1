#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtinCommands.c"
#include "ioRedirection.c"
#include "process.c"
//#include "signals.c"

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators


typedef struct process{
	pid_t proccessId;
	char *outputFilename;
	char *inputFilename;
	char *arguments[50];
	int isBuiltin;
	int isBackground;
}process;


int checkCommands(char **commands){
	int i = 0;
	int argCount = 0;
	char cmd[50];
	int ilk = 1;
	process proc;
	for(;commands[i]!=NULL;i++){ /* inspect each arg. */
		/* if there is a redirect, change redirect string */
		/* if background */
		/* if pipe */
		/* arguments */
		if( strcmp(commands[i], ">") == 0 ){
			//if not give an error
			proc.outputFilename = commands[++i];
		}
		else if( strcmp(commands[i], "<") == 0 ){
			//if not give an error
			proc.inputFilename = commands[++i];
		}
		else if( strcmp(commands[i], "&") == 0 ){
			//if not give an error
			proc.isBackground = 1;
		}
		else if( strcmp(commands[i], "|") == 0 ){
			/* run the previous program, create a new proc. */
			proc.arguments[argCount] = NULL;
			
			openPipe();
			
			if(ilk){
				readFromInput = 0;
				writeToOutput = 1;
				ilk = 0;	
			}else{
				readFromInput = 1;
				writeToOutput = 0;
			}
				strcpy(cmd, which(proc.arguments[0]));
				fprintf(stderr, "%s %d,%d\n", cmd,readFromInput, writeToOutput);
				runForegroundProcess(cmd, proc.arguments);			
			closePipes();
				
			argCount = 0;
		}
		else{
			proc.arguments[argCount++] = commands[i];
		}
	}
	closePipes();
	/* run the last proc */
	proc.arguments[argCount] = NULL;
	//strcpy(cmd, which(proc.arguments[0]));
	//runForegroundProcess(cmd, proc.arguments);
	
	//printf("%s", proc.arguments[0]);
	
	return 1;
}

int checkCommandss(char **commands){

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
		strcpy(cmd, which(commands[0]));
		if(cmd!=NULL){
			// fetch the arguments
			int j = 0;
			char *argumanlar[30];
			while(commands[j]!=NULL){
				if(*commands[j]=='>')
					break;
				argumanlar[j] = commands[j];
				//printf("%s\n", commands[j]);
				j++;
			}
			argumanlar[j] = NULL;
			j = 0;

			runForegroundProcess(cmd, argumanlar);

			
		}
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
    char * prompt = "Moje Shell ==> " ;                    // shell prompt
	int checkCommandsResult = 0;
/* keep reading input until "quit" command or eof of redirected input */
     
  //   initSignals();
     
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
