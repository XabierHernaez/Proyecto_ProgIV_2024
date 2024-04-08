#ifndef RESERVA_H_
#define RESERVA_H_

#include <stdio.h>
#include "habitacion.h"
#include "usuario.h"

typedef struct
{
	int dia;
	int mes;
	int año;
}Fecha;

typedef struct{
	Usuario usuario;
	Fecha entrada;
	Fecha salida;
	Habitacion habitacion;
}Reserva;

Reserva comenzarReserva();
int fechaFormatoCorrecto(Fecha f);
void modificarReserva(Reserva *r);
#endif
