#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "usuario.h"
#include "listaUsuarios.h"
#include "listaHabitacion.h"
#include "fichero.h"
#include "habitacion.h"
#include "reserva.h"
#include "listaReservas.h"
#define TAM 100

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


	char opcion, opcion2, opcion3,opcion4, opcion5, opcion6, opcion7, opcion8, opcion9;
	int posU, contraCorrecta, tipoU, numP, fechaCorrecta, numHD, numHabitacionUsaurio, posH, numReserAct, reservaCorrecta, fechaCorrecta2, contR, tamH, tamU, tamR, numH3, posH2;
	char mensaje1[100];
	char mensaje2[100];
	char mensaje3[100];
	char mensaje4[100];
	char mensaje5[100];
	char mensaje6[100];
	Usuario u, u2;
	Reserva r, r2, r3, r4, r5, r6, r7;
	Habitacion h, h2, h3, h4;

	ListaHabitacion lH;
	ListaUsuarios lU;
	ListaReservas lR;

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
					if(tipoU == 0){
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
							case '1':/*TERMINADO NO MODIFICAR*/
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
								printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
								r = comenzarReserva();
								sprintf(sendBuff,"%d",r.entrada.anyo);
								send(s,sendBuff,sizeof(sendBuff),0);
								sprintf(sendBuff,"%d",r.entrada.mes);
								send(s,sendBuff,sizeof(sendBuff),0);
								sprintf(sendBuff,"%d",r.entrada.dia);
								send(s,sendBuff,sizeof(sendBuff),0);
								sprintf(sendBuff,"%d",r.salida.anyo);
								send(s,sendBuff,sizeof(sendBuff),0);
								sprintf(sendBuff,"%d",r.salida.mes);
								send(s,sendBuff,sizeof(sendBuff),0);
								sprintf(sendBuff,"%d",r.salida.dia);
								send(s,sendBuff,sizeof(sendBuff),0);
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&fechaCorrecta);
								if(fechaCorrecta == 1){
									numP = numeroPersonas();
									sprintf(sendBuff,"%d",numP);
									send(s,sendBuff,sizeof(sendBuff),0);
									recv(s,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&numHD);
									if(numHD > 0){
										for(int i =0;i<numHD;i++){
											char tipo[200];
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&h.numA);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%s",tipo);
											h.tipo = (char*)malloc((strlen(tipo)+1)*sizeof(char));
											strcpy(h.tipo, tipo);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%f",&h.precio);
											mostrarHabitacion(h);
										}
										numHabitacionUsaurio = numHabitacion();
										sprintf(sendBuff,"%d",numHabitacionUsaurio);
										send(s,sendBuff,sizeof(sendBuff),0);
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%d",&posH);
										if(posH != -1){
											char usuario[20];
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%s", usuario);
											r.usuario = (char*)malloc((strlen(usuario)+1)*sizeof(char));
											strcpy(r.usuario, usuario);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d", &r.habitacion.numA);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d", &r.habitacion.numP);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%f", &r.precio);
											mostrarReserva(r);
											printf("Es correcta la reserva [S/N]: ");
											fflush(stdout);
											fflush(stdin);
											scanf("%c", &opcion6);
											sprintf(sendBuff,"%c",opcion6);
											send(s,sendBuff,sizeof(sendBuff),0);
											if(opcion6 == 'S'){
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
												printf("%s %s %s\n", mensaje1, mensaje2, mensaje3);
											}else{
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
												printf("%s %s\n", mensaje1, mensaje2);
											}
										}else{
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
											printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
										}
									}else{
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
										printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
									}
								}else{
									recv(s,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
									printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
								}
								break;
							case '2':
								do{
									recv(s,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
									printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
									opcion5 = menuModificarReservaC();
									sprintf(sendBuff,"%c",opcion5);
									send(s,sendBuff,sizeof(sendBuff),0);
									switch(opcion5){
									case '0':
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
										printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
										break;
									case '1':
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
										printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
										printf("Reservas actuales...\n");fflush(stdout);

										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%d",&numReserAct);
										if(numReserAct > 0){
											for(int i = 0;i<numReserAct;i++){
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.habitacion.numA);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.habitacion.numP);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.habitacion.ocupada);
												char tipo[20];
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s",tipo);
												r2.habitacion.tipo = (char*)malloc(strlen(tipo)*sizeof(char));
												strcpy(r2.habitacion.tipo, tipo);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%f",&r2.habitacion.precio);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.entrada.anyo);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.entrada.mes);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.entrada.dia);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.salida.anyo);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.salida.mes);
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%d",&r2.salida.dia);
												mostrarReserva(r2);
											}

											printf("Introduzca el numero y la fecha de la habitacion que deseas modificar o eliminar...\n");fflush(stdout);
											int numH2 = numHabitacion();
											r3 = comenzarReserva();
											sprintf(sendBuff,"%d",numH2);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.entrada.anyo);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.entrada.mes);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.entrada.dia);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.salida.anyo);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.salida.mes);
											send(s,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r3.salida.dia);
											send(s,sendBuff,sizeof(sendBuff),0);
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&reservaCorrecta);
											printf("%d\n", reservaCorrecta);fflush(stdout);
											if(reservaCorrecta == 1){
												printf("¿Desea borrar su reserva [S/N]?: ");fflush(stdout);fflush(stdin);
												scanf("%c", &opcion7);
												sprintf(sendBuff,"%c",opcion7);
												send(s,sendBuff,sizeof(sendBuff),0);
												if(opcion7 == 'S'){
													recv(s,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
													printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
												}else{
													printf("Se modificara solo la fecha de la reserva, si usted quiere añadir mas personas debera eliminar la reserva y volver a realizar una reserva\n");fflush(stdout);
													printf("Porfavor ingrese la nueva fecha...\n");fflush(stdout);
													r4 = comenzarReserva();
													sprintf(sendBuff,"%d",r4.entrada.anyo);
													send(s,sendBuff,sizeof(sendBuff),0);
													sprintf(sendBuff,"%d",r4.entrada.mes);
													send(s,sendBuff,sizeof(sendBuff),0);
													sprintf(sendBuff,"%d",r4.entrada.dia);
													send(s,sendBuff,sizeof(sendBuff),0);
													sprintf(sendBuff,"%d",r4.salida.anyo);
													send(s,sendBuff,sizeof(sendBuff),0);
													sprintf(sendBuff,"%d",r4.salida.mes);
													send(s,sendBuff,sizeof(sendBuff),0);
													sprintf(sendBuff,"%d",r4.salida.dia);
													send(s,sendBuff,sizeof(sendBuff),0);
													recv(s,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&fechaCorrecta2);
													if(fechaCorrecta2 == 1){
														recv(s,recvBuff,sizeof(recvBuff),0);
														sscanf(recvBuff,"%d",&contR);
														if(contR == -1){
															recv(s,recvBuff,sizeof(recvBuff),0);
															sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
															printf("%s %s\n", mensaje1, mensaje2);
														}else{
															recv(s,recvBuff,sizeof(recvBuff),0);
															sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
															printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);
														}
													}else{
														recv(s,recvBuff,sizeof(recvBuff),0);
														sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
														printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);
													}
												}
											}else{
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
												printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);
											}

										}else{
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
											printf("%s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5);fflush(stdout);
										}

										break;
									default:
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
										printf("%s %s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
										break;
									}
								}while(opcion5 != '0');
								break;
							default:
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
								printf("%s %s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
								break;
							}
						} while (opcion3 != '0');
					}else{
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%d", &tamH);
						lH = reservarMemoriaH(tamH);
						for(int i=0;i<tamH;i++){
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&h2.numA);
							char tipo[20];
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",tipo);
							h2.tipo = (char*)malloc((strlen(tipo)+1)*sizeof(char));
							strcpy(h2.tipo, tipo);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&h2.numP);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&h2.ocupada);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%f",&h2.precio);
							anyadirHabitacion(&lH,h2, tamH);
						}
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%d", &tamU);
						lU.numU = 0;
						for(int i=0;i<tamU;i++){
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.nombre);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.primerApellido);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.segundoApellido);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.dni);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.usuario);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u2.contrasenya);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&u2.telefono);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%c",&u2.tipo);
							anyadirUsuario(&lU,u2);
						}

						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%d", &tamR);
						lR.numR = 0;

						for(int i = 0;i<tamR;i++){
							char u[20];
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",u);
							r5.usuario = (char*)malloc((strlen(u)+1)*sizeof(char));
							strcpy(r5.usuario, u);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.habitacion.numA);
							char t[20];
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s",t);
							r5.habitacion.tipo = (char*)malloc((strlen(t)+1)*sizeof(char));
							strcpy(r5.habitacion.tipo, t);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%f",&r5.precio);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.entrada.anyo);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.entrada.mes);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.entrada.dia);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.salida.anyo);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.salida.mes);
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&r5.salida.dia);
							h3 = buscarHabitacion(lH, r5.habitacion.numA);
							r5.habitacion.numP = h3.numA;
							r5.habitacion.precio = h3.precio;
							anyadirReserva(&lR, r5);
						}
						do {
							opcion4 = menuAdministrador();
							sprintf(sendBuff,"%c",opcion4);
							send(s,sendBuff,sizeof(sendBuff),0);
							switch(opcion4){
							case '0':
								printf("Saliendo del sistema...\n");fflush(stdout);
								printf("Muchas gracias\n");fflush(stdout);
								liberarMemoriaH(&lH);
								liberarMemoriaLU(&lU);
								liberarMemoria(&lR);
								break;
							case '1':
								visualizarReservasActias(lR);
								printf("Quieres eliminar o modificar alguna reserva[S/N]: ");
								fflush(stdout);
								fflush(stdin);
								scanf("%c", &opcion8);
								if(opcion8 == 'S'){
									printf("Rellene la siguinete informacion...\n");fflush(stdout);
									int numH3 = numHabitacion();
									r6 = comenzarReserva();
									posH2 = encontrarReserva(lR, r6, numH3);
									if(posH2 != -1){
										printf("Eliminar [1] / Modificar [2]: ");
										fflush(stdout);
										fflush(stdin);
										scanf("%c", &opcion9);
										if(opcion9 == '1'){
											printf("Eliminar reserva...\n");fflush(stdout);
											printf("Reserva eliminada con exito\n");fflush(stdout);
											eliminarReserva(&lR, posH2);
										}else{
											printf("Modificar reserva...\n");fflush(stdout);
											printf("Se modificara solo la fecha de la reserva, si usted quiere añadir mas personas debera eliminar la reserva y volver a realizar una reserva\n");fflush(stdout);
											printf("Porfavor ingrese la nueva fecha...\n");fflush(stdout);
											r7 = comenzarReserva();
											if(reservafechaCorrecta(r7) == 1){
													if(disponibilidadHabitacion(lR, r7,numH3) == -1){
														printf("Reserva modificada...\n");fflush(stdout);
													modificarReserva(&lR, r7, posH2);
													}else{
														printf("Habitacion ocupada en esas fechas\n");fflush(stdout);
													}
											}else{
												printf("Fecha incorrecta\n");fflush(stdout);
											}
										}
									}
								}
								break;
							case '2': break;
							case '3':break;
							default: break;
							}
						} while (opcion4 != '0');
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
