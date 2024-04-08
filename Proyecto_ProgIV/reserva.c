#include "reserva.h"
#include <stdio.h>


Reserva comenzarReserva(){
	Reserva r;

	printf("Rellene los siguientes campos...\n");
	printf("--------\n");

	printf("Fecha de entrada\n");fflush(stdout);
	printf("Dia: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.entrada.dia);

	printf("Mes: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.entrada.mes);

	printf("Año: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.entrada.anyo);

	printf("Fecha de salida\n");fflush(stdout);
	printf("Dia: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.salida.dia);

	printf("Mes: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.salida.mes);

	printf("Año: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&r.salida.anyo);

	return r;

}
void modificarReserva(Reserva *r){

}
int fechaCorrecta(Fecha f)
{
	if((f.anyo > 0) ||(f.mes > 0)||(f.mes < 13)||(f.dia > 0)||(f.dia < 32)){
		return 1;
	}else{
		return 0;
	}
}
int numHabitacion()
{
	int numH;
	printf("Escoga una habitacion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &numH);
	return numH;
}
void realizarReserva(Reserva *r, Habitacion h, char *usuario, Fecha entrada, Fecha salida)
{
	r->habitacion = h;
	r->entrada = entrada;
	r->salida = salida;
	r->usuario = usuario;

}
