#include "listaReservas.h"
#include <stdlib.h>
#include <string.h>

void anyadirReserva(ListaReservas *aR, Reserva r)
{
	if(aR->numR == 0){
		aR->listaR = (Reserva*)malloc(1*sizeof(Reserva));
	}else{
		Reserva *aux = (Reserva*)malloc(aR->numR*sizeof(Reserva));
		for(int i=0;i<aR->numR;i++){
			aux[i] = aR->listaR[i];
		}
		free(aR->listaR);
		aR->listaR = (Reserva*)malloc((aR->numR +1)*sizeof(Reserva));
		for(int i=0;i<aR->numR;i++){
			aR->listaR[i] = aux[i];
		}
		free(aux);
	}
	aR->listaR[aR->numR] = r;
	(aR->numR)++;
}
void visualizarReservasActias(ListaReservas listaR)
{
	printf("Reservas activas...\n");fflush(stdout);
	printf("----------\n");fflush(stdout);
	printf("----------\n");fflush(stdout);
	for(int i =0;i<listaR.numR;i++){
		mostrarReserva(listaR.listaR[i]);
	}
}
int encontrarReserva(ListaReservas listaR, Reserva r,  int numH)
{
	int enc = 0, i = 0;
	while(!enc && i < listaR.numR){
		if(listaR.listaR[i].habitacion.numA == numH && listaR.listaR[i].entrada.dia == r.entrada.dia && listaR.listaR[i].entrada.mes == r.entrada.mes &&
				listaR.listaR[i].entrada.anyo == r.entrada.anyo && listaR.listaR[i].salida.dia == r.salida.dia && listaR.listaR[i].salida.mes == r.salida.mes && listaR.listaR[i].salida.anyo == r.salida.anyo){
			enc = 1;
		}else{
			i++;
		}
	}
	if(enc){
		return i;
	}else{
		printf("Habitacion no encontrada...\n");fflush(stdout);
		return -1;
	}
}
int disponibilidadHabitacion(ListaReservas listaR, Reserva r, int numH)
{
	int enc = 0, i = 0;
	while(!enc && i < listaR.numR){
		if(listaR.listaR[i].entrada.dia == r.entrada.dia && listaR.listaR[i].entrada.mes == r.entrada.mes &&
			listaR.listaR[i].entrada.anyo == r.entrada.anyo && listaR.listaR[i].salida.dia == r.salida.dia && listaR.listaR[i].salida.mes == r.salida.mes && listaR.listaR[i].salida.anyo == r.salida.anyo && listaR.listaR[i].habitacion.numA == numH){
				enc = 1;
		}else{
			i++;
		}
	}
	if(enc){
		return 1;
	}else{
		return -1;
	}
}
void modificarReserva(ListaReservas *listaR, Reserva nuevaReserva, int posH)
{
	listaR->listaR[posH].entrada.anyo = nuevaReserva.entrada.anyo;
	listaR->listaR[posH].entrada.mes = nuevaReserva.entrada.mes;
	listaR->listaR[posH].entrada.dia = nuevaReserva.entrada.dia;
	listaR->listaR[posH].salida.anyo = nuevaReserva.salida.anyo;
	listaR->listaR[posH].salida.mes = nuevaReserva.salida.mes;
	listaR->listaR[posH].salida.dia = nuevaReserva.salida.dia;
}
void eliminarReserva(ListaReservas *listaR, int posH)
{
	for(int i=posH;i<listaR->numR-1;i++){
		listaR->listaR[i] = listaR->listaR[i+1];
	}
	(listaR->numR)--;
}
int estaEnLista(char **listaUsuarios, int numUsuarios, const char *usuario) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(listaUsuarios[i], usuario) == 0) {
            return 1;
        }
    }
    return 0;
}
char** usuariosConReserva(ListaReservas lR, int *numUsuariosUnicos)
{
    char **listaUsuarios = (char **)malloc(lR.numR * sizeof(char *));
    *numUsuariosUnicos = 0;
    for (int i = 0; i < lR.numR; i++) {
        if (!estaEnLista(listaUsuarios, *numUsuariosUnicos, lR.listaR[i].usuario)) {
            listaUsuarios[*numUsuariosUnicos] = strdup(lR.listaR[i].usuario);
            (*numUsuariosUnicos)++;
        }
    }
    return listaUsuarios;
}
void liberarMemoria(ListaReservas *aR)
{
	free(aR->listaR);
}
