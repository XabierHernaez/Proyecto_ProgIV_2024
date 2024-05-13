
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

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo

	cout<<("\nInitialising Winsock...\n")<<endl; // inicializa la libreria
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<("Failed. Error Code : %d", WSAGetLastError())<<endl;
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<("Could not create socket : %d", WSAGetLastError())<<endl;
		WSACleanup();
		return -1;
	}

	cout<<("Socket created.\n")<<endl;
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		cout<<("Bind failed with error code: %d", WSAGetLastError())<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	cout<<("Bind done.\n")<<endl; //DEJAR EL SOCKET EN ESPERA

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		cout<<("Listen failed with error code: %d", WSAGetLastError())<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	cout<<("Waiting for incoming connections...\n")<<endl;
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		cout<<("accept failed with error code : %d", WSAGetLastError())<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	cout<<("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port))<<endl;

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
	for(int i=0;i<4;i++){
		sprintf(sendBuff,"%d", lR.listaR[i].habitacion.numA);
		send(comm_socket,sendBuff,sizeof(sendBuff),0);
	}



	char opcion, opcion2, opcion3, opcion6;
	int posU, contraCorrecta, tipoU, numP, fechaCorrecta, *numHabitacionesReser, contHDis, numHD, numeroHabitacionUsuario, posH;
	char mensaje[200];
	Usuario u;
	Reserva r;
	Habitacion *aux = NULL;
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
			sprintf(sendBuff,"%d", posU);
			send(comm_socket,sendBuff,sizeof(sendBuff),0);
			if(posU != -1){
				contraCorrecta = u.contraseniaCorrecta(lU.listaUsuario[posU].contrasenya);
				sprintf(sendBuff,"%d", contraCorrecta);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
				if(contraCorrecta == 1){
					strcpy(mensaje, "Bienvenido ");
					strcat(mensaje, u.usuario);
					sprintf(sendBuff,mensaje, "%s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
					tipoU = lU.listaUsuario[posU].tipoUsuario();
					sprintf(sendBuff,"%d", tipoU);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
					if(tipoU != -1){
						do {
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
								fechaCorrecta = r.fechaCorrecta();
								sprintf(sendBuff,"%d", fechaCorrecta);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								if(fechaCorrecta == 1){
									recv(comm_socket,recvBuff,sizeof(recvBuff),0);
									sscanf(recvBuff,"%d",&numP);
									numHabitacionesReser = lR.habitacionesDisponibles(r, numP,&contHDis);
									lH.modificarOcupacion(numHabitacionesReser, contHDis, numP);
									aux = lH.habitacionesDisponibles(numP, &numHD);
									sprintf(sendBuff,"%d", numHD);
									send(comm_socket,sendBuff,sizeof(sendBuff),0);
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
											recv(comm_socket,recvBuff,sizeof(recvBuff),0);
											sscanf(recvBuff,"%c",&opcion6);
											if(opcion6 == 'S'){
												baseDatos.anyadirReservaBaseDatos(db, r);
												strcpy(mensaje, "Reserva realizada correctamente");
												sprintf(sendBuff,mensaje, "%s %s %s", recvBuff);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												lH.ocupacionLibre(numHabitacionesReser,contHDis);

											}else{
												strcpy(mensaje, "Cancelando reserva...");
												sprintf(sendBuff,mensaje, "%s %s", recvBuff);
												send(comm_socket,sendBuff,sizeof(sendBuff),0);
												lH.ocupacionLibre(numHabitacionesReser,contHDis);

											}
										}else{
											strcpy(mensaje, "Numero de habitacion erroneo");
											sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
											send(comm_socket,sendBuff,sizeof(sendBuff),0);
											lH.ocupacionLibre(numHabitacionesReser,contHDis);

										}
									}else{
										strcpy(mensaje, "No hay habiatciones libres");
										sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
										send(comm_socket,sendBuff,sizeof(sendBuff),0);
										lH.ocupacionLibre(numHabitacionesReser,contHDis);
									}
								}else{
									strcpy(mensaje, "Fecha incorrecta");
									sprintf(sendBuff,mensaje, "%s %s", recvBuff);
									send(comm_socket,sendBuff,sizeof(sendBuff),0);
									break;
								}
								break;
							case '2':
								strcpy(mensaje, "Modificar reserva...");
								sprintf(sendBuff,mensaje, "%s %s", recvBuff);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								break;
							default:
								strcpy(mensaje, "La opcion introducida no es correcta.");
								sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
								send(comm_socket,sendBuff,sizeof(sendBuff),0);
								break;
							}
						} while (opcion3 != '0');
					}else{

					}
				}else{
					strcpy(mensaje, "Contraseña incorrecta");
					sprintf(sendBuff,mensaje, "%s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
				}
			}else{
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
				if(posU == -1){
					baseDatos.anyadirUsuarioBaseDatos(db, u);
					strcpy(mensaje,"Usuario añadido con exito" );
					sprintf(sendBuff,mensaje, "%s %s %s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
				}else{
					strcpy(mensaje, "El usuario introducido esta en uso");
					sprintf(sendBuff,mensaje, "%s %s %s %s %s %s", recvBuff);
					send(comm_socket,sendBuff,sizeof(sendBuff),0);
				}
			}else{
				strcpy(mensaje, "Cancelando registro...");
				sprintf(sendBuff,mensaje, "%s %s", recvBuff);
				send(comm_socket,sendBuff,sizeof(sendBuff),0);
			}
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


