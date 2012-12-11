#include <string.h>
#include <stdlib.h>
#include "signals.c"

int checkInternalCommand(char *args[]){
                if (!strcmp(args[0],"clear")) { // "clear" command
					pid_t pid;
					int status;
                    if((pid = fork())==0)
						execl("/usr/bin/clear", "clear", NULL);
					else
						waitpid(pid, &status, 0);
                    //continue;
                    return 1;
                }
                if (!strcmp(args[0],"exit")){   // "quit" command
					killAllProcesses();
                    return -1;
                }
                
                if (!strcmp(args[0],"ps_all")){  // list
					listAllProcesses();
                    return 1;
                }
				if (!strcmp(args[0],"kill")){  // kill
					int index = 0;
					char Index[10];
					if(args[1][0] == '%')//INDEX
						strcpy(Index, &args[1][1]);
					else
						strcpy(Index, &args[1][0]);
					index = atoi(Index);
					if(args[1][0] == '%')
						killWithIndex(index);
					else
						killWithProcessId(index);
                    return 1;
                }
				if (!strcmp(args[0],"fg")){  // fg
					int index = 0;
					char Index[10];
					if( args[1][0] != '%'){//INDEX
						fprintf(stderr, "\nUsage : fg %cindex",'%');
						return 1;
					}
						strcpy(Index, &args[1][1]);
					index = atoi(Index);
					bringForeground(index);
                    return 1;
                } 
				if (!strcmp(args[0],"bg")){  // bg
					bringBackground();
                    return 1;
                }                                            
	return 0;
}
