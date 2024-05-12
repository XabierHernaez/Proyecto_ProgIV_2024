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

#include <stdio.h>
#include <winsock2.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]){
	/*
	char opcion, opcion2, opcion3, opcion4, opcion5, opcion6, opcion7;
	int posU, tipoU, numHDisponibles, numReserH, *numHreser, contHDis, contR;
	Usuario u;
	ListaUsuarios lu;
	ListaHabitacion lH;
	ListaReservas lR;
	Reserva r, r2, r3;
	lH = reservarMemoriaH(TAM);
	lu = reservarMemoriaLU(TAM);
	lR = reservarMemoria(TAM);
	Habitacion h2;
	volcadoFicheroListaU(&lu,"usuarios.txt");
	volcadoFicheroListaH(&lH, "habitaciones.txt");
	volcadoFicheroListaR(&lR, "reservas.txt");
	*/
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
	ntohs(server.sin_port));


	char opcion, opcion2, opcion3;
	int posU, contraCorrecta, tipoU;
	char mensaje1[100];
	char mensaje2[100];
	char mensaje3[100];
	char mensaje4[100];
	char mensaje5[100];
	char mensaje6[100];
	Usuario u;
	do {
		opcion = menuPrincipal();
		sprintf(sendBuff,"%c",opcion);
		send(s,sendBuff,sizeof(sendBuff),0);
		switch(opcion){
		case '0':
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
			printf("%s %s %s", mensaje1, mensaje2, mensaje3);fflush(stdout);
			printf("\n");fflush(stdout);
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
			printf("%s %s", mensaje1, mensaje2);fflush(stdout);
			printf("\n");fflush(stdout);
			break;
		case '1':
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
			printf("%s %s %s\n", mensaje1, mensaje2, mensaje3);fflush(stdout);
			u = datosUsuarioI();
			sprintf(sendBuff,"%s",u.usuario);
			send(s,sendBuff,sizeof(sendBuff),0);
			sprintf(sendBuff,"%s",u.contrasenya);
			send(s,sendBuff,sizeof(sendBuff),0);
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%d",&posU);
			if(posU != -1){
				recv(s,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%d",&contraCorrecta);
				if(contraCorrecta == 1){
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%d",&tipoU);
					if(tipoU != -1){
						do {
							opcion3 = menuCliente();
							sprintf(sendBuff,"%c",opcion3);
							send(s,sendBuff,sizeof(sendBuff),0);
							switch(opcion3){
							case '0':
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s",mensaje1);
								printf("%s\n", mensaje1);fflush(stdout);
								break;
							case '1':
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
								printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
								break;
							case '2':
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
								printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
								break;
							default:
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
								printf("%s %s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
								break;
							}
						} while (opcion3 != '0');
					}else{

					}
				}else{
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
				}
			}else{
				recv(s,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
				printf("%s %s %s\n", mensaje1, mensaje2, mensaje3);fflush(stdout);
			}
			break;
		case '2':
				printf("A continucacion se va a realizar el registro del usuario...\n");fflush(stdout);
				u = datosUsuarioR();
				printf("---------\n");
				fflush(stdout);
				opcion2 = mostrarDatosUsuario(u);
				sprintf(sendBuff,"%c",opcion2);
				send(s,sendBuff,sizeof(sendBuff),0);
				if(opcion2 == '1'){
					sprintf(sendBuff,"%s",u.nombre);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",u.primerApellido);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",u.segundoApellido);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",u.dni);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",u.usuario);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%s",u.contrasenya);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%d",u.telefono);
					send(s,sendBuff,sizeof(sendBuff),0);
					sprintf(sendBuff,"%c",u.tipo);
					send(s,sendBuff,sizeof(sendBuff),0);
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%d",&posU);
					if(posU == -1){
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
						printf("%s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
						printf("\n");fflush(stdout);
					}else{
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
						printf("%s %s %s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
						printf("\n");fflush(stdout);
					}
				}else{
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s", mensaje1, mensaje2);fflush(stdout);
					printf("\n");fflush(stdout);
				}
				break;
		default:
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
			printf("%s %s %s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
			printf("\n");fflush(stdout);
			break;
		}
	} while (opcion != '0');

	closesocket(s);
	WSACleanup();
	/*
	 *
	do{
		opcion = menuPrincipal();
		switch(opcion){
			case '0':
				//ficheroLog("Selecciona la opcion de salir", "fichero.log");
				printf("Saliendo del sistema...\n");
				printf("Muchas gracias.");
				fflush(stdout);
				break;
			case '1':
				printf("A continucacion se va a realizar el inicio de sesion del usuario...\n");fflush(stdout);
				u = datosUsuarioI();
				ficheroLog("Realiza el inicio de sesion de datos", u.usuario, "fichero.log");
				posU = buscarUsuario(lu, u.usuario);
				ficheroLog("Se busca en la lista de usuarios si exite",u.usuario, "fichero.log");
				if(posU != -1){
					if(contraseniaCorrecta(u.contrasenya, lu.aUsuario[posU].contrasenya) == 1){
						ficheroLog("El usuario inicio sesion",u.usuario, "fichero.log");
						printf("Bienvenido %s\n", lu.aUsuario[posU].nombre);fflush(stdout);
						ficheroLog("Registro de movimientos del usuario", u.usuario, "fichero.log");
						ficheroLog("----------------",u.usuario, "fichero.log");
						tipoU = tipoUsuario(lu.aUsuario[posU].tipo);
						if(tipoU != 1){
							do {
								ficheroLog("Entra en el menu dedicado a los clientes",u.usuario, "fichero.log");
								opcion3 = menuCliente();
								switch(opcion3){
									case '0':
										ficheroLog("Selecciona la opcion de salir",u.usuario, "fichero.log");
										printf("Saliendo al menu principal...\n");
										fflush(stdout);
										break;
									case '1':
										ficheroLog("Selecciona la opcion de realizar una reserva",u.usuario, "fichero.log");
										printf("A continuacion se realizara una reserva paso a paso...\n");fflush(stdout);
										r = comenzarReserva();
										int numP = numeroPersonas();
										if(fechaCorrecta(r) == 1){
											ficheroLog("Rellena los datos de la reserva correctamente",u.usuario, "fichero.log");
											printf("Comprobando disponibilidad...\n");fflush(stdout);
											printf("A continuacion se muestran las habitaciones disponibles...\n");fflush(stdout);
											numHreser = habitacionesDisponiblesReserva(lR, r,numP, &contHDis);
											modificarOcupacionH(&lH, numHreser, contHDis);
											habitacionesDisponibles(lH, numP, &numHDisponibles);
											ficheroLog("Se le muestran las habiatciones disponibles de acuerdo con su fecha introducida",u.usuario, "fichero.log");
											if(numHDisponibles > 0){
												ficheroLog("Hay habitaciones disponibles",u.usuario, "fichero.log");
												int numH = numHabitacion();
												int posH = buscarHabitacion(lH, numH);
												if(posH != -1){
													ficheroLog("Escoge una habitacion",u.usuario, "fichero.log");
													h2 = lH.aHabitacion[posH];
													realizarReserva(&r, h2,u.usuario);
													mostrarReserva(r);
													printf("Es correcta la reserva [S/N]: ");
													fflush(stdout);
													fflush(stdin);
													scanf("%c", &opcion6);
													if(opcion6 == 'S'){
														ficheroLog("Realiza la reserva de esa habitacion",u.usuario, "fichero.log");
														anyadirReserva(&lR, r);
														volcadoListaRFichero(lR, "reservas.txt");
														printf("Habitacion reservada\n");fflush(stdout);
														ocupacionLibre(&lH, numHreser, contHDis);
													}else{
														ficheroLog("No realiza la reserva de esa habitacion",u.usuario, "fichero.log");
														printf("La reserva se ha cancelado con exito\n");fflush(stdout);
														ocupacionLibre(&lH, numHreser, contHDis);
													}
												}else{
													ficheroLog("Ingresa un numero de habitacion erroneo",u.usuario, "fichero.log");
													printf("No se ha encontrado la habitacion\n");fflush(stdout);
													ocupacionLibre(&lH, numHreser, contHDis);
												}
											}else{
												ficheroLog("No hay habitaciones libres en las fechas introducidas por el usuario",u.usuario, "fichero.log");
												printf("Actualmente todas las habitaciones con ese numero de personas estan ocupadas\n");fflush(stdout);
												ocupacionLibre(&lH, numHreser, contHDis);
											}
										}else{
											ficheroLog("Introduce una fecha erronea",u.usuario, "fichero.log");
											printf("La fecha no es correcta\n");fflush(stdout);
										}
										break;
									case '2':
										do {
											ficheroLog("Selecciona la opcion de modificar uan reserva",u.usuario, "fichero.log");
											opcion5 = menuModificarReservaC();
											switch (opcion5) {
											case '0':
												ficheroLog("Sale de la modificacion de la reserva",u.usuario, "fichero.log");
												printf("Se ha cancelado la modificacion\n");fflush(stdout);
												break;
											case '1':
												ficheroLog("Se empieza con la modificacion de la reserva",u.usuario, "fichero.log");
												printf("Reservas actuales...\n");fflush(stdout);
												obtenerReservasUsuario(lR, u.usuario, &numReserH);
												printf("Introduzca el numero y la fecha de la habitacion que deseas modificar o eliminar...\n");fflush(stdout);
												int numH2 = numHabitacion();
												r3 = comenzarReserva();
												if(numReserH > 0 && fechaCorrecta(r3)){
													ficheroLog("El usuario ha introducido el numero y fecha de la reserva antigua",u.usuario, "fichero.log");
													printf("¿Desea borrar su reserva [S/N]?: ");fflush(stdout);fflush(stdin);
													scanf("%c", &opcion7);
													if(opcion7 == 'S'){
														ficheroLog("Se borra esa reserva",u.usuario, "fichero.log");
														eliminarReserva(&lR, numH2, u.usuario, r3);
														printf("La reserva se ha eliminado con exito\n");fflush(stdout);
														printf("Reservas actuales...\n");fflush(stdout);
														obtenerReservasUsuario(lR, u.usuario, &numReserH);
														volcadoListaRFichero(lR, "reservas.txt");
													}else{
														ficheroLog("Se modifica la fecha",u.usuario, "fichero.log");
														printf("Se modificara solo la fecha de la reserva, si usted quiere añadir mas personas debera eliminar la reserva y volver a realizar una reserva\n");fflush(stdout);
														printf("Porfavor ingrese la nueva fecha...\n");fflush(stdout);
														r2 = comenzarReserva();
														if(fechaCorrecta(r2)){
															contR = conthabitacionesDisponiblesReserva(lR, r2, numH2);
															ficheroLog("Introduce la nueva fecha y se mira que haya habitaciones disponibles y la fecha sea correcta",u.usuario, "fichero.log");
															if(contR == -1){
																modificarReserva(&lR, numH2,r2, r3, u.usuario);
																volcadoListaRFichero(lR, "reservas.txt");
																printf("La reserva se ha modificado con exito...\n");fflush(stdout);
																obtenerReservasUsuario(lR, u.usuario, &numReserH);
																ficheroLog("Se modifica la reserva",u.usuario, "fichero.log");
															}else{
																ficheroLog("En las fechas seleccionadas no se puede reservar",u.usuario, "fichero.log");
																printf("En esas fechas exite una reserva activa\n");
																fflush(stdout);
															}
														}else{
															ficheroLog("Introduce una fecha erronea",u.usuario, "fichero.log");
															printf("Error. Fecha incorrecta\n");fflush(stdout);
														}
													}
												}else{
													ficheroLog("No tiene reservas",u.usuario, "fichero.log");
													printf("No se han encontrado reservas a su nombre\n");fflush(stdout);
												}
												}
											} while (opcion5 != '0');
											break;

									default:
										printf("Error. La opcion introducida no es correcta o realize alguna reserva\n");
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
						ficheroLog("La contraseña introducida es erronea",u.usuario, "fichero.log");
						printf("La contraseña es incorrecta\n");fflush(stdout);
					}
				}else{
					ficheroLog("El usuario no se ha encontrado",u.usuario, "fichero.log");
					printf("Error. No se ha encontrado al usuario\n");
				}
				break;

			case '2':
				printf("A continucacion se va a realizar el registro del usuario...\n");fflush(stdout);
				u = datosUsuarioR();
				ficheroLog("Selecciona la opcion de registro de un usuario",u.usuario, "fichero.log");
				printf("Porfavor revise sus datos\n");
				printf("---------\n");
				fflush(stdout);
				opcion2 = mostrarDatosUsuario(u);
				if(opcion2 == '1'){
					posU = buscarUsuario(lu, u.usuario);
					if(posU != -1){
						ficheroLog("Existe ese usuario",u.usuario, "fichero.log");
						printf("Porfavor introduzca otro nombre de usuario\n");
						fflush(stdout);
					}else{
						ficheroLog("Se añade ese usuario",u.usuario, "fichero.log");
						anyadirUsuario(&lu, u);
						anyadirUsuarioAlFichero(u, "usuarios.txt");
					}
				}else{
					ficheroLog("Selecciona la opcion de cancelar el registro",u.usuario, "fichero.log");
					printf("Registro cancelado...\n");
					printf("Volviendo a la pagina principal.\n");
				}
				break;
			default:
				ficheroLog("Introduce una opcion erronea", u.usuario, "fichero.log");
				printf("Error. La opcion introducida no es correcta\n");
				fflush(stdout);
				break;
		}
	}while(opcion != '0');

	ficheroLog("Se termina el programa",u.usuario, "fichero.log");
	ficheroLog("-------------------------------------------------",u.usuario, "fichero.log");
	liberarMemoriaLU(&lu);
	liberarMemoria(&lR);
	liberarMemoriaH(&lH);
	*/
	return 0;
}
