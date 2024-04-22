
#ifndef LISTARESERVAS_H_
#define LISTARESERVAS_H_

#include "reserva.h"

typedef struct{
	Reserva *aR;
	int tam;
	int numR;
}ListaReservas;

ListaReservas reservarMemoria(int tam);
void anyadirReserva(ListaReservas *aR, Reserva r);
void obtenerReservasUsuario(ListaReservas aR, char *usuario, int *numReserActu);
void modificarReserva(ListaReservas *aR, int numH, Reserva nuevaReserva, char * usuario);
void eliminarReserva(ListaReservas *aR, int numH, char * usuario);
int * habitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numP, int *cont);
int conthabitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numH);
void liberarMemoria(ListaReservas *aR);

#endif
