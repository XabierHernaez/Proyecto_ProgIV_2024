#include "listaUsuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ListaUsuarios reservarMemoriaLU(int tam)
{
	ListaUsuarios lu;
	lu.tam = tam;
	lu.numU = 0;
	lu.aUsuario = (Usuario*)malloc(tam * sizeof(Usuario));
	return lu;
}
void liberarMemoriaLU(ListaUsuarios *lu)
{
	free(lu);
}
void anyadirUsuario(ListaUsuarios *lu, Usuario u)
{
	if(lu->numU < lu->tam){
		lu->aUsuario[lu->numU] = u;
		lu->numU++;
		printf("Usuario añadido correctamnete.\n");
		fflush(stdout);
	}else{
		printf("ERROR. La lista de usuarios se encuentra actualmente llena.\n");
		fflush(stdout);
	}

}
int buscarUsuario(ListaUsuarios lu, char *usuario)
{
	int pos = 0, enc = 0;
	while(!enc && pos < lu.numU){
		if(stricmp(lu.aUsuario[pos].usuario, usuario) == 0){
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
