#include "ListaReserva.h"
#include <iostream>
ListaReserva::ListaReserva()
{
	listaR = NULL;
	numR = 0;
}
void ListaReserva::anyadirReserva(const Reserva &r)
{
	if(numR == 0){
		listaR = new Reserva[1];
		listaR[numR] = r;
		numR++;
	}else{
		Reserva *aux = new Reserva[numR];
		int i;
		for(i=0;i<numR;i++){
			aux[i] = listaR[i];
		}
		delete[] listaR;
		listaR = new Reserva[numR+1];
		for(i=0;i<numR;i++){
			listaR[i] = aux[i];
		}
		listaR[numR] = r;
		numR++;
	}
}
int* ListaReserva::habitacionesDisponibles(Reserva r, int numP, int *cont)
{
	int i, *numH, j = 0;
	*cont = 0;
	for(i=0;i<numR;i++){
		//		1               5							3				4
		if((r.entrada.dia - listaR[i].salida.dia <= 0 && r.salida.dia >  listaR[i].entrada.dia&& r.entrada.mes == listaR[i].salida.mes) && listaR[i].habitacion.numP == numP){
			(*cont)++;
		}
	}
	numH = new int[*cont];
	for(i=0;i<numR;i++){
		if((r.entrada.dia - listaR[i].salida.dia < 0 && r.salida.dia >  listaR[i].entrada.dia&& r.entrada.mes == listaR[i].salida.mes) && listaR[i].habitacion.numP == numP){
			numH[j] = listaR[i].habitacion.numA;
			j++;
		}
	}
	return numH;
}
ListaReserva::~ListaReserva() {
	if(listaR != NULL){
		delete[] listaR;
	}
}

