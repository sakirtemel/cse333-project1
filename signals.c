#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


#ifndef SIGNALS_C
#define SIGNALS_C
#define CHILD 0

void suspendHandler();
void terminateHandler();
void addProcess(int,const char*);
void bringForeground(int);
void bringBackground();

void killWithIndex(int);
void listAllProcesses();
void killAllProcesses();
struct job
{
    char *info;
    int index;
    int pid;
    struct job *next;
};
typedef struct job *JOB;

JOB jobHeader,jobFooter;
JOB terminatedJobHeader,terminatedJobFooter;

pid_t last_pid;
int processIndexCounter = 0;
int command=0;
int lastForegroundProcessId = 0;









/* LL */
void addToList(JOB *list,JOB newNode){
        JOB current = *list; /* current pointer is now head of the list */

        if(current == NULL){ /* if the list is empty */
                *list = newNode; /* head of the list is newNode */
        }
        else{ /* if the list is not empty */
                while(current->next != NULL) /* go until the end of the list */
                        current = current->next; /* next node */
                
                current->next = newNode; /* now it's the end of the list, the end node's next node is our newNode */
        }
        newNode->next = NULL; /* and our newNode is the last node */
}
int removeFromList(JOB *list,JOB node){
        JOB current = *list;
        JOB previous = NULL;
        if(current == NULL){
                return 0; /* list is empty, can't remove anything */
        }
        while(current != NULL){
                if( current == node ){
                        if( previous == NULL ) /* if the element that is wanted removed is the first element of the list */
                                *list = current->next;
                        else
                                previous->next = current->next; /* link the elements next to the removed element */

                        //free(node);
                        node->next = NULL;
                        return 1;
                }
                previous = current;
                current = current->next;
        }
        return 0;
}
void printList(JOB *list){
        JOB current = *list;

        if(current == NULL){ /* if list is empty */
                printf("no element\n");
        }
        else{
                while(current != NULL){/* write all of the points in the list */
                       // printf("(%d,%d) ", current->x, current->y);
                        current = current->next;
                }
        }
}

/**/









void addProcess(int pid,const char *info)
{
    JOB  node= malloc(sizeof(JOB));
    node->info=malloc(sizeof(char)*20);
    strcat(node->info,info);
    node->pid=pid;
    node->index=++processIndexCounter;
    addToList(&jobHeader, node);
    /*node->next=NULL;
    if (jobHeader == NULL)
    {
        jobHeader = node;
        jobFooter = jobHeader;
    }
    else
    {
        jobFooter->next = node;
        jobFooter = node;
    }*/
}








void bringBackground(){
	fprintf(stderr, "bring called");
	kill(lastForegroundProcessId, SIGCONT);
}


void bringForeground(int index)
{
	int status;
    JOB tmp = jobHeader;

    while (tmp !=NULL)
    {
        if (tmp->index == index)
        {
			lastForegroundProcessId = tmp->pid;
             waitpid(tmp->pid, &status, 0);
	pid_t pid = tmp->pid;

	if(pid==-1){ // foreground process already catched at runForegroundProcess
		return;
	}
		/* find the job */
		/* move it to terminatedJobList */
		JOB currentHeader = jobHeader;
		
		while(currentHeader!=NULL){
			if(currentHeader->pid == pid){
				
				removeFromList(&jobHeader, currentHeader);
				addToList(&terminatedJobHeader, currentHeader);
				return;
				/* move to the other list */
				
			}
			//prev = currentHeader;
			currentHeader = currentHeader->next;
		}
		fprintf(stderr, "Error: child died before the time we expected: %d", (int)pid);
		
		

             
             //childOldu();
             break;
        }
        tmp = tmp->next;
    }

}



void killWithIndex(int index){
    JOB tmp = jobHeader;

    while (tmp != NULL)
    {
        if (tmp->index == index)
        {
            kill(tmp->pid,SIGKILL);
            fprintf(stderr, " Killed:  %d" ,tmp->index);
            return;
        }
        tmp=tmp->next;
    }
    fprintf(stderr, " There is no such a process with index =  %d" , index);
}
void listAllProcesses(){
        JOB tmp = jobHeader;
        JOB tmp2 = terminatedJobHeader;
		JOB temp = NULL;
	if(jobHeader==NULL)
		processIndexCounter = 0;
	fprintf(stderr, "\nRunning Processes\n");
    while (tmp != NULL)
    {
        fprintf(stderr, "\n[%d]  %s  (pid=%d)" ,tmp->index,tmp->info,tmp->pid);
        tmp=tmp->next;
    }
    fprintf(stderr, "\nTerminated Processes\n");
    while (tmp2 != NULL)
    {
        fprintf(stderr, "\n[%d]  %s  (pid=%d)" ,tmp2->index,tmp2->info,tmp2->pid);
        temp = tmp2;
        tmp2=tmp2->next;
        removeFromList(&terminatedJobHeader, temp);
        free(temp);
    }
}

//ctrl+Z
void suspendHandler()
{
        kill(lastForegroundProcessId,SIGSTOP);
        printf("process (%d)  stopped\n",lastForegroundProcessId);
        raise(SIGCHLD);
}

//ctrl+D
void terminateHandler()
{
	fprintf(stderr,"ctrl+D");
	//exit(0);
}

void childOldu(){
	pid_t pid = wait(NULL);
	if(pid==-1){ // foreground process already catched at runForegroundProcess
		return;
	}
		/* find the job */
		/* move it to terminatedJobList */
		JOB currentHeader = jobHeader;
		
		while(currentHeader!=NULL){
			if(currentHeader->pid == pid){
				
				removeFromList(&jobHeader, currentHeader);
				addToList(&terminatedJobHeader, currentHeader);
				return;
				/* move to the other list */
				
			}
			//prev = currentHeader;
			currentHeader = currentHeader->next;
		}
		fprintf(stderr, "Error: child died before the time we expected: %d", (int)pid);
}


int initSignals(){
	signal(SIGINT, SIG_IGN); //Ignore ctrl+C
	//signal(SIGUSR1, SIG_IGN); //Ignore ctrl+C
	signal(SIGTSTP, suspendHandler); // ctrl+Z
	signal(3, terminateHandler); // ctrl+D
	signal(SIGCHLD, childOldu);
	return 1;
}
void killAllProcesses(){
        JOB tmp = jobHeader;
        JOB temp = NULL;
    while (tmp != NULL){
        //fprintf(stderr, "\n[%d]  %s  (pid=%d)" ,tmp->index,tmp->info,tmp->pid);
        temp = tmp;
        tmp=tmp->next;
        killWithIndex(temp->index);
    }
}

#endif
