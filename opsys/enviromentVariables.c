#include <stdio.h>
#include <stdlib.h>

extern char **environ;  
// NULL terminated array of char *          

int main(){

   //int i;   
   /*for (i = 0; environ[i] != NULL; i++)
	printf("%s\n",environ[i]);*/
	//exit(0);
	printf("%s\n",getenv("PATH"));
	printf("Hello");

	return 0;
}
