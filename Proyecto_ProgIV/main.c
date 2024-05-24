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

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512], mensajeLog[200];


	strcpy(mensajeLog, "Initialising Winsock...");
	ficheroLog(mensajeLog, "","log.txt");
	//printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		snprintf(mensajeLog, sizeof(mensajeLog), "Failed. Error Code : %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		//printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	strcpy(mensajeLog, "Initialised.");
	ficheroLog(mensajeLog, "","log.txt");
	//printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		snprintf(mensajeLog, sizeof(mensajeLog), "Could not create socket : %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		//printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	strcpy(mensajeLog, "Socket created.");
	ficheroLog(mensajeLog, "","log.txt");
	//printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		snprintf(mensajeLog, sizeof(mensajeLog),"Connection error: %d",  WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		//printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	snprintf(mensajeLog, sizeof(mensajeLog),"Connection stablished with: %s (%d)",  inet_ntoa(server.sin_addr),ntohs(server.sin_port));
	ficheroLog(mensajeLog, "","log.txt");
	//printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
	//ntohs(server.sin_port));


	char opcion, opcion2, opcion3,opcion4, opcion5, opcion6, opcion7, opcion8, opcion9;
	int posU, contraCorrecta, tipoU, numP, fechaCorrecta, numHD, numHabitacionUsaurio, posH, numReserAct, reservaCorrecta, fechaCorrecta2, contR, tamH, tamU, tamR, numH3, posH2, telCorrec, dniCorrec,numUsuariosUnicos;
	char mensaje1[100];
	char mensaje2[100];
	char mensaje3[100];
	char mensaje4[100];
	char mensaje5[100];
	char mensaje6[100];
	char **listaUsuario;
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
		snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion);
		ficheroLog(mensajeLog, "","log.txt");
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
			strcpy(mensajeLog, "Ingresa el usuario y contraseña");
			ficheroLog(mensajeLog, u.usuario,"log.txt");
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%d",&posU);
			if(posU != -1){
				strcpy(mensajeLog, "Se valida si el usuario ya existe");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				recv(s,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%d",&contraCorrecta);
				if(contraCorrecta == 1){
					strcpy(mensajeLog, "Se valida si la contraseña ya existe");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%d",&tipoU);
					if(tipoU == 0){
						do {
							strcpy(mensajeLog, "Validacion correcta, ingresa al menu cliente");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							opcion3 = menuCliente();
							sprintf(sendBuff,"%c",opcion3);
							send(s,sendBuff,sizeof(sendBuff),0);
							snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion3);
							ficheroLog(mensajeLog, u.usuario,"log.txt");
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
								strcpy(mensajeLog, "Se le pide la informacion de la reserva");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&fechaCorrecta);
								strcpy(mensajeLog, "Se recibe si la fecha de la reserva es correcta");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								if(fechaCorrecta == 1){
									numP = numeroPersonas();
									strcpy(mensajeLog, "Se pide el numero de persona y se envia");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
									sprintf(sendBuff,"%d",numP);
									send(s,sendBuff,sizeof(sendBuff),0);
									recv(s,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&numHD);
									strcpy(mensajeLog, "Se recibe las habitaciones disponibles");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
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
										strcpy(mensajeLog, "El usuario escoge la habitacion que desea y se la envia");
										ficheroLog(mensajeLog, u.usuario,"log.txt");
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
											strcpy(mensajeLog, "Se recibe la informacion de la habitacion");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											mostrarReserva(r);
											printf("Es correcta la reserva [S/N]: ");
											fflush(stdout);
											fflush(stdin);
											scanf("%c", &opcion6);
											sprintf(sendBuff,"%c",opcion6);
											send(s,sendBuff,sizeof(sendBuff),0);
											snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion6);
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											if(opcion6 == 'S'){
												strcpy(mensajeLog, "Se recibe confirmacion de la reserva");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
												printf("%s %s %s\n", mensaje1, mensaje2, mensaje3);
											}else{
												strcpy(mensajeLog, "Recibe cancelacion de la reserva");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
												printf("%s %s\n", mensaje1, mensaje2);
											}
										}else{
											strcpy(mensajeLog, "Recibe que el numero de habitaciones es erroneo");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											recv(s,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
											printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
										}
									}else{
										strcpy(mensajeLog, "Recibe que no hay habitaciones libres");
										ficheroLog(mensajeLog, u.usuario,"log.txt");
										recv(s,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
										printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
									}
								}else{
									strcpy(mensajeLog, "Recibe que la fecha es incorrecta");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
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
									snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion5);
									ficheroLog(mensajeLog, u.usuario,"log.txt");
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
												sscanf(recvBuff,"%f",&r2.precio);
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
												h4 = buscarHabitacion(lH, r2.habitacion.numA);
												r2.habitacion.numP = h4.numP;
												mostrarReserva(r2);
											}
											strcpy(mensajeLog, "Recibe toda la informacion de las reservas del usuario");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
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
											strcpy(mensajeLog, "Se envia la informacion de la reserva a modificar o borrar");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											if(reservaCorrecta == 1){
												printf("¿Desea borrar su reserva [S/N]?: ");fflush(stdout);fflush(stdin);
												scanf("%c", &opcion7);
												sprintf(sendBuff,"%c",opcion7);
												send(s,sendBuff,sizeof(sendBuff),0);
												snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion7);
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												if(opcion7 == 'S'){
													strcpy(mensajeLog, "Recibe validacion de la transaccion");
													ficheroLog(mensajeLog, u.usuario,"log.txt");
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
													strcpy(mensajeLog, "Se envia la fecha nueva a modificar y recibe si es correcta");
													ficheroLog(mensajeLog, u.usuario,"log.txt");
													if(fechaCorrecta2 == 1){
														strcpy(mensajeLog, "Recibe si hay disponibilidad de fechas");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														recv(s,recvBuff,sizeof(recvBuff),0);
														sscanf(recvBuff,"%d",&contR);
														if(contR == -1){
															strcpy(mensajeLog, "Recibe mensaje de validacion");
															ficheroLog(mensajeLog, u.usuario,"log.txt");
															recv(s,recvBuff,sizeof(recvBuff),0);
															sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
															printf("%s %s\n", mensaje1, mensaje2);
														}else{
															strcpy(mensajeLog, "Recibe validacion de la transaccion erroneo");
															ficheroLog(mensajeLog, u.usuario,"log.txt");
															recv(s,recvBuff,sizeof(recvBuff),0);
															sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
															printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);
														}
													}else{
														strcpy(mensajeLog, "Recibe que la fecha no es correcta");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														recv(s,recvBuff,sizeof(recvBuff),0);
														sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
														printf("%s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4);
													}
												}
											}else{
												strcpy(mensajeLog, "Recibe que no es valida la reserva");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												recv(s,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
												printf("%s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
											}

										}else{
											strcpy(mensajeLog, "Recibe que no se han encotrado reservas");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
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
						/*EMPIEZA EL PROGRAMA ADMINISTRADOR*/
						strcpy(mensajeLog, "Entra en la parte de administrador");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
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
							r5.habitacion.numP = h3.numP;
							r5.habitacion.precio = h3.precio;
							anyadirReserva(&lR, r5);
						}
						strcpy(mensajeLog, "Recibe todos los datos para realizar las operaciones");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						do {
							opcion4 = menuAdministrador();
							sprintf(sendBuff,"%c",opcion4);
							send(s,sendBuff,sizeof(sendBuff),0);
							snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion4);
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							switch(opcion4){
							case '0':
								printf("Saliendo del sistema...\n");fflush(stdout);
								printf("Muchas gracias\n");fflush(stdout);

								sprintf(sendBuff,"%d",lU.numU);
								send(s,sendBuff,sizeof(sendBuff),0);
								for(int i=0;i<lU.numU;i++){
									sprintf(sendBuff,"%s",lU.aUsuario[i].nombre);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%s",lU.aUsuario[i].primerApellido);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%s",lU.aUsuario[i].segundoApellido);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%s",lU.aUsuario[i].dni);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%s",lU.aUsuario[i].usuario);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%s",lU.aUsuario[i].contrasenya);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lU.aUsuario[i].telefono);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%c",lU.aUsuario[i].tipo);
									send(s,sendBuff,sizeof(sendBuff),0);
								}

								sprintf(sendBuff,"%d",lR.numR);
								send(s,sendBuff,sizeof(sendBuff),0);
								for(int i=0;i<lR.numR;i++){
									sprintf(sendBuff,"%s",lR.listaR[i].usuario);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].habitacion.numA);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%f",lR.listaR[i].precio);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].entrada.anyo);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].entrada.mes);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].entrada.dia);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].salida.anyo);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].salida.mes);
									send(s,sendBuff,sizeof(sendBuff),0);
									sprintf(sendBuff,"%d",lR.listaR[i].salida.dia);
									send(s,sendBuff,sizeof(sendBuff),0);
								}
								strcpy(mensajeLog, "Se le envian los datos modificados");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								liberarMemoriaH(&lH);
								liberarMemoriaLU(&lU);
								liberarMemoria(&lR);
								break;
							case '1':
								visualizarReservasActias(lR);
								strcpy(mensajeLog, "Se visualizan todas las reservas");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								printf("Quieres eliminar o modificar alguna reserva[S/N]: ");
								fflush(stdout);
								fflush(stdin);
								scanf("%c", &opcion8);
								snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion8);
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								if(opcion8 == 'S'){
									printf("Rellene la siguinete informacion...\n");fflush(stdout);
									numH3 = numHabitacion();
									r6 = comenzarReserva();
									posH2 = encontrarReserva(lR, r6, numH3);
									strcpy(mensajeLog, "Se pide informacion sobre esa reserva y se mira que exista");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
									if(posH2 != -1){
										printf("Eliminar [1] / Modificar [2]: ");
										fflush(stdout);
										fflush(stdin);
										scanf("%c", &opcion9);
										snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion9);
										ficheroLog(mensajeLog, u.usuario,"log.txt");
										if(opcion9 == '1'){
											strcpy(mensajeLog, "Se elimina la reserva");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											printf("Eliminar reserva...\n");fflush(stdout);
											printf("Reserva eliminada con exito\n");fflush(stdout);
											eliminarReserva(&lR, posH2);
										}else{
											printf("Modificar reserva...\n");fflush(stdout);
											printf("Se modificara solo la fecha de la reserva, si usted quiere añadir mas personas debera eliminar la reserva y volver a realizar una reserva\n");fflush(stdout);
											printf("Porfavor ingrese la nueva fecha...\n");fflush(stdout);
											r7 = comenzarReserva();
											strcpy(mensajeLog, "Se pide informacion sobre la nueva fecha y se comprueba que sea valida");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											if(reservafechaCorrecta(r7) == 1){
													if(disponibilidadHabitacion(lR, r7, numH3) == -1){
														strcpy(mensajeLog, "Reserva modificada");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														printf("Reserva modificada...\n");fflush(stdout);
														modificarReserva(&lR, r7, posH2);
													}else{
														strcpy(mensajeLog, "No se pudo modificar la habitacion en esas fechas");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														printf("Habitacion ocupada en esas fechas\n");fflush(stdout);
													}
											}else{
												strcpy(mensajeLog, "Fecha incorrecta");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												printf("Fecha incorrecta\n");fflush(stdout);
											}
										}
									}
								}
								break;
							case '2':
								listaUsuario = usuariosConReserva(lR, &numUsuariosUnicos);
								strcpy(mensajeLog, "Se sacan todos los usuarios que tengan reserva");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								borrarUsuariosSinReserva(&lU, listaUsuario, numUsuariosUnicos);
								strcpy(mensajeLog, "Se mira uno por uno cada usuario si se elimina de la base de datos");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								break;
							default: break;
							}
						} while (opcion4 != '0');
					}
				}else{
					strcpy(mensajeLog, "Recibe que la contraseña es incorrecta");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s\n", mensaje1, mensaje2);fflush(stdout);
				}
			}else{
				strcpy(mensajeLog, "Recibe que el usuario no existe en la base de datos");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				recv(s,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s %s %s",mensaje1, mensaje2, mensaje3);
				printf("%s %s %s\n", mensaje1, mensaje2, mensaje3);fflush(stdout);
			}
			break;
		case '2':
				printf("A continucacion se va a realizar el registro del usuario...\n");fflush(stdout);
				u = datosUsuarioR();
				strcpy(mensajeLog, 	"Se piden los datos al usuario");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				printf("---------\n");
				fflush(stdout);
				opcion2 = mostrarDatosUsuario(u);
				sprintf(sendBuff,"%c",opcion2);
				send(s,sendBuff,sizeof(sendBuff),0);
				snprintf(mensajeLog, sizeof(mensajeLog),"Selecciona la opcion: %c ",opcion2);
				ficheroLog(mensajeLog, u.usuario,"log.txt");
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
					strcpy(mensajeLog, 	"Se envia los datos y recibe si el usario ya existia");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					if(posU == -1){
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%d",&telCorrec);
						strcpy(mensajeLog, 	"Recibe si el telefono no esta repetido");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						if(telCorrec == -1){
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%d",&dniCorrec);
							strcpy(mensajeLog, 	"Recibe si el dni no esta repetido");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							if(dniCorrec == -1){
								strcpy(mensajeLog, 	"Recibe confirmacion de registro");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4);
								printf("%s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4);fflush(stdout);
								printf("\n");fflush(stdout);
							}else{
								strcpy(mensajeLog, 	"Recibe que el dni existe");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								recv(s,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
								printf("%s %s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);fflush(stdout);
								printf("\n");fflush(stdout);
							}
						}else{
							strcpy(mensajeLog, 	"Recibe que el telefono ya existe");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							recv(s,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
							printf("%s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
						}
					}else{
						strcpy(mensajeLog, 	"Recibe que el usuario introducido esta en uso");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						recv(s,recvBuff,sizeof(recvBuff),0);
						sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
						printf("%s %s %s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
						printf("\n");fflush(stdout);
					}
				}else{
					strcpy(mensajeLog, 	"Recibe que se esta cancelando el registro");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%s %s",mensaje1, mensaje2);
					printf("%s %s", mensaje1, mensaje2);fflush(stdout);
					printf("\n");fflush(stdout);
				}
				break;
		case '3':
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5);
			printf("%s %s %s %s %s\n", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5);fflush(stdout);
			printf("INFORMACION: \n");fflush(stdout);
			printf("-----------\n");fflush(stdout);
			printf("-----------\n");fflush(stdout);
			printf("Inicio Sesion:\n");fflush(stdout);
			printf("	En el inicio de sesion solo tendra que meter el usuario y contraseña introducidos en el registro.\n");fflush(stdout);
			printf("	Si tuviera algun problema con su usuario o contraseña debera notificarlo al personal de trabajo.\n");fflush(stdout);
			printf("-------------\n");fflush(stdout);
			printf("Registro:\n");fflush(stdout);
			printf("	Para completar el registro, se le pediran los datos basicos.\n");fflush(stdout);
			printf("	Una vez completado el registro no tendria que tener problema para realizar el inicio de sesion.\n");fflush(stdout);
			printf("-------------\n");fflush(stdout);
			printf("Realizar una reserva:\n");fflush(stdout);
			printf("	Para realizar una reserva se pediran datos tales como la fecha de entrada y salida.\n");fflush(stdout);
			printf("	A continuacion se le muestra todas las habitaciones disponibles, solo debe escoger una y se completara la reserva.\n");fflush(stdout);
			printf("-------------\n");fflush(stdout);
			printf("Modificar una reserva:\n");fflush(stdout);
			printf("	Para modificar una reserva debera escoger la reserva deseada y tendra dos opciones.\n");fflush(stdout);
			printf("	Si desea eliminarla, solo tendra que confirmarlo y se eliminara automaticamente\n");fflush(stdout);
			printf("	Si desea modificarla tendra que meter la nueva fecha y esperar a que este disponible en esa fecha.\n");fflush(stdout);
			printf("	Recuerde que solo se puede modificar la fecha de la reserva, no se puede añadir mas personas o elegir otra habitacion\n");fflush(stdout);
			printf("-------------\n");fflush(stdout);
			break;
		default:
			recv(s,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s %s %s %s %s %s",mensaje1, mensaje2, mensaje3, mensaje4, mensaje5, mensaje6);
			printf("%s %s %s %s %s %s", mensaje1, mensaje2, mensaje3, mensaje4,  mensaje5, mensaje6);fflush(stdout);
			break;
		}
	} while (opcion != '0');

	closesocket(s);
	WSACleanup();

	return 0;
}
