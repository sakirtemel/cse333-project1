#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	int i = 0;
	for(;i<20;i++){
		fprintf(stderr, "sleep %d\n", i);
		sleep(2);
	}

	return 0;
}
