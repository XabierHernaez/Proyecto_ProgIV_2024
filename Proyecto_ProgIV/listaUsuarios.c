#include "listaUsuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liberarMemoriaLU(ListaUsuarios *lu)
{
	free(lu->aUsuario);
}
void anyadirUsuario(ListaUsuarios *lU, Usuario u)
{
	if(lU->numU == 0){
		lU->aUsuario = (Usuario*)malloc(1*sizeof(Usuario));
	}else{
		Usuario *aux = (Usuario*)malloc(lU->numU*sizeof(Usuario));
		for(int i=0;i<lU->numU;i++){
			aux[i] = lU->aUsuario[i];
		}
		free(lU->aUsuario);
		lU->aUsuario = (Usuario*)malloc((lU->numU+1)*sizeof(Usuario));
		for(int i=0;i<lU->numU;i++){
			lU->aUsuario[i] = aux[i];
		}
		free(aux);
	}
	lU->aUsuario[lU->numU] = u;
	(lU->numU)++;
}
/*
ListaUsuarios reservarMemoriaLU(int tam)
{
	ListaUsuarios lu;
	lu.tam = tam;
	lu.numU = 0;
	lu.aUsuario = (Usuario*)malloc(tam * sizeof(Usuario));
	return lu;
}
int buscarUsuario(ListaUsuarios lu, char *usuario)
{
	int pos = 0, enc = 0;
	while(!enc && pos < lu.numU){
		if(strcmp(lu.aUsuario[pos].usuario, usuario) == 0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc){
		return pos;
	}else{
		return -1;
	}
	return pos;
}
*/
