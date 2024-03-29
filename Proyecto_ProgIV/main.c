#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "usuario.h"
#include "listaUsuarios.h"
#include "fichero.h"
#define TAM 100
int main(){

	char opcion, opcion2;
	int posU;
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
			case '1':
				printf("A continucacion se va a realizar el inicio de sesion del usuario...\n");fflush(stdout);
				u = datosUsuarioI();
				posU = buscarUsuario(lu, u.usuario);
				if(posU != -1){
					if(contraseniaCorrecta(u.contrasenya, lu.aUsuario[posU].contrasenya) == 1){
						printf("Bienvenido %s\n", lu.aUsuario[posU].nombre);fflush(stdout);
					}else{
						printf("La contraseña es incorrecta\n");fflush(stdout);
					}
				}else{
					printf("Error. No se ha encontrado al usuario\n");
				}
				break;

			case '2':
				printf("A continucacion se va a realizar el registro del usuario...\n");fflush(stdout);
				u = datosUsuarioR();
				printf("Porfavor revise sus datos\n");
				printf("---------\n");
				fflush(stdout);
				opcion2 = mostrarDatosUsuario(u);
				if(opcion2 == '1'){
					posU = buscarUsuario(lu, u.usuario);
					if(posU != -1){
						printf("Porfavor introduzca otro nombre de usuario\n");
						fflush(stdout);
					}else{
						anyadirUsuario(&lu, u);
						anyadirUsuarioAlFichero(u, "usuarios.txt");
					}
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
