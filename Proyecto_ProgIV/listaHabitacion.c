#include "listaHabitacion.h"
#include <stdlib.h>
#include <stdio.h>
ListaHabitacion reservarMemoriaH(int tam)
{
	ListaHabitacion lH;
	lH.numH =0;
	lH.aHabitacion = (Habitacion*)malloc(tam*sizeof(Habitacion));
	return lH;
}
void anyadirHabitacion(ListaHabitacion *lH,Habitacion h, int tam)
{
	if(lH->numH < tam){
		lH->aHabitacion[lH->numH] = h;
		(lH->numH)++;
	}
}
Habitacion buscarHabitacion(ListaHabitacion listaH, int numH)
{
	Habitacion h;
	int enc = 0, i = 0;
	while(!enc && i < listaH.numH){
		if(listaH.aHabitacion[i].numA == numH){
			enc = 1;
		}else{
			i++;
		}
	}
	if(enc){
		h = listaH.aHabitacion[i];
		return h;
	}else{
		return h;
	}
}
void liberarMemoriaH(ListaHabitacion *aH)
{

	int i;
	for(i=0;i<aH->numH;i++){
		free(aH->aHabitacion[i].tipo);
	}
	free(aH->aHabitacion);
}

