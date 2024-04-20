#ifndef FICHERO_H_
#define FICHERO_H_
#include "listaUsuarios.h"
#include "listaHabitacion.h"

void volcadoFicheroListaU(ListaUsuarios *lu, char *nomFich);
void anyadirUsuarioAlFichero(Usuario u, char *nomFich);
void volcadoFicheroListaH(ListaHabitacion *aH, char * nomFich);
void volcadoListaHaFichero(ListaHabitacion aH, char *nomFich);

#endif
