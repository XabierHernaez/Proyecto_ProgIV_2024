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
	printf("3. Ayuda\n");
	printf("Elija una opcion[0-3]: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;
}
char menuCliente()
{
	char opcion;
	printf("MENU CLIENTE\n");
	printf("----------\n");
	printf("0. Salir\n");
	printf("1. Realizar reserva\n");
	printf("2. Modificar reserva\n");
	printf("Elija una opcion[0-2]: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;
}
char menuAdministrador()
{
	char opcion;
	printf("MENU ADMINISTRADOR\n");
	printf("----------\n");
	printf("0. Salir\n");
	printf("1. Visualizar las reservas activas\n");
	printf("2. Eliminar a los usuarios sin reserva\n");
	printf("Elija una opcion[0-2]: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;
}
char menuModificarReservaC()
{
	char opcion;
	fflush(stdout);
	printf("0. Cancelar\n");
	printf("1. Modificar\n");
	printf("Elija una opcion[0-1]: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}
