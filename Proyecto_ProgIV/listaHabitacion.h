#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "habitacion.h"

typedef struct{
	Habitacion *aHabitacion;
	int numH;
	int tam;
}ListaHabitacion;

ListaHabitacion reservarMemoriaH(int tam);
void habitacionesDisponibles(ListaHabitacion aH, int numP);
int buscarHabitacion(ListaHabitacion aH, int numH);
void liberarMemoriaH(ListaHabitacion *aH);

#endif /* LISTAHABITACION_H_ */
