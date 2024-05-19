
#ifndef LISTARESERVAS_H_
#define LISTARESERVAS_H_

#include "reserva.h"

typedef struct{
	Reserva *listaR;
	int numR;
}ListaReservas;

void liberarMemoria(ListaReservas *aR);
void anyadirReserva(ListaReservas *aR, Reserva r);
void visualizarReservasActias(ListaReservas listaR);
int encontrarReserva(ListaReservas listaR, Reserva r, int numH);
void eliminarReserva(ListaReservas *listaR, int posH);
void modificarReserva(ListaReservas *listaR, Reserva nuevaReserva, int posH);
int disponibilidadHabitacion(ListaReservas listaR, Reserva r, int numH);
char** usuariosConReserva(ListaReservas lR, int *numUsuariosUnicos);
int estaEnLista(char **listaUsuarios, int numUsuarios, const char *usuario);

/*
ListaReservas reservarMemoria(int tam);
void obtenerReservasUsuario(ListaReservas aR, char *usuario, int *numReserActu);
void modificarReserva(ListaReservas *aR, int numH, Reserva nuevaReserva, Reserva viejaReserva, char * usuario);
void eliminarReserva(ListaReservas *aR, int numH, char * usuario, Reserva nuevaReserva);
int * habitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numP, int *cont);
int conthabitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numH);
*/
#endif
