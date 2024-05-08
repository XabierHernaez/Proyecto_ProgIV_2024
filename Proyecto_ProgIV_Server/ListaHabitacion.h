
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
	virtual ~ListaHabitacion();
};

#endif
