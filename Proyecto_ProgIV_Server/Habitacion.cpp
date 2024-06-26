#include "Habitacion.h"
#include <string.h>
#include <iostream>
using namespace std;
Habitacion::Habitacion()
{
	numA = 0;
	tipo = new char[1];
	tipo[0] = '\0';
	numP = 0;
	precio = 0.0;
	ocupada = 0;
}
Habitacion::Habitacion(int nH, char * tipo, int nP, float p, int o)
{
	numA = nH;
	this->tipo = new char(strlen(tipo)+1);
	strcpy(this->tipo, tipo);
	numP = nP;
	precio = p;
	ocupada = o;
}
Habitacion::Habitacion(const Habitacion &a)
{
	numA = a.numA;
	this->tipo = new char(strlen(a.tipo)+1);
	strcpy(this->tipo, a.tipo);
	numP = a.numP;
	precio = a.precio;
	ocupada = a.ocupada;
}
void Habitacion::setNumA(int numA)
{
	this->numA = numA;
}
void Habitacion::setTipo(char *tipo)
{
	delete[] this->tipo;
	this->tipo = new char[strlen(tipo)+1];
	strcpy(this->tipo, tipo);
}
void Habitacion::setNumP(int numP)
{
	this->numP = numP;
}
void Habitacion::setPrecio(float precio)
{
	this->precio = precio;
}
void Habitacion::setOcupada(int ocupada)
{
	this->ocupada = ocupada;
}
int Habitacion::getNumA()
{
	return numA;
}
char * Habitacion::getTipo()
{
	return tipo;
}
int Habitacion::getNumP()
{
	return numP;
}
float Habitacion::getPrecio()
{
	return precio;
}
int Habitacion::getOcupada()
{
	return ocupada;
}
Habitacion& Habitacion::operator=(const Habitacion &r)
{
	numA = r.numA;
	delete[] tipo;
	tipo = new char[strlen(r.tipo)+1];
	strcpy(tipo, r.tipo);
	numP = r.numP;
	precio = r.precio;
	ocupada = r.ocupada;
	return(*this);

}
void Habitacion::visualizarHabitacion()
{
	cout<<"Numero habitacion: "<<numA<<" - Tipo: "<<tipo<<" - Precio: " <<precio<<endl;
}
Habitacion::~Habitacion()
{
	delete[] tipo;
}

