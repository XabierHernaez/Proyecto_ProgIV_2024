

#ifndef LISTARESERVA_H_
#define LISTARESERVA_H_
#include "Reserva.h"
class ListaReserva {
public:
	Reserva *listaR;
	int numR;
public:
	ListaReserva();
	void anyadirReserva(const Reserva &r);
	int* habitacionesDisponibles(Reserva r, int numP, int *cont);
	Reserva* obtenerReservasUsuario(char *usuario,int *numReser);
	int comprobarReservaCorrecta(Reserva r);
	int contHabitacionesDisponibles(Reserva r);
	virtual ~ListaReserva();
};

#endif
