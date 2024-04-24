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
void habitacionesDisponibles(ListaHabitacion aH, int numP,int *numHD)
{
	int i;
	*numHD = 0;
	for(i=0;i<aH.numH;i++){
		if(aH.aHabitacion[i].numP == numP && aH.aHabitacion[i].ocupada == 0){
			mostrarHabitacion(aH.aHabitacion[i]);
			(*numHD)++;
		}
	}
}
int buscarHabitacion(ListaHabitacion aH, int numH)
{

	int enc =0, pos = 0;
	while(!enc && pos < aH.numH){
		if(aH.aHabitacion[pos].numA == numH && aH.aHabitacion[pos].ocupada == 0){
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
void modificarOcupacionH(ListaHabitacion *aH, int *numH, int cont)
{
	int i, j = 0;
	for(i=0;i<cont;i++){
		for(j=0;j<aH->numH;j++){
			if(aH->aHabitacion[j].numA == numH[i]){
				aH->aHabitacion[j].ocupada = 1;
			}
		}
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

