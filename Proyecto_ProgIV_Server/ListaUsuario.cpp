#include "ListaUsuario.h"
#include <iostream>
#include <string.h>
using namespace std;
ListaUsuario::ListaUsuario()
{
	listaUsuario = NULL;
	numU = 0;
}
void ListaUsuario::anyadirUsuario(const Usuario &u)
{
	if(numU == 0){
		listaUsuario = new Usuario[1];
	}else{
		Usuario *aux = new Usuario[numU];
		int i;
		for(i=0;i<numU;i++){
			aux[i] = listaUsuario[i];
		}
		delete[] listaUsuario;
		listaUsuario = new Usuario[numU +1];
		for(i=0;i<numU;i++){
			listaUsuario[i] = aux[i];
		}
		delete[] aux;
	}
	listaUsuario[numU] = u;
	numU++;
}
int ListaUsuario::buscarUsuarioExiste(char *usuario)
{
	int pos = 0, enc = 0;
	while(!enc && pos<numU){
		if(strcmp(listaUsuario[pos].usuario, usuario) == 0){
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
}
ListaUsuario::~ListaUsuario()
{
	if(listaUsuario !=NULL){
		delete[] listaUsuario;
	}
}

