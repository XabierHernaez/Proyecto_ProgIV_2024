#include "menu.h"
#include <stdio.h>
char menuPrincipal()
{
	char opcion;
	printf("Bienvenido!!!!\n");
	printf("Porfavor, eliga una opcion...\n");
	printf("----------\n");
	printf("0. Salir\n");
	printf("1. Inicio de sesion\n");
	printf("2. Registrarse\n");
	printf("La opcion elegida [0-2] es: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);






	return opcion;
}

