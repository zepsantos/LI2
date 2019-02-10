#ifndef ___ANCORA_H___
#define ___ANCORA_H___

typedef struct movimento {
int X; 
int Y; 
int Valor;
}MOVIMENTO; 

typedef struct node {
MOVIMENTO this_move; 
struct node *next; 
}NODE; 

void pushMove(NODE * top, MOVIMENTO e); 
MOVIMENTO pop(NODE * top); 
#endif