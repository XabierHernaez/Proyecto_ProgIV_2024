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
	char opcion, opcion2, opcion3, opcion4, opcion5, opcion6;
	int posU, tipoU, numHDisponibles;
	Usuario u;
	ListaUsuarios lu;
	ListaHabitacion lH;
	ListaReservas lR;
	Reserva r;
	lH = reservarMemoriaH(TAM);
	lu = reservarMemoriaLU(TAM);
	lR = reservarMemoria(TAM);
	Habitacion h2;
	volcadoFicheroListaU(&lu,"usuarios.txt");
	volcadoFicheroListaH(&lH, "habitaciones.txt");
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
										int numP = numeroPersonas();
										if(fechaCorrecta(r) == 1){
											printf("Comprobando disponibilidad...\n");fflush(stdout);
											printf("A continuacion se muestran las habitaciones disponibles...\n");fflush(stdout);
											habitacionesDisponibles(lH, numP, &numHDisponibles);
											if(numHDisponibles > 0){
												int numH = numHabitacion();
												int posH = buscarHabitacion(lH, numH);
												int Hreservada = buscarHabitacionReservada(lR, numH);
												if(posH != -1 && Hreservada != 1){
													h2 = lH.aHabitacion[posH];
													realizarReserva(&r, h2,u.usuario);
													mostrarReserva(r);
													printf("Es correcta la reserva [S/N]: ");
													fflush(stdout);
													fflush(stdin);
													scanf("%c", &opcion6);
													if(opcion6 == 'S'){
														modificarOcupacionH(&lH, posH);
														volcadoListaHaFichero(lH, "habitaciones.txt");
														anyadirReserva(&lR, r);
														printf("Habitacion reservada\n");fflush(stdout);
													}else{
														printf("La reserva se ha cancelado con exito\n");fflush(stdout);
													}
												}else{
													printf("No se ha encontrado la habitacion\n");fflush(stdout);
												}
											}else{
												printf("Actualmente todas las habitaciones con ese numero de personas estan ocupadas\n");fflush(stdout);
											}
										}else{
											printf("La fecha no es correcta\n");fflush(stdout);
										}
										break;
									case '2':
										printf("A continuacion se realizara la modificacion de la reserva paso a paso...\n");
										fflush(stdout);
										do {
											mostrarReserva(r);
											opcion5 = menuModificarReservaC();
											switch (opcion5) {
												case '0':
													printf("Se ha cancelado la modificacion\n");fflush(stdout);
													break;
												case '1':
													printf("Comenzando la modificacion de la resserva...\n");fflush(stdout);
													comenzarReserva();
											}

										} while (opcion5 != '0');
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
