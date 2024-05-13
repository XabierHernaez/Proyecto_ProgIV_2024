
#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "Habitacion.h"
#define TAM 90
class ListaHabitacion {
public:
	Habitacion *listaHabitacion;
	int numE;
public:
	ListaHabitacion();
	void anyadirHabitacion(const Habitacion &h);
	void modificarOcupacion(int *numH, int cont, int numP);
	Habitacion* habitacionesDisponibles(int numP, int *numHD);
	int buscarHabitacion(int numH);
	void ocupacionLibre(int *numH, int cont);
	virtual ~ListaHabitacion();
};

#endif
