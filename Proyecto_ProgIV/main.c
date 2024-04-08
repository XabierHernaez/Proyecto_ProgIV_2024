#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "usuario.h"
#include "listaUsuarios.h"
#include "listaHabitacion.h"
#include "fichero.h"
#include "habitacion.h"
#include "reserva.h"
#include "listaReservas.h"
#define TAM 100
int main(){
	char opcion, opcion2, opcion3, opcion4;
	int posU, tipoU;
	Usuario u;
	ListaUsuarios lu;
	ListaHabitacion lH;
	ListaReservas lR;
	Reserva r, r2;
	lH = reservarMemoriaH(TAM);
	lu = reservarMemoriaLU(TAM);
	lR = reservarMemoria(TAM);
	Habitacion h2;
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
										printf("A continuacion se realizara una reserva paso a paso...\n");fflush(stdout);
										r = comenzarReserva();
										r.usuario = u.usuario;
										int numP = numeroPersonas();
										r.habitacion.numP = numP;
										if(fechaCorrecta(r.entrada) == 1 && fechaCorrecta(r.salida) == 1){
											printf("Comprobando disponibilidad...\n");fflush(stdout);
											printf("A continuacion se muestran las habitaciones disponibles...\n");fflush(stdout);
											habitacionesDisponibles(lH, numP);
											int numH = numHabitacion();
											int posH = buscarHabitacion(lH, numH);
											if(posH == 1){
												h2 = lH.aHabitacion[posH];
												r2 = realizarReserva(h2,u.usuario,r.entrada,r.salida);
												anyadirReserva(&lR, r2);
												printf("Habitacion reservada\n");fflush(stdout);
											}else{
												printf("No se ha encontrado la habitacion\n");fflush(stdout);
											}
										}else{
											printf("La fecha no es correcta\n");fflush(stdout);
										}
										break;
									case '2':
										printf("A continuacion se realizara la modificacion de la reserva paso a paso...\n");
										fflush(stdout);
										modificarReserva(&r);
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
	liberarMemoria(&lR);
	liberarMemoriaH(&lH);

	return 0;
}
