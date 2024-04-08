#include "listaHabitacion.h"
#include <stdlib.h>
#include <stdio.h>
ListaHabitacion reservarMemoriaH(int tam)
{
	ListaHabitacion lH;
	lH.numH =0;
	lH.tam = tam;
	lH.aHabitacion = (Habitacion*)malloc(tam*sizeof(Habitacion));
	return lH;
}
void habitacionesDisponibles(ListaHabitacion aH, int numP)
{
	int i;
	for(i=0;i<aH.numH;i++){
		if(aH.aHabitacion[i].numP == numP && aH.aHabitacion[i].ocupada == 0){
			mostrarHabitacion(aH.aHabitacion[i]);
		}
	}
}
int buscarHabitacion(ListaHabitacion aH, int numH)
{

	int enc =0, pos;
	while(!enc && pos < aH.numH){
		if(aH.aHabitacion[pos].numA == numH){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc){
		return pos;
	}else{
		return -1;
	}
}
void liberarMemoriaH(ListaHabitacion *aH)
{
	free(aH);
}
