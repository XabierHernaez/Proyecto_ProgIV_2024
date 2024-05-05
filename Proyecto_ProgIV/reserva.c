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
	printf("Numero habitacion. %d - Fecha de entrada: %d/%d/%d - Fecha de salida: %d/%d/%d - Num huespedes: %d - precio: %.2f €\n",
			r.habitacion.numA,r.entrada.dia,r.entrada.mes,r.entrada.anyo,r.salida.dia,r.salida.mes,r.salida.anyo,r.habitacion.numP, r.precio);
}
int fechaCorrecta(Reserva r)
{
	if ((r.entrada.anyo == 2024) && (r.entrada.mes >= 1 && r.entrada.mes <= 12) && (r.entrada.dia >= 1 && r.entrada.dia <= 31) && (r.salida.anyo >= 1) && (r.salida.mes >= 1 && r.salida.mes <= 12) && (r.salida.dia >= 1 && r.salida.dia <= 31)
		 && ((r.entrada.mes == r.salida.mes) || (r.entrada.mes - r.salida.mes == -1)) && (r.entrada.dia < r.salida.dia)) {
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

void realizarReserva(Reserva *r, Habitacion h, char *usuario)
{
	h.ocupada = 1;
	r->habitacion = h;
	r->usuario = usuario;
	r->precio = 0;
	r->precio += h.precio * h.numP;

}

