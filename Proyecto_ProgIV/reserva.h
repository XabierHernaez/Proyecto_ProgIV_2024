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
}Reserva;

Reserva comenzarReserva();
int fechaCorrecta(Fecha f);
void mostrarReserva(Reserva r);
int numHabitacion();
Reserva realizarReserva(Habitacion h, char * usuario, Fecha entrada, Fecha salida);
#endif
