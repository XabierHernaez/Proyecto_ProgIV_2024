#ifndef LISTAHABITACION_H_
#define LISTAHABITACION_H_
#include "habitacion.h"

typedef struct{
	Habitacion *aHabitacion;
	int numH;
}ListaHabitacion;

ListaHabitacion reservarMemoriaH(int tam);
void anyadirHabitacion(ListaHabitacion *lH,Habitacion h, int tam);
Habitacion buscarHabitacion(ListaHabitacion listaH, int numH);
void liberarMemoriaH(ListaHabitacion *aH);



#endif
