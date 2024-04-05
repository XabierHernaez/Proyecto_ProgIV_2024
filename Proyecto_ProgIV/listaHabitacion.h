#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "habitacion.h"

typedef struct{
	Habitacion *aHabitacion;
	int numH;
	int tam;
}ListaHabitacion;

ListaHabitacion reservarMemoria(int tam);
void habitacionesDisponibles(ListaHabitacion aH, Habitacion h);
void liberarMemoria(ListaHabitacion *aH);

#endif /* LISTAHABITACION_H_ */
