#include "habitacion.h"
#include <stdio.h>
#include <string.h>
Habitacion pedirHabitacion()
{
	Habitacion h;
	printf("numero de huspedes: ");
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
