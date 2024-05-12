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
ListaHabitacion::~ListaHabitacion()
{
	delete[] listaHabitacion;
}

