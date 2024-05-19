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
            return 1; // Usuario encontrado
        }
    }
    return 0; // Usuario no encontrado
}
char** usuariosConReserva(ListaReservas lR, int *numUsuariosUnicos)
{
    char **listaUsuarios = (char **)malloc(lR.numR * sizeof(char *));
    *numUsuariosUnicos = 0;

    // Recorrer la lista de reservas para obtener usuarios únicos
    for (int i = 0; i < lR.numR; i++) {
        // Verificar si el usuario ya está en la lista
        if (!estaEnLista(listaUsuarios, *numUsuariosUnicos, lR.listaR[i].usuario)) {
            // Si no está en la lista, agregarlo
            listaUsuarios[*numUsuariosUnicos] = strdup(lR.listaR[i].usuario);
            (*numUsuariosUnicos)++;
        }
    }

    // Devolver el arreglo de usuarios únicos y actualizar el número de usuarios
    // Sin necesidad de asignación indirecta
    return listaUsuarios;
}
void liberarMemoria(ListaReservas *aR)
{
	free(aR->listaR);
}
/*
ListaReservas reservarMemoria(int tam)
{
	ListaReservas aR;
	aR.tam = tam;
	aR.aR = (Reserva*)malloc(tam*sizeof(Reserva));
	aR.numR = 0;
	return aR;
}
void eliminarReserva(ListaReservas *aR, int numH, char * usuario, Reserva nuevaReserva)
{
	int i;
		for(i=0;i<aR->numR;i++){
			if(strcmp(aR->aR[i].usuario, usuario) == 0 && aR->aR[i].habitacion.numA == numH && aR->aR[i].entrada.anyo == nuevaReserva.entrada.anyo && aR->aR[i].entrada.mes == nuevaReserva.entrada.mes && aR->aR[i].entrada.dia == nuevaReserva.entrada.dia && aR->aR[i].salida.anyo == nuevaReserva.salida.anyo && aR->aR[i].salida.mes == nuevaReserva.salida.mes && aR->aR[i].salida.dia == nuevaReserva.salida.dia){
				aR->aR[i] = aR->aR[i+1];
				(aR->numR)--;
			}
		}
}
void obtenerReservasUsuario(ListaReservas aR, char *usuario, int *numReserActu)
{

	int i;
	*numReserActu =0;
	for(i=0;i<aR.numR;i++){
		if(strcmp(aR.aR[i].usuario, usuario) == 0){
			mostrarReserva(aR.aR[i]);
			(*numReserActu)++;
		}
	}

}
void modificarReserva(ListaReservas *aR, int numH, Reserva nuevaReserva, Reserva viejaReserva, char * usuario)
{
	int i;
	for(i=0;i<aR->numR;i++){
		if(strcmp(aR->aR[i].usuario, usuario) == 0 && aR->aR[i].habitacion.numA == numH && aR->aR[i].entrada.anyo == viejaReserva.entrada.anyo && aR->aR[i].entrada.mes == viejaReserva.entrada.mes && aR->aR[i].entrada.dia == viejaReserva.entrada.dia && aR->aR[i].salida.anyo == viejaReserva.salida.anyo && aR->aR[i].salida.mes == viejaReserva.salida.mes && aR->aR[i].salida.dia == viejaReserva.salida.dia){
				aR->aR[i].entrada.anyo = nuevaReserva.entrada.anyo;
				aR->aR[i].entrada.mes = nuevaReserva.entrada.mes;
				aR->aR[i].entrada.dia = nuevaReserva.entrada.dia;
				aR->aR[i].salida.anyo = nuevaReserva.salida.anyo;
				aR->aR[i].salida.mes = nuevaReserva.salida.mes;
				aR->aR[i].salida.dia = nuevaReserva.salida.dia;
		}
	}
}
int conthabitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numH)
{
	int i = 0, enc = 0;
	while(!enc && i<aR.numR){
		if((r.entrada.dia - aR.aR[i].salida.dia < 0 && r.salida.dia >  aR.aR[i].entrada.dia&& r.entrada.mes == aR.aR[i].salida.mes) && aR.aR[i].habitacion.numA == numH){
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
int * habitacionesDisponiblesReserva(ListaReservas aR, Reserva r, int numP, int *cont)
{
	int i, *numH, j = 0;
	*cont = 0;
	for(i=0;i<aR.numR;i++){
		//		1               5							3				4
		if((r.entrada.dia - aR.aR[i].salida.dia < 0 && r.salida.dia >  aR.aR[i].entrada.dia&& r.entrada.mes == aR.aR[i].salida.mes) && aR.aR[i].habitacion.numP == numP){
			(*cont)++;
		}
	}
	numH = (int*)malloc((*cont)*sizeof(int));
	for(i=0;i<aR.numR;i++){
		if((r.entrada.dia - aR.aR[i].salida.dia < 0 && r.entrada.mes == aR.aR[i].salida.mes) && aR.aR[i].habitacion.numP == numP){
			numH[j] = aR.aR[i].habitacion.numA;
			j++;
		}
	}
	return numH;
}
void liberarMemoria(ListaReservas *aR)
{
	free(aR->aR);
}
*/

