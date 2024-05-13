#include "ListaHabitacion.h"
#define TAM 90
#include <iostream>
using namespace std;
ListaHabitacion::ListaHabitacion()
{
	listaHabitacion = new Habitacion[TAM];
	numE = 0;
}
void ListaHabitacion::anyadirHabitacion(const Habitacion &h)
{
	if(numE < 90){
		listaHabitacion[numE] = h;
		numE++;
	}
}
void ListaHabitacion::modificarOcupacion(int *numH, int cont)
{
	int i, j;
	for(i=0;i<numE;i++){
		for(j=0;j<cont;j++){
			if(listaHabitacion[i].numA == numH[j]){
				listaHabitacion[i].ocupada = 0;
			}
		}
	}
}
int ListaHabitacion::habitacionesDisponibles(int numP)
{
	int i, numHD = 0;
	for(i=0;i<numE;i++){
		if(listaHabitacion[i].numP == numP && listaHabitacion[i].ocupada == 0){
			numHD++;
		}
	}
	return numHD;
}
int ListaHabitacion::buscarHabitacion(int numH)
{
	int enc =0, pos = 0;
	while(!enc && pos < numE){
		if(listaHabitacion[pos].numA == numH && listaHabitacion[pos].ocupada == 0){
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
void ListaHabitacion::mostrarHabitacionesDisponibles(ListaHabitacion &aux, int numP)
{
	int i;
	for(i=0;i<numE;i++){
		if(listaHabitacion[i].numP == numP && listaHabitacion[i].ocupada == 0){
				aux.anyadirHabitacion(listaHabitacion[i]);
		}
	}
}
void ListaHabitacion::ocupacionLibre(int *numH, int cont)
{
	int i, j;
	for(i=0;i<numE;i++){
		for(j=0;j<cont;j++){
			if(listaHabitacion[i].numA == numH[j]){
				listaHabitacion[i].ocupada = 0;
			}
		}
	}
}
ListaHabitacion::~ListaHabitacion()
{
	delete[] listaHabitacion;
}

