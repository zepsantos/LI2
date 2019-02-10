#ifndef ___OPENFILE_H___
#define ___OPENFILE_H___
#include "ancora.h"
#include "estado.h"

int readGameFromFile(ESTADO * e, char * fileName); 
void saveMoveToFile(char * fileName, NODE *stack); 
void saveEstadoToFile(char * estadoStr, char * fileName); 
NODE * readMoveFromFile(char * fileName); 
char * readEstadoFromFile(char * fileName); 
char * appendTxtToStringSTACK(char * fileName);
int fileExist(char * fileName); 
char * appendTxtToString(char * fileName); 
#endif