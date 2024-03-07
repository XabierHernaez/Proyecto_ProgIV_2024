#include <stdio.h>
#include "menu.h"

int main(){

	char opcion;
	do{
		opcion = menuPrincipal();
		switch(opcion){
			case '0':
				printf("Saliendo del sistema...\n");
				printf("Muchas gracias.");
				fflush(stdout);
				break;
			case '1': break;
			case '2': break;
			default:
				printf("Error. La opcion introducida no es correcta\n");
				fflush(stdout);
				break;
		}
	}while(opcion != '0');






	return 0;
}
