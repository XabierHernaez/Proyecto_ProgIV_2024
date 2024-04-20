
#ifndef HABITACION_H_
#define HABITACION_H_

typedef struct{
	int numA; // Numero de habitacio
	char *tipo;
	int numP; // El numero de personas que entran en la habiatcion
	float precio;
	int ocupada; // 1 ocupada; 0 libre
}Habitacion;

int numeroPersonas();
void mostrarHabitacion(Habitacion h);
#endif
