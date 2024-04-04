

#ifndef HABITACION_H_
#define HABITACION_H_

typedef struct{
	int numA; // Numero de habitacio
	char *tipo;
	char *descr;
	int numP; // El numero de personas que entran en la habiatcion
	float precio;
	char ocupada; // 1 ocupada; 0 libre
};

#endif
