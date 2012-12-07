#include <string.h>
#include <stdlib.h>

int checkInternalCommand(char **args){

                if (!strcmp(args[0],"clear")) { // "clear" command
                    system("clear");
                    //continue;
                    return 1;
                }
                if (!strcmp(args[0],"exit"))   // "quit" command
                    return -1;
                    
	return 0;
}
