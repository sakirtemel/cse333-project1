#include <string.h>
#include <stdlib.h>
#include "signals.c"

int checkInternalCommand(char *args[]){
                if (!strcmp(args[0],"clear")) { // "clear" command
                    if(fork()==0)
						execl("/usr/bin/clear", "clear", NULL);
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
					char *Index;
					strncpy(Index, args[1][1]);
					//index = (int)args[1][0]-'0';
					index = atoi(Index);
					killWithIndex(index);
                    return 1;
                }
				if (!strcmp(args[0],"fg")){  // fg
					int index = 0;
					index = (int)args[1][0]-'0';
					bringForeground(index);
                    return 1;
                } 
				if (!strcmp(args[0],"bg")){  // bg
					bringBackground();
                    return 1;
                }                                            
	return 0;
}
