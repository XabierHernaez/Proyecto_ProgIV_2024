#include "usuario.h"
#include <stdio.h>
#include <string.h>
Usuario datosUsuarioR()
{
	Usuario u;
	printf("Porfavor introduzca los siguientes campos:\n");
	printf("---------\n");

	printf("Nombre: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.nombre);

	printf("Primer apellido: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.primerApellido);

	printf("Segundo apellido: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.segundoApellido);

	printf("dni: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.dni);

	printf("Usuario: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.usuario);

	printf("Contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);

	printf("Telefono: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &u.telefono);

	char tipo = 'C';
	u.tipo = tipo;

	return u;
}
Usuario datosUsuarioI()
{
	Usuario u;
	printf("Usuario: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.usuario);

	printf("Contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(u.contrasenya);

	return u;
}
int contraseniaCorrecta(char *conU, char *con)
{
	int correcta = 0;
	if(strcmp(conU, con) == 0){
		correcta = 1;
	}
	return correcta;
}
char mostrarDatosUsuario(Usuario u)
{
	char opcion;
	printf("Nombre: %s\n", u.nombre);
	printf("Primer apellido: %s\n", u.primerApellido);
	printf("Segundo apellido: %s\n", u.segundoApellido);
	printf("DNI: %s\n", u.dni);
	printf("Usuario: %s\n", u.usuario);
	printf("Contraseña: %s\n", u.contrasenya);
	printf("Telefono: %d\n", u.telefono);
	printf("Tipo: %c\n",u.tipo);
	printf("Porfavor, mire si los campos son correctos introduzca [1], si hay algun error introduzca [2]: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c", &opcion);
	return opcion;


}
int tipoUsuario(char tipo)
{
	if(tipo == 'A'){
		return 1;
	}else{
		return -1;
	}
}
