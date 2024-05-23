
#ifndef HABITACION_H_
#define HABITACION_H_

typedef struct{
	int numA;
	char *tipo;
	int numP;
	float precio;
	int ocupada;
}Habitacion;

int numeroPersonas();
void mostrarHabitacion(Habitacion h);
#endif
