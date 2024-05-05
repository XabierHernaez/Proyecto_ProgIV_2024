#ifndef FICHERO_H_
#define FICHERO_H_
#include "listaUsuarios.h"
#include "listaHabitacion.h"
#include "listaReservas.h"

void volcadoFicheroListaU(ListaUsuarios *lu, char *nomFich);
void anyadirUsuarioAlFichero(Usuario u, char *nomFich);
void volcadoFicheroListaH(ListaHabitacion *aH, char * nomFich);
void volcadoFicheroListaR(ListaReservas *aR, char *nomFich);
void volcadoListaRFichero(ListaReservas aR, char *nomFich);
void ficheroLog(char *mensaje, char *usuario, char * nomFich);

#endif
