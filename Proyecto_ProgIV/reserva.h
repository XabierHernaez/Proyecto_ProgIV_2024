#ifndef RESERVA_H_
#define RESERVA_H_

#include <stdio.h>
#include "habitacion.h"
#include "usuario.h"

typedef struct
{
	int dia;
	int mes;
	int anyo;
}Fecha;

typedef struct{
	char *usuario;
	Fecha entrada;
	Fecha salida;
	Habitacion habitacion;
	float precio;
}Reserva;

Reserva comenzarReserva();
int reservafechaCorrecta(Reserva r);
void mostrarReserva(Reserva r);
int numHabitacion();
void realizarReserva(Reserva *r, Habitacion h, char * usuario);
#endif
