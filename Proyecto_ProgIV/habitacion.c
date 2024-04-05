#include "habitacion.h"
#include <stdio.h>
#include <string.h>
Habitacion pedirHabitacion()
{
	Habitacion h;
	printf("Fecha de entrada[dd-mm-yyyy]: ");
	fflush(stdout);
	fflush(stdin);
	gets(h.f_entrada);

	printf("Fecha de salida[dd-mm-yyyy]: ");
	fflush(stdout);
	fflush(stdin);
	gets(h.f_salida);

	printf("Fecha el numero de huspedes: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &h.numP);

	return h;
}

int fechaCorrecta(Habitacion h)
{
	if(strcmp(h.f_entrada, h.f_salida)<0){
		return 1;
	}else{
		return -1;
	}
}
