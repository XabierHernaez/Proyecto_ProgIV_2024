#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "habitacion.h"

typedef struct{
	Habitacion *aHabitacion;
	int numH;
	int tam;
}ListaHabitacion;

ListaHabitacion reservarMemoriaH(int tam);
void habitacionesDisponibles(ListaHabitacion aH, int numP,int *numHD);
int buscarHabitacion(ListaHabitacion aH, int numH);
void modificarOcupacionH(ListaHabitacion *aH, int *numH, int cont);
void liberarMemoriaH(ListaHabitacion *aH);

#endif
