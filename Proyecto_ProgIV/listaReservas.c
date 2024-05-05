#include "listaReservas.h"
#include <stdlib.h>
#include <string.h>
ListaReservas reservarMemoria(int tam)
{
	ListaReservas aR;
	aR.tam = tam;
	aR.aR = (Reserva*)malloc(tam*sizeof(Reserva));
	aR.numR = 0;
	return aR;
}
void anyadirReserva(ListaReservas *aR, Reserva r)
{
	if(aR->numR < aR->tam){
		aR->aR[aR->numR] = r;
		aR->numR++;
	}else{
		printf("La lista de reservas esta llena\n");fflush(stdout);
	}
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


