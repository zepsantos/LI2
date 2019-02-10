/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

#include "cgi.h"
#include "estado.h"
#include "openFile.h"
#include "ancora.h"
#include "verifica.h"

#define MAX_BUFFER 10240
#define GRELHA 4
#define TAM 40
/**
Concatenação do IP definido no cgi.h com o link 
*/
#define STARTLINK "/cgi-bin/GandaGalo"
#define NOVO IP STARTLINK


char user[32];


/**
Função que inicializa o estado
@returns Um novo estado
*/
ESTADO inicializar() {
	ESTADO e = {0};
	e.ancora= 0;
	e.num_lins = GRELHA; 
	e.num_cols = GRELHA; 
	readGameFromFile( &e, "tabuleiro.txt");	
	saveEstadoToFile(estado2str(e),appendTxtToString(user)); 
	return e; 
}




int isActionType(char *args,char *actionType) {
	char *strToSplit = (char*) malloc(strlen(args)*(sizeof(char)));
	strcpy(strToSplit,args);
	char *token = strtok( strToSplit, "/" );
 	while ( token )
  	{
	if(strcmp(token,actionType) == 0) {
		return 1;
	}
    token = strtok( NULL, "/" );
  	}
	
	return 0; 
	
}
NODE* LoadStack() {
	NODE *top = readMoveFromFile(appendTxtToStringSTACK(user));
	return top;	
}


void handleLoad(ESTADO *e) {
	
	
	if(e->ancora > 0) {
	NODE *top;	
	top = (NODE*)LoadStack();
	while(e->ancora > 0) {
	MOVIMENTO this_move = pop(top);;
	e->grelha[this_move.X][this_move.Y] = this_move.Valor;
	e->ancora--;
	}
	
	}

}


void handleSave(ESTADO *e) {
	NODE *top;
	if(e->ancora > 0) {	
	top = (NODE*)LoadStack();
	} else {
	top = (NODE*) malloc(sizeof(NODE));
	}
	e->ancora++;
	MOVIMENTO this_move;
	this_move.X = e->lastX;
	this_move.Y = e->lastY;
	this_move.Valor = e->lastVal;
	
	pushMove(top,this_move);
	saveMoveToFile(appendTxtToStringSTACK(user),top);

}

void getResume(char *args, char **posx, char **posy,char **val, char **user) {
	char *strToSplit = (char*) malloc(strlen(args)*(sizeof(char)));
	strcpy(strToSplit,args);
	*user = strtok( strToSplit, "/" );
	char *action = strtok( NULL, "/" );
	*posx = strtok( NULL, "/" );
	*posy = strtok( NULL, "/" );
	*val = strtok( NULL, "/" );
}  

ESTADO handleResume(char *args,ESTADO e) {
	
	char *x,*y,*val,*user;
	int posx=0,posy=0,mVal=0;
	getResume(args,&x,&y,&val,&user);
	posx = atoi(x);
	posy = atoi(y);
	mVal = atoi(val);
	e.lastX = posx;
	e.lastY = posy;
	e.lastVal = e.grelha[posx][posy];

	e.grelha[posx][posy] = (VALOR) mVal;
	
	if(e.ancora != 0) {
		handleSave(&e);
		//e.ancora++;
	}  
	saveEstadoToFile(estado2str(e),appendTxtToString(user));
	return e;
} 

void getUser(char *args) {
	char *tempuser;
	char *strToSplit=(char*) malloc(strlen(args)*(sizeof(char)));
	strcpy(strToSplit,args);
	tempuser = strtok(strToSplit,"/");
	strcpy(user,tempuser);
	free(strToSplit);
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/



ESTADO ler_estado(char *args) 
{	
	ESTADO e;
	getUser(args);
	if(!(fileExist(appendTxtToString(user)))) {
		return inicializar();
	} else {
	e = str2estado(readEstadoFromFile(appendTxtToString(user)));
		if(isActionType(args,"resume")) {
			return handleResume(args,e);
		} else if(isActionType(args,"save")) {
			handleSave(&e);
		} else if(isActionType(args,"load")) {
			handleLoad(&e);
		} else if(isActionType(args,"newgame")) {
			return inicializar();
		}
	saveEstadoToFile(estado2str(e),appendTxtToString(user));	
	} 
	return e;
	
} 




VALOR nextVal(VALOR currentVal) {
	VALOR prox[10]; 
	prox[VAZIA] = SOL_X; 
	prox[SOL_X] = SOL_O; 
	prox[SOL_O] = VAZIA; 
	return prox[currentVal];
}

/** 
 * Dá retorno do link de maneira a passar a variavel de ambiente para o próximo movimento
 * @param ESTADO e ,int x , int y , Passa o estado a posição atual x e y
 * @returns O link
 * 
 */

void link(ESTADO e, int x, int y) {
	ESTADO n = e; 
	VALOR next; 
	
	n.X = x; 
	n.Y = y; 
	next = nextVal(n.grelha[x][y]); 
	n.grelha[x][y] = next; 
	while (verifica(n, x, y)) {
		next = nextVal(next); 
		n.grelha[x][y] = next; 
	}

	char buffer[MAX_BUFFER]; 
	sprintf(buffer, "%s/cgi-bin/GandaGalo?%s/%s/%d/%d/%d",IP,user,"resume",x,y,next); 
	ABRIR_LINK(buffer); 
}

/**
 * Imprime o tabuleiro
 * @param Estado e , o estado no momento em que a função é chamada
 * 
 */

void imprime_tabuleiro(ESTADO e) {
	for (int i = 0; i < e.num_lins; i++) {
		for (int j = 0; j < e.num_cols; j++) {
			switch (e.grelha[i][j]) {
			case VAZIA:
				link(e, i, j); 
				IMAGEM(i, j, 40, "vazio.png"); 
				FECHAR_LINK; 
				break; 
			case FIXO_X:
				IMAGEM(i, j, 40, "X.png"); 
				break; 
			case FIXO_O:
				IMAGEM(i, j, 40, "O.png"); 
				break; 
			case BLOQUEADA:
				IMAGEM(i, j, 40, "bloq.png"); 
				break; 
			case SOL_X:
				link(e, i, j); 
				IMAGEM(i, j, 40, "X.png"); 
				FECHAR_LINK; 
				break; 
			case SOL_O:
				link(e, i, j); 
				IMAGEM(i, j, 40, "O.png"); 
				FECHAR_LINK; 
				break; 
			default:
				break; 
			}
		}
	}
}


void actionLink(char *action) {
	char buffer[MAX_BUFFER]; 
	sprintf(buffer, "%s/cgi-bin/GandaGalo?%s/%s/",IP,user,action); 
	ABRIR_LINK(buffer);
}


/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main() {
	ESTADO e = ler_estado(getenv("QUERY_STRING"));

	COMECAR_HTML; 
	ABRIR_SVG(600, 600); 
	imprime_tabuleiro(e);
	printf("ANCORA:%d\n",e.ancora);
	actionLink("newgame"); 
	IMAGEM(2, 0, 80, "novo.png"); 
	FECHAR_LINK;
	actionLink("save");
	IMAGEM(0, 2, 100, "save.png"); // SAVE
	FECHAR_LINK; 
	actionLink("load");
	IMAGEM(3, 4, 50, "undo.png"); //UNDO
	FECHAR_LINK; 
	FECHAR_SVG; 
	FECHAR_HTML; 

	return 0; 
}
