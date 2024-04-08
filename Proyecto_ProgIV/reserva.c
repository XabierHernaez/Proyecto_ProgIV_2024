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
void mostrarReserva(Reserva r){
	printf("Tu reserva actual es:\nUsuario: %s, Fecha de entrada: %d/%d/%d, Fecha de salida: %d/%d/%d, Num huespedes: %d\n",
			r.usuario,r.entrada.dia,r.entrada.mes,r.entrada.anyo,r.salida.dia,r.salida.mes,r.salida.anyo,r.habitacion.numP);
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

Reserva realizarReserva(Habitacion h, char *usuario, Fecha entrada, Fecha salida)
{
	Reserva r;
	h.ocupada = 1;
	r.habitacion = h;
	r.entrada = entrada;
	r.salida = salida;
	r.usuario = usuario;
	return r;
}

