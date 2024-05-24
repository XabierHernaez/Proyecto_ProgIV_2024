
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include <winsock2.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;

#include "BaseDatos.h"
#include "ListaHabitacion.h"
#include "Reserva.h"
#include "Usuario.h"
#include "ListaReserva.h"


void ficheroLog(const char *mensaje,const char *usuario,const char * nomFich)
{
	FILE * pf;
	pf = fopen(nomFich, "a");
	if(pf != (FILE*)NULL){
		fprintf(pf, "%s - Usuario: %s\n", mensaje, usuario);
		fclose(pf);
	}
}

int main(int argc, char *argv[]) {


	char mensajeLog[200];

	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo

	strcpy(mensajeLog, "Initialising Winsock...");
	ficheroLog(mensajeLog, "","log.txt");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		snprintf(mensajeLog, sizeof(mensajeLog), "Failed. Error Code : %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		return -1;
	}

	strcpy(mensajeLog, "Initialised.");
	ficheroLog(mensajeLog, "","log.txt");

	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		snprintf(mensajeLog, sizeof(mensajeLog), "Could not create socket : %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		WSACleanup();
		return -1;
	}

	strcpy(mensajeLog, "Socket created.");
	ficheroLog(mensajeLog, "","log.txt");
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		snprintf(mensajeLog, sizeof(mensajeLog),"Bind failed with error code: %d",  WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	strcpy(mensajeLog, "Bind done.");
	ficheroLog(mensajeLog, "","log.txt");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		snprintf(mensajeLog, sizeof(mensajeLog),"Listen failed with error code: %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	strcpy(mensajeLog, "Waiting for incoming connections...");
	ficheroLog(mensajeLog, "","log.txt");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		snprintf(mensajeLog, sizeof(mensajeLog),"accept failed with error code : %d", WSAGetLastError());
		ficheroLog(mensajeLog, "","log.txt");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	snprintf(mensajeLog, sizeof(mensajeLog),"Incomming connection from: %s (%d)", inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	ficheroLog(mensajeLog, "","log.txt");

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	/*EMPIEZA EL PROGRAMA DEL SERVIDOR*/

	ListaHabitacion lH;
	ListaUsuario lU;
	ListaReserva lR;
	sqlite3 *db;

	BaseDatos baseDatos;
	baseDatos.abrirBaseDatos(&db);
	baseDatos.crearTablas(&db);
	//baseDatos.cargarFicheroABaseHabitacion(db);
	//baseDatos.cargarFicheroABaseUsuario(db);
	baseDatos.volcarBaseDatosListaHabitacion(db, lH);
	baseDatos.volcarBaseDatosListaUsuario(db, lU);
	baseDatos.volcarBaseDatosListaReserva(db,lR);


	char opcion, opcion2, opcion3,opcion4, opcion5, opcion6, opcion7;
	int posU, contraCorrecta, tipoU, numP, fechaCorrecta, *numHabitacionesReser, contHDis, numHD, numeroHabitacionUsuario, posH, numReserAct, fechaCorrecta2, contR, telCorrec, dniCorrec, numU, numR;
	char mensaje[200];
	Usuario u, u2;
	Reserva r, r2, r3, r4;
	Habitacion *aux = NULL;
	Reserva *aux2 = NULL;
	Habitacion h;
	do {
		recv(comm_socket,recvBuff,sizeof(recvBuff),0);
		sscanf(recvBuff,"%c",&opcion);
		switch(opcion){
		case '0':
			strcpy(mensaje, "Saliendo del sistema...");
			sprintf(sendBuff,mensaje, "%s %s %s", recvBuff);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			strcpy(mensaje, "Muchas gracias");
			sprintf(sendBuff,mensaje, "%s %s", recvBuff);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			break;
		case '1':
			strcpy(mensaje, "Realizando incio sesion...");
			sprintf(sendBuff,mensaje, "%s %s %s", recvBuff);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			recv(comm_socket,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s",u.usuario);
			recv(comm_socket,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%s",u.contrasenya);
			posU = lU.buscarUsuarioExiste(u.usuario);
			strcpy(mensajeLog, "Ingresa el usuario y contraseña");
			ficheroLog(mensajeLog, u.usuario,"log.txt");
			sprintf(sendBuff,"%d", posU);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			if(posU != -1){
				strcpy(mensajeLog, "Se valida si el usuario ya existe");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				contraCorrecta = u.contraseniaCorrecta(lU.listaUsuario[posU].contrasenya);
				sprintf(sendBuff,"%d", contraCorrecta);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
				if(contraCorrecta == 1){
					strcpy(mensajeLog, "Se valida si la contraseña ya existe");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					strcpy(mensaje, "Bienvenido ");
					strcat(mensaje, u.usuario);
					sprintf(sendBuff,mensaje, "%s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
					tipoU = lU.listaUsuario[posU].tipoUsuario();
					sprintf(sendBuff,"%d", tipoU);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
					if(tipoU == 0){
						do {
							strcpy(mensajeLog, "Validacion correcta, ingresa al menu cliente");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%c",&opcion3);
							switch(opcion3){
							case '0':
								strcpy(mensaje, "Saliendo...");
								sprintf(sendBuff,mensaje, "%s", recvBuff);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								break;
							case '1':
								strcpy(mensaje, "Completar reserva...");
								sprintf(sendBuff,mensaje, "%s %s", recvBuff);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.entrada.anyo);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.entrada.mes);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.entrada.dia);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.salida.anyo);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.salida.mes);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&r.salida.dia);
								strcpy(mensajeLog, "Se recibe la informacion de la reserva");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								fechaCorrecta = r.fechaCorrecta();
								sprintf(sendBuff,"%d", fechaCorrecta);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								strcpy(mensajeLog, "Se envia si la fecha de la reserva es correcta");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								if(fechaCorrecta == 1){
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&numP);
									strcpy(mensajeLog, "Se recibe el numero de personas y se realiza la comprobacion de habitaciones");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
									numHabitacionesReser = lR.habitacionesDisponibles(r, numP,&contHDis);
									lH.modificarOcupacion(numHabitacionesReser, contHDis, numP);
									lH.modificarOcupacionRestante(numP);
									aux = lH.habitacionesDisponibles(numP, &numHD);
									sprintf(sendBuff,"%d", numHD);
									send(comm_socket,sendBuff,sizeof(sendBuff),0);
									strcpy(mensajeLog, "Se envia las habitaciones disponibles");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
									if(numHD > 0){
										for(int i=0;i<numHD;i++){
											sprintf(sendBuff,"%d", aux[i].numA);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%s", aux[i].tipo);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%f", aux[i].precio);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
										}
										delete[] aux;
										strcpy(mensajeLog, "Recibe el numero de habitacion y se busca para verificar que esta libre");
										ficheroLog(mensajeLog, u.usuario,"log.txt");
										recv(comm_socket,recvBuff,sizeof(recvBuff),0);
										sscanf(recvBuff,"%d",&numeroHabitacionUsuario);
										posH = lH.buscarHabitacion(numeroHabitacionUsuario);
										sprintf(sendBuff,"%d", posH);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										if(posH != -1){
											h = lH.listaHabitacion[posH];
											r.resalizarReserva(u.usuario, h);
											sprintf(sendBuff,"%s",r.usuario);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r.habitacion.numA);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%d",r.habitacion.numP);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											sprintf(sendBuff,"%f",r.precio);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											strcpy(mensajeLog, "Se envia la informacion de la habitacion");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%c",&opcion6);
											if(opcion6 == 'S'){
												strcpy(mensajeLog, "Se añade a la base de datos y se envia confirmacion");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												baseDatos.anyadirReservaBaseDatos(db, r);
												strcpy(mensaje, "Reserva realizada correctamente");
												sprintf(sendBuff,mensaje, "%s %s %s", recvBuff);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												lH.ocupacionLibre(contHDis);

											}else{
												strcpy(mensajeLog, "Se envia la cancelacion de la reserva");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												strcpy(mensaje, "Cancelando reserva...");
												sprintf(sendBuff,mensaje, "%s %s", recvBuff);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												lH.ocupacionLibre(contHDis);

											}
										}else{
											strcpy(mensajeLog, "Se envia que el numero de habitaciones es erroneo");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											strcpy(mensaje, "Numero de habitacion erroneo");
											sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											lH.ocupacionLibre(contHDis);

										}
									}else{
										strcpy(mensajeLog, "Se envia la informacion de que no hay habitaciones libres");
										ficheroLog(mensajeLog, u.usuario,"log.txt");
										strcpy(mensaje, "No hay habiatciones libres");
										sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										lH.ocupacionLibre(contHDis);
									}
								}else{
									strcpy(mensajeLog, "Se envia la informacion de que la fecha es incorrecta");
									ficheroLog(mensajeLog, u.usuario,"log.txt");
									strcpy(mensaje, "Fecha incorrecta");
									sprintf(sendBuff,mensaje, "%s %s", recvBuff);
									send(comm_socket,sendBuff,sizeof(sendBuff),0);
									break;
								}
								break;
							case '2':
								do{
									strcpy(mensaje, "Modificar reserva...");
									sprintf(sendBuff,mensaje, "%s %s", recvBuff);
									send(comm_socket,sendBuff,sizeof(sendBuff),0);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%c",&opcion5);
									switch(opcion5){
									case '0':
										strcpy(mensaje, "Cancelando modificacion...");
										sprintf(sendBuff,mensaje, "%s %s", recvBuff);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										break;
									case '1':
										strcpy(mensaje, "Comenzando modificacion...");
										sprintf(sendBuff,mensaje, "%s %s", recvBuff);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										aux2 = lR.obtenerReservasUsuario(u.usuario,&numReserAct);
										sprintf(sendBuff,"%d",numReserAct);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										if(numReserAct > 0){
											for(int i =0;i<numReserAct;i++){
												sprintf(sendBuff,"%d",aux2[i].habitacion.numA);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%f",aux2[i].precio);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].entrada.anyo);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].entrada.mes);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].entrada.dia);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].salida.anyo);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].salida.mes);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												sprintf(sendBuff,"%d",aux2[i].salida.dia);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
											}
											delete[] aux2;
											strcpy(mensajeLog, "Se envia la informacion de todas las reservas del usuario");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.habitacion.numA);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.entrada.anyo);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.entrada.mes);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.entrada.dia);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.salida.anyo);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.salida.mes);
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%d",&r2.salida.dia);
											int reservaCorrecta = lR.comprobarReservaCorrecta(r2);
											sprintf(sendBuff,"%d",reservaCorrecta);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											strcpy(mensajeLog, "Recibe la informacion de la reserva a modificar");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											if(reservaCorrecta == 1){
												recv(comm_socket,recvBuff,sizeof(recvBuff),0);
												sscanf(recvBuff,"%c",&opcion7);
												r2.setUsuario(u.usuario);
												if(opcion7 == 'S'){
													strcpy(mensajeLog, "Se borra la reserva y se le envia validacion de la transaccion");
													ficheroLog(mensajeLog, u.usuario,"log.txt");
													baseDatos.borrarReserva(db, r2);
													strcpy(mensaje, "Reserva eliminada");
													sprintf(sendBuff,mensaje, "%s %s %s %s %s", recvBuff);
													send(comm_socket,sendBuff,sizeof(sendBuff),0);
												}else{
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.entrada.anyo);
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.entrada.mes);
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.entrada.dia);
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.salida.anyo);
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.salida.mes);
													recv(comm_socket,recvBuff,sizeof(recvBuff),0);
													sscanf(recvBuff,"%d",&r3.salida.dia);
													fechaCorrecta2 = r3.fechaCorrecta();
													sprintf(sendBuff,"%d", fechaCorrecta2);
													send(comm_socket,sendBuff,sizeof(sendBuff),0);
													strcpy(mensajeLog, "Recibe la nueva fecha a modificar y comprueba que la fecha es correcta y se envia");
													ficheroLog(mensajeLog, u.usuario,"log.txt");
													if(fechaCorrecta2 == 1){
														strcpy(mensajeLog, "Se le envia si hay disponibilidad de fechas");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														contR =lR.contHabitacionesDisponibles(r3);
														printf(sendBuff,"%d", fechaCorrecta2);
														send(comm_socket,sendBuff,sizeof(sendBuff),0);
														if(contR == -1){
															strcpy(mensajeLog, "Realiza la modificacion y envia mensaje de validacion");
															ficheroLog(mensajeLog, u.usuario,"log.txt");
															baseDatos.modificarReserva(db, r3, r2);
															strcpy(mensaje, "Reserva modificada");
															sprintf(sendBuff, "%s %s", mensaje, recvBuff);
															send(comm_socket,sendBuff,sizeof(sendBuff),0);
														}else{
															strcpy(mensajeLog, "Se le envia validacion de la transaccion erroneo");
															ficheroLog(mensajeLog, u.usuario,"log.txt");
															strcpy(mensaje, "Error modificando la reserva");
															sprintf(sendBuff,mensaje, "%s %s", recvBuff);
															send(comm_socket,sendBuff,sizeof(sendBuff),0);
														}
													}else{
														strcpy(mensajeLog, "Se le envia que la fecha no es correcta");
														ficheroLog(mensajeLog, u.usuario,"log.txt");
														strcpy(mensaje, "Formato de fecha incorrecta");
														sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
														send(comm_socket,sendBuff,sizeof(sendBuff),0);
													}
												}
											}else{
												strcpy(mensajeLog, "Se le envia que no es valida la reserva");
												ficheroLog(mensajeLog, u.usuario,"log.txt");
												strcpy(mensaje, "No se valida la reserva");
												sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
											}
										}else{
											strcpy(mensajeLog, "Se le envia que no se han encontrado reservas");
											ficheroLog(mensajeLog, u.usuario,"log.txt");
											strcpy(mensaje, "No se han encontrado reservas");
											sprintf(sendBuff,mensaje, "%s %s %s %s %s", recvBuff);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
										}

										break;
									default:
										strcpy(mensaje, "La opcion introducida no es correcta.");
										sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										break;
									}
								}while(opcion5 != '0');
								break;
							default:
								strcpy(mensaje, "La opcion introducida no es correcta.");
								sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								break;
							}
						} while (opcion3 != '0');
					}else{ /*EMPIEZA PROGRAMA ADMINISTRADOR*/
						strcpy(mensajeLog, "Entra en la parte de administrador");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						sprintf(sendBuff, "%d", lH.numE);
						send(comm_socket,sendBuff,sizeof(sendBuff),0);
						for(int i = 0;i<lH.numE;i++){
							sprintf(sendBuff, "%d", lH.listaHabitacion[i].getNumA());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lH.listaHabitacion[i].getTipo());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%d", lH.listaHabitacion[i].numP);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%d", lH.listaHabitacion[i].ocupada);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%f", lH.listaHabitacion[i].precio);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
						}
						sprintf(sendBuff, "%d", lU.numU);
						send(comm_socket,sendBuff,sizeof(sendBuff),0);
						for(int i=0;i<lU.numU;i++){
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getNombre());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getprimerApellido());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getsegundoApellido());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getDni());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getUsuario());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%s", lU.listaUsuario[i].getContrasenya());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%d", lU.listaUsuario[i].getTelefono());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff, "%c", lU.listaUsuario[i].getTipo());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
						}

						sprintf(sendBuff, "%d", lR.numR);
						send(comm_socket,sendBuff,sizeof(sendBuff),0);

						for(int i=0;i<lR.numR;i++){
							sprintf(sendBuff,"%s",lR.listaR[i].getUsuario());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].habitacion.getNumA());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%s",lR.listaR[i].habitacion.getTipo());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%f",lR.listaR[i].getPrecio());
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].entrada.anyo);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].entrada.mes);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].entrada.dia);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].salida.anyo);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].salida.mes);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
							sprintf(sendBuff,"%d",lR.listaR[i].salida.dia);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
						}
						strcpy(mensajeLog, "Se le envian todos los datos para realizar las operaciones");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						do {
							recv(comm_socket,recvBuff,sizeof(recvBuff),0);
							sscanf(recvBuff,"%c",&opcion4);
							switch(opcion4){
							case '0':
								baseDatos.borrarTablasUsuarioReserva(db);
								baseDatos.crearTablas(&db);
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&numU);
								for(int i=0;i<numU;i++){
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.nombre);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.primerApellido);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.segundoApellido);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.dni);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.usuario);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",u2.contrasenya);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&u2.telefono);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%c",&u2.tipo);
									baseDatos.anyadirUsuarioBaseDatos(db, u2);
								}
								recv(comm_socket,recvBuff,sizeof(recvBuff),0);
								sscanf(recvBuff,"%d",&numR);
								for(int i=0;i<numR;i++){
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%s",r4.usuario);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.habitacion.numA);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%f",&r4.precio);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.entrada.anyo);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.entrada.mes);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.entrada.dia);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.salida.anyo);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.salida.mes);
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&r4.salida.dia);
									baseDatos.anyadirReservaBaseDatos(db, r4);
								}
								strcpy(mensajeLog, "Recibe los datos modificados");
								ficheroLog(mensajeLog, u.usuario,"log.txt");
								break;
							case '1': break;
							case '2': break;
							default:break;
							}
						} while (opcion4 != '0');
					}
				}else{
					strcpy(mensajeLog, "Se le envia que la contraseña es incorrecta");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					strcpy(mensaje, "Contraseña incorrecta");
					sprintf(sendBuff,mensaje, "%s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
				}
			}else{
				strcpy(mensajeLog, "Se envia que el usuario no existe en la base de datos");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				strcpy(mensaje, "Usuario no existente");
				sprintf(sendBuff,mensaje, "%s %s %s", recvBuff);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
			}
			break;
		case '2':
			recv(comm_socket,recvBuff,sizeof(recvBuff),0);
			sscanf(recvBuff,"%c",&opcion2);
			if(opcion2 == '1'){
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.nombre);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.primerApellido);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.segundoApellido);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.dni);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.usuario);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%s",u.contrasenya);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%d",&u.telefono);
				recv(comm_socket,recvBuff,sizeof(recvBuff),0);
				sscanf(recvBuff,"%c",&u.tipo);
				posU = lU.buscarUsuarioExiste(u.usuario);
				sprintf(sendBuff,"%d", posU);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
				strcpy(mensajeLog, 	"Recibe los datos del usuario y envia se ya existia");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				if(posU == -1){
					telCorrec = lU.buscarTelefonoExiste(u.telefono);
					sprintf(sendBuff,"%d", telCorrec);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
					strcpy(mensajeLog, 	"Envia si el telefono no esta repetido");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					if(telCorrec == -1){
						dniCorrec = lU.buscarDniExiste(u.dni);
						sprintf(sendBuff,"%d", dniCorrec);
						send(comm_socket,sendBuff,sizeof(sendBuff),0);
						strcpy(mensajeLog, 	"Envia si el dni no esta repetido");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						if(dniCorrec == -1){
							strcpy(mensajeLog, 	"Se envia confirmacion de registro de usuario");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							baseDatos.anyadirUsuarioBaseDatos(db, u);
							strcpy(mensaje,"Usuario añadido con exito" );
							sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
						}else{
							strcpy(mensajeLog, 	"Se envia que el dni ya existe");
							ficheroLog(mensajeLog, u.usuario,"log.txt");
							strcpy(mensaje, "El dni introducido ya existe");
							sprintf(sendBuff,mensaje, "%s %s %s %s %s", recvBuff);
							send(comm_socket,sendBuff,sizeof(sendBuff),0);
						}
					}else{
						strcpy(mensajeLog, 	"Se envia que el telefono ya existe");
						ficheroLog(mensajeLog, u.usuario,"log.txt");
						strcpy(mensaje, "El telefono introducido ya existe");
						sprintf(sendBuff,mensaje, "%s %s %s %s %s", recvBuff);
						send(comm_socket,sendBuff,sizeof(sendBuff),0);
					}
				}else{
					strcpy(mensajeLog, 	"Se envia que el usuario introducido esta en uso");
					ficheroLog(mensajeLog, u.usuario,"log.txt");
					strcpy(mensaje, "El usuario introducido esta en uso");
					sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
				}
			}else{
				strcpy(mensajeLog, 	"Se envia que se esta cancelando el registro");
				ficheroLog(mensajeLog, u.usuario,"log.txt");
				strcpy(mensaje, "Cancelando registro...");
				sprintf(sendBuff,mensaje, "%s %s", recvBuff);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
			}
			break;
		case '3':
			strcpy(mensaje, "La opcion introducida es ayuda.");
			sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			break;
		default:
			strcpy(mensaje, "La opcion introducida no es correcta.");
			sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			break;
		}

	} while (opcion != '0');


	baseDatos.cerrarBaseDatos(&db);



	// CLOSING the sockets and cleaning Winsock...

	closesocket(comm_socket);
	WSACleanup();

	return 0;
}


