#include <string.h>
#include <stdlib.h>
#include "signals.c"

int checkInternalCommand(char *args[]){
                if (!strcmp(args[0],"clear")) { // "clear" command
                    system("clear");
                    //continue;
                    return 1;
                }
                if (!strcmp(args[0],"exit")){   // "quit" command
					killAllProcesses();
                    return -1;
                }
                
                if (!strcmp(args[0],"ps_all")){  // "quit" command
					listAllProcesses();
                    return 1;
                }
				if (!strcmp(args[0],"kill")){  // "quit" command
					int index = 0;
					index = (int)args[1][0]-'0';
					killWithIndex(index);
                    return 1;
                }
				if (!strcmp(args[0],"fg")){  // "quit" command
					int index = 0;
					index = (int)args[1][0]-'0';
					bringForeground(index);
                    return 1;
                } 
				if (!strcmp(args[0],"bg")){  // "quit" command
					bringBackground();
                    return 1;
                }                                            
                    
	return 0;
}
