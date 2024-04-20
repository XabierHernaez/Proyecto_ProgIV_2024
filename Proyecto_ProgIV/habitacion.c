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
	printf("Numero habitacion: %d - Tipo: %s - Precio: %.2f\n",h.numA, h.tipo, h.precio);fflush(stdout);
}
