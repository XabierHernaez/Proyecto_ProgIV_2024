#ifndef LISTAUSUARIOS_H_
#define LISTAUSUARIOS_H_
#include "usuario.h"

typedef struct{
	Usuario *aUsuario;
	int numU;
}ListaUsuarios;

void liberarMemoriaLU(ListaUsuarios *lu); // Liberamos la memoria reservada
void anyadirUsuario(ListaUsuarios *lU, Usuario u);
void visualizarU(ListaUsuarios lU);
/*
ListaUsuarios reservarMemoriaLU(int tam); //Reservamos memoria para la lista de usuarios
void liberarMemoriaLU(ListaUsuarios *lu); // Liberamos la memoria reservada
void anyadirUsuario(ListaUsuarios *lu, Usuario u);
int buscarUsuario(ListaUsuarios lu, char *usuario);
*/
#endif
