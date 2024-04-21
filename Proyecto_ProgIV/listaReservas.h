
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
int buscarHabitacionReservada(ListaReservas aR, int numA);
void liberarMemoria(ListaReservas *aR);

#endif
