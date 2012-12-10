void addToList(point **list,point *newNode){
        point *current = *list; /* current pointer is now head of the list */

        if(current == NULL){ /* if the list is empty */
                *list = newNode; /* head of the list is newNode */
        }
        else{ /* if the list is not empty */
                while(current->nextPoint != NULL) /* go until the end of the list */
                        current = current->nextPoint; /* next node */
                
                current->nextPoint = newNode; /* now it's the end of the list, the end node's next node is our newNode */
        }
        newNode->nextPoint = NULL; /* and our newNode is the last node */
}
int removeFromList(point **list,point *node){
        point *current = *list;
        point *previous = NULL;
        if(current == NULL){
                return 0; /* list is empty, can't remove anything */
        }
        while(current != NULL){
                if( current == node ){
                        if( previous == NULL ) /* if the element that is wanted removed is the first element of the list */
                                *list = current->nextPoint;
                        else
                                previous->nextPoint = current->nextPoint; /* link the elements next to the removed element */

                        //free(node);
                        node->nextPoint = NULL;
                        return 1;
                }
                previous = current;
                current = current->nextPoint;
        }
        return 0;
}
void printList(point **list){
        point *current = *list;

        if(current == NULL){ /* if list is empty */
                printf("no element\n");
        }
        else{
                while(current != NULL){/* write all of the points in the list */
                        printf("(%d,%d) ", current->x, current->y);
                        current = current->nextPoint;
                }
        }
}
