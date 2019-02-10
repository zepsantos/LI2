#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "openFile.h"

#define LOCATION "/usr/local/games/GandaGalo/"
#define LOCATIONSTACK "/usr/local/games/GandaGalo/stack/"

int readGameFromFile(ESTADO *e, char * fileName) {
	int c = 0; 
	FILE * ptr_file; 
	ptr_file = fopen(fileName, "r"); 
	if ( ! ptr_file)
		return 1; 
	for (int x = 0; (x < (e -> num_lins) && (c != -1)); x++) {
		for (int y = 0; y <= (e -> num_cols); y++) {
			c = fgetc(ptr_file); 
			if (c == '\n')
				continue; 
			e -> grelha[x][y] = c - '0'; 
			//printf("%d\n",e -> grelha[x][y]); // DEBUG DO QUE ESTÁ A LER DO FICHEIRO
		}
	}
	fclose(ptr_file); 
	return 0; 
}

void saveMoveToFile(char * fileName, NODE *stack) {
	FILE * ptr_file; 
	ptr_file = fopen(fileName, "w"); 
	MOVIMENTO this_move; 
	this_move = pop(stack);
	printf("VALORX:%d\n",this_move.X);
	fprintf(ptr_file, "%d,%d,%d\n", this_move.X, this_move.Y, this_move.Valor);
	
	while ((stack)->next != NULL) {
		printf("VALORX:%d\n",this_move.X);
		fprintf(ptr_file, "%d,%d,%d\n", this_move.X, this_move.Y, this_move.Valor);
		this_move = pop(stack); 
	
	}

	fclose(ptr_file);  
}

NODE* readMoveFromFile(char * fileName) {
	FILE * ptr_file; 
	NODE * temp = (NODE*) malloc(sizeof(NODE)); 
	ptr_file = fopen(fileName, "r"); 
	MOVIMENTO this_move =  {0};
	while ((fscanf(ptr_file, "%d,%d,%d\n",  &(this_move.X),  &(this_move.Y),  &(this_move.Valor))) != EOF) {
		pushMove( temp, this_move); 
	}
	fclose(ptr_file); 
	return temp; 
}
void saveEstadoToFile(char *estadoStr, char * fileName) {
	FILE * ptr_file; 
	ptr_file = fopen(fileName, "w"); 
	if ( !(ptr_file))
		return;  
	fputs(estadoStr, ptr_file); 
	fclose(ptr_file); 
}

char* readEstadoFromFile(char * fileName) {
	char buffer[10240]; 
	FILE * ptr_file; 
	ptr_file = fopen(fileName, "r"); 
	fgets(buffer, 10240, ptr_file); 
	fclose(ptr_file); 
	return buffer;
}

int fileExist(char * fileName) {
	FILE * ptr_file; 
	ptr_file = fopen(fileName, "r"); 
	if ( !ptr_file) {
		return 0;
	}
	fclose(ptr_file); 
	return 1; 
}

char * appendTxtToString(char * fileName) {
	char buffer[1000]; 
	strcpy(buffer, LOCATION); 
	strcat(buffer, fileName); 
	strcat(buffer, ".txt"); 
	return buffer; 
}
char * appendTxtToStringSTACK(char * fileName) {
	char buffer[1000]; 
	strcpy(buffer, LOCATIONSTACK); 
	strcat(buffer, fileName); 
	strcat(buffer, ".txt"); 
	return buffer; 
}
