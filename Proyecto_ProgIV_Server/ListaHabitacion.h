
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
	void modificarOcupacion(int *numH, int cont);
	int habitacionesDisponibles(int numP);
	int buscarHabitacion(int numH);
	void mostrarHabitacionesDisponibles(ListaHabitacion &aux, int numP);
	void ocupacionLibre(int *numH, int cont);
	virtual ~ListaHabitacion();
};

#endif
