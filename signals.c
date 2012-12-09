#include <stdio.h>
#include <signal.h>

void emptySlot(void);
void suspendSlot(void);

void initSignals(){
	signal(SIGINT, emptySlot); // CTRL + C
	signal(SIGTSTP, suspendSlot); // CTRL + Z
}
void emptySlot(){
	fprintf(stderr, "Exit called");
}
void suspendSlot(){
	fprintf(stderr, "Suspend called");
}
