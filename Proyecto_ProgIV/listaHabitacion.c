#include "listaHabitacion.h"
#include <stdlib.h>
ListaHabitacion reservarMemoria(int tam)
{
	ListaHabitacion lH;
	lH.numH =0;
	lH.tam = tam;
	lH.aHabitacion = (Habitacion*)malloc(tam*sizeof(Habitacion));
	return lH;
}
void habitacionesDisponibles(ListaHabitacion aH, Habitacion h)
{
	int i;
	for(i=0;i<aH.numH;i++){
		if(aH.aHabitacion[i].numP == h.numP){

		}
	}
}
void liberarMemoria(ListaHabitacion *aH)
{
	free(aH);
}

