#ifndef LISTAUSUARIOS_H_
#define LISTAUSUARIOS_H_
#include "usuario.h"

typedef struct{
	Usuario *aUsuario;
	int numU;
}ListaUsuarios;

void liberarMemoriaLU(ListaUsuarios *lu);
void anyadirUsuario(ListaUsuarios *lU, Usuario u);
void visualizarLU(ListaUsuarios lU);
void eliminarUsuario(ListaUsuarios *lU, int pos);
void borrarUsuariosSinReserva(ListaUsuarios *lU, char **listaU, int contU);

#endif
