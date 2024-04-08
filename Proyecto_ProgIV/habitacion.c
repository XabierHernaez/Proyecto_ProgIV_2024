#include "habitacion.h"
#include <stdio.h>
#include <string.h>
int numeroPersonas()
{
	int num;
	printf("numero de huspedes: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &num);

	return num;
}
void mostrarHabitacion(Habitacion h)
{
	printf("Numero habitacion: %d - Tipo: %s - Descripcion: %s - Precio: %.3f\n",h.numA, h.tipo,h.descr, h.precio);fflush(stdout);
}
