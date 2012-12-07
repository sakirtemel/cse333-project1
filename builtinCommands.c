#include <string.h>
#include <stdlib.h>


int checkInternalCommand(char **args){
//	int curOut = dup(1);
                if (!strcmp(args[0],"clear")) { // "clear" command
                    system("clear");
                    //continue;
                    return 1;
                }
                if (!strcmp(args[0],"exit"))   // "quit" command
                    return -1;
                
                if (!strcmp(args[0],"ps_all")){  // "quit" command
					//saveOut();
					//redirectOutput("result.txt");
					printf("listeler\n");
					printf("1-\n");
					printf("2-\n");
					//loadOut();

					//dup2(curOut, 1);
                    return 1;
                }
                    
	return 0;
}
