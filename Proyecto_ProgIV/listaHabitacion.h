#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "habitacion.h"

typedef struct{
	Habitacion *aHabitacion;
	int numH;
}ListaHabitacion;

ListaHabitacion reservarMemoriaH(int tam);
void anyadirHabitacion(ListaHabitacion *lH,Habitacion h, int tam);
void liberarMemoriaH(ListaHabitacion *aH);
/*
void habitacionesDisponibles(ListaHabitacion aH, int numP,int *numHD);
int buscarHabitacion(ListaHabitacion aH, int numH);
void modificarOcupacionH(ListaHabitacion *aH, int *numH, int cont);
void ocupacionLibre(ListaHabitacion *aH, int *numH, int cont);
*/


#endif
