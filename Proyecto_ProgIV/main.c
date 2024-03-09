#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "usuario.h"
#include "listaUsuarios.h"
#include "fichero.h"
#define TAM 100
int main(){

	char opcion, opcion2;
	Usuario u;
	ListaUsuarios lu;
	lu = reservarMemoriaLU(TAM);
	volcadoFicheroListaU(&lu,"usuarios.txt");
	do{
		opcion = menuPrincipal();
		switch(opcion){
			case '0':
				printf("Saliendo del sistema...\n");
				printf("Muchas gracias.");
				fflush(stdout);
				break;
			case '1': break;
			case '2':
				printf("A continucacion se va a realizar el registro del usuario...\n");fflush(stdout);
				u = datosUsuario();
				printf("Porfavor revise sus datos\n");
				printf("---------\n");
				fflush(stdout);
				opcion2 = mostrarDatosUsuario(u);
				if(opcion2 == '1'){
					anyadirUsuario(&lu, u);
					fflush(stdout);
				}else{
					printf("Registro cancelado...\n");
					printf("Volviendo a la pagina principal.\n");
				}
				break;
			default:
				printf("Error. La opcion introducida no es correcta\n");
				fflush(stdout);
				break;
		}
	}while(opcion != '0');


	liberarMemoriaLU(&lu);



	return 0;
}
