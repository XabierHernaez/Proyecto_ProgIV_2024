#include "reserva.h"
#include <stdio.h>

int fechaFomatoCorrecto(Fecha f){
	if(f.año < 0 ||f.mes < 1||f.mes > 12||f.dia < 1||f.dia > 31){
		return 1;
	}else{
		return 0;
	}
}

Reserva comenzarReserva(){
	Reserva r;
	printf("Introduce la Fecha de entrada[dd-mm-yyyy]: ");
	scanf("%d-%d-%d",r.entrada.año,r.entrada.mes,r.entrada.año);
	fflush(stdout);
	fflush(stdin);
	if (fechaFomatoCorrecto(r.entrada)== 1){
		printf("La fecha no tiene el formato especificado o esa fecha no existe");
		fflush(stdout);
		fflush(stdin);
	}

	printf("Introduce la Fecha de salida[dd-mm-yyyy]: ");
	scanf("%d-%d-%d",r.salida.año,r.salida.mes,r.salida.año);
	fflush(stdout);
	fflush(stdin);

	r.habitacion = pedirHabitacion();
	return r;

}
void modificarReserva(Reserva *r){

}
