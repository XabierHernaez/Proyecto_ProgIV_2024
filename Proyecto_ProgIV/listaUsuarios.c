#include "listaUsuarios.h"
#include <stdio.h>
#include <stdlib.h>
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
