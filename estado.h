#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O tamanho máximo da grelha */
#define MAX_GRID		20
//                 0      1        2        3    4       5
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O}VALOR; 

/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	char num_lins; 
	int ancora; 
	char X;
	int lastX;
	int lastY;
	int lastVal;
	char Y; 
	char num_cols; 
	char grelha[MAX_GRID][MAX_GRID]; 
}ESTADO; 

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char * estado2str(ESTADO e); 

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char * argumentos); 

#endif
