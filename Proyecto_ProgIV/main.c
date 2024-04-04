#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "usuario.h"
#include "listaUsuarios.h"
#include "fichero.h"
#define TAM 100
int main(){

	char opcion, opcion2, opcion3, opcion4;
	int posU, tipoU;
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
						tipoU = tipoUsuario(lu.aUsuario[posU].tipo);
						if(tipoU != 1){
							do {
								opcion3 = menuCliente();
								switch(opcion3){
									case '0':
										printf("Saliendo al menu principal...\n");
										fflush(stdout);
										break;
									case '1':
										printf("A continuacion se realizara una reserva paso a paso...\n");
										fflush(stdout);
										break;
									case '2':
										printf("A continuacion se realizara la modificacion de una reserva paso a paso...\n");
										fflush(stdout);
										break;
									default:
										printf("Error. La opcion introducida no es correcta\n");
										fflush(stdout);
										break;
								}
								} while (opcion3 != '0');
						}else{
							do {
								opcion4 = menuAdministrador();
								switch(opcion4){
								case '0':
										printf("Saliendo al menu principal...\n");
										fflush(stdout);
										break;
								case '1':
										printf("Visulizando las reservas activas...\n");
										fflush(stdout);
										break;
								case '2':
										printf("Realizando la asignacion de habitaciones...\n");
										fflush(stdout);
										break;
								case '3':
										printf("Eliminando las reservas pasadas...\n");
										fflush(stdout);
										break;
								default:
										printf("Error. La opcion introducida no es correcta\n");
										fflush(stdout);
										break;
								}
							} while (opcion4 != '0');
						}
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
