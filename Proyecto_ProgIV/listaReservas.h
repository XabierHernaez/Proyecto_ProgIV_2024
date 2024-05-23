
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

#endif
