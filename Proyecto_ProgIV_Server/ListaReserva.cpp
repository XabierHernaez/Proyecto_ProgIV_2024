#include "ListaReserva.h"
#include <iostream>
#include "string.h"
ListaReserva::ListaReserva()
{
	listaR = NULL;
	numR = 0;
}
void ListaReserva::anyadirReserva(const Reserva &r)
{
	if(numR == 0){
		listaR = new Reserva[1];
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
		delete[] aux;
	}
	listaR[numR] = r;
	numR++;
}
int* ListaReserva::habitacionesDisponibles(Reserva r, int numP, int *cont)
{
	*cont = 0;
	for (int i = 0; i < numR; i++) {
		if (listaR[i].fechaDisponible(r) == 1) {
			(*cont)++;
	        }
	}
	int* numH = new int[*cont];
	int j = 0;
	for (int i = 0; i < numR; i++) {
		if (listaR[i].fechaDisponible(r) == 1) {
			numH[j] = listaR[i].habitacion.numA;
			j++;
		}
	}
	return numH;
}
Reserva* ListaReserva::obtenerReservasUsuario(char *usuario,int *numReser)
{
	int i;
	*numReser =0;
	Reserva *r;
	for(i=0;i<numR;i++){
		if(strcmp(listaR[i].usuario, usuario) == 0){
			(*numReser)++;
		}
	}
	r = new Reserva[*numReser];
	int j = 0;
	for(i=0;i<numR;i++){
		if(strcmp(listaR[i].usuario, usuario) == 0){
			r[j] = listaR[i];
			j++;
		}
	}
	return r;

}
int ListaReserva::comprobarReservaCorrecta(Reserva r)
{
	int i, valido = 0;
	for(i=0;i<numR;i++){
		if(listaR[i].validarReserva(r) == 1){
			valido = 1;
		}
	}
	return valido;
}
int ListaReserva::contHabitacionesDisponibles(Reserva r)
{
	int i = 0, enc = 0;
	while(!enc && i<numR){
		if(listaR[i].validarReserva(r) == 1){
			enc = 1;
		}else{
			i++;
		}
	}
	if(enc){
		return 1;
	}else{
		return -1;
	}
}
ListaReserva::~ListaReserva() {
	if(listaR != NULL){
		delete[] listaR;
	}
}

