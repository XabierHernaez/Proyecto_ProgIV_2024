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
void ListaHabitacion::modificarOcupacion(int *numH, int cont, int numP) {
    if (numH != NULL && cont > 0) {
        for (int j = 0; j < cont; j++) {
            for (int i = 0; i < numE; i++) {
                if (listaHabitacion[i].numA == numH[j]) {
                    listaHabitacion[i].ocupada = 1;
                    break;
                }
            }
        }
    }
}
void ListaHabitacion::modificarOcupacionRestante(int numP)
{
	int i;
	for(i=0;i<numE;i++){
		if(listaHabitacion[i].numP != numP){
			listaHabitacion[i].ocupada = 1;
		}
	}
}
Habitacion* ListaHabitacion::habitacionesDisponibles(int numP, int *numHD)
{
    *numHD = 0;
    for (int i = 0; i < numE; i++) {
        if (listaHabitacion[i].numP == numP && listaHabitacion[i].ocupada == 0) {
            (*numHD)++;
        }
    }
    Habitacion* aux = new Habitacion[*numHD];
    int index = 0;
    for (int i = 0; i < numE; i++) {
        if (listaHabitacion[i].numP == numP && listaHabitacion[i].ocupada == 0) {
            aux[index] = listaHabitacion[i];
            index++;
        }
    }
    return aux;
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
void ListaHabitacion::ocupacionLibre(int cont)
{
	int i;
	for(i=0;i<numE;i++){
		if(listaHabitacion[i].ocupada == 1){
			listaHabitacion[i].ocupada = 0;
		}
	}
}
ListaHabitacion::~ListaHabitacion()
{
	delete[] listaHabitacion;
}

