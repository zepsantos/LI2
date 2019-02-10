#include <stdio.h> 
#include <stdlib.h> 
#include "estado.h"
#include "ancora.h"
#include "cgi.h"
#include "openFile.h"



#define MAX_BUFFER		10240

/* void pushMoveOld(NODE *top, MOVIMENTO move ) {

    NODE *newNode = (NODE* )malloc(sizeof(NODE)); 
    newNode -> this_move = move; 
    if ( top == NULL) {
    newNode -> next = NULL; 
    }else {
    newNode -> next =  top; 
    } top = newNode; 
} */

void printStack(NODE *top) {
    NODE * temp = top;
    while(temp->next != NULL) {
        //printf("STACK:%d", temp->this_move.X);
        temp = temp->next;
    }
}

void pushMove(NODE *top, MOVIMENTO move ) {
    
    NODE *newNode = (NODE* )malloc(sizeof(NODE)); 
    newNode -> this_move = move; 
    if ( top == NULL) {
    newNode -> next = NULL; 
    }else {
    newNode -> next =  top -> next; 
    } 
    top -> next = newNode;
    printStack(top);
}

MOVIMENTO popOld(NODE *top) {
    MOVIMENTO move = {0}; 
     NODE* temp =  top;
    if ( top != NULL) {
    move = temp -> this_move;  
    top = temp -> next; 
    free(temp); 
    return move; 
    }
    return move; 
}


MOVIMENTO pop(NODE *top) {
    MOVIMENTO move = {0}; 
    NODE* temp =  top->next;
    move = temp -> this_move;  
    top->next = temp -> next; 
    free(temp); 
    return move;     
    
}
















