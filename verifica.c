#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "verifica.h"



int igual(VALOR v1, VALOR v2) {
	if (v1 == v2)
		return 1; 
	if (v1 == SOL_X && v2 == FIXO_X)
		return 1; 
	if (v1 == SOL_O && v2 == FIXO_O)
		return 1; 
	if (v1 == FIXO_X && v2 == SOL_X)
		return 1; 
	if (v1 == FIXO_O && v2 == SOL_O)
		return 1; 
	return 0; 
}

int verifica(ESTADO e, int l, int c) {

	if (e.grelha[l][c] != VAZIA) {
		//cima vertical
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && l + 2 < e.num_lins) {
			if (igual(e.grelha[l][c], e.grelha[l + 1][c]) && igual(e.grelha[l][c], e.grelha[l + 2][c]))
				return 1; 
		}
		//baixo vertical
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && l - 2 >= 0) {
			if (igual(e.grelha[l][c], e.grelha[l - 1][c]) && igual(e.grelha[l][c], e.grelha[l - 2][c]))
				return 1; 
		}
		//esquerda horizontal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c + 2 < e.num_cols) {
			if (igual(e.grelha[l][c], e.grelha[l][c + 1]) && igual(e.grelha[l][c], e.grelha[l][c + 2]))
				return 1; 
		}
		//direita  horizontal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c - 2 >= 0) {
			if (igual(e.grelha[l][c], e.grelha[l][c - 1]) && igual(e.grelha[l][c], e.grelha[l][c - 2]))
				return 1; 
		}
		//direita superior diagonal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c - 2 >= 0 && l + 2 < e.num_lins) {
			if (igual(e.grelha[l][c], e.grelha[l + 1][c - 1]) && igual(e.grelha[l][c], e.grelha[l + 2][c - 2]))
				return 1; 
		}
		//esquerda superior diagonal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c + 2 < e.num_cols && l + 2 < e.num_lins) {
			if (igual(e.grelha[l][c], e.grelha[l + 1][c + 1]) && igual(e.grelha[l][c], e.grelha[l + 2][c + 2]))
				return 1; 
		}
		//direita inferior diagonal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c - 2 >= 0 && l - 2 >= 0) {
			if (igual(e.grelha[l][c], e.grelha[l - 1][c - 1]) && igual(e.grelha[l][c], e.grelha[l - 2][c - 2]))
				return 1; 
		}
		//esquerda inferior diagonal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c + 2 < e.num_cols && l - 2 >= 0) {
			if (igual(e.grelha[l][c], e.grelha[l - 1][c + 1]) && igual(e.grelha[l][c], e.grelha[l - 2][c + 2]))
				return 1; 
		}
		//meio horizontal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && c - 1 >= 0 && c + 1 < e.num_cols) {
			if (igual(e.grelha[l][c], e.grelha[l][c - 1]) && igual(e.grelha[l][c], e.grelha[l][c + 1]))
				return 1; 
		}
		// meio vertical
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && l - 1 >= 0 && l + 1 < e.num_lins) {
			if (igual(e.grelha[l][c], e.grelha[l - 1][c]) && igual(e.grelha[l][c], e.grelha[l + 1][c]))
				return 1; 
		}
		// meio diagonal
		if (c >= 0 && l >= 0 && c < e.num_cols && l < e.num_lins && l - 1 >= 0 && l + 1 < e.num_lins && c - 1 >= 0 && c + 1 < e.num_cols) {
			if (igual(e.grelha[l][c], e.grelha[l - 1][c + 1]) && igual(e.grelha[l][c], e.grelha[l + 1][c - 1]))
				return 1; 
			if (igual(e.grelha[l][c], e.grelha[l - 1][c - 1]) && igual(e.grelha[l][c], e.grelha[l + 1][c + 1]))
				return 1; 
		}

		return 0; 
	}
	else
		return 0; 
}