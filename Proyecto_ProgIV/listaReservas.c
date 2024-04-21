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
int buscarHabitacionReservada(ListaReservas aR, int numA)
{
	int i=0, enc =0;
	while(!enc && i<aR.numR){
		if(aR.aR[i].habitacion.numA == numA){
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
void eliminarReserva(ListaReservas *aR, int numH, char * usuario)
{
	int i;
		for(i=0;i<aR->numR;i++){
			if(strcmp(aR->aR[i].usuario, usuario) == 0 && aR->aR[i].habitacion.numA == numH){
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
void modificarReserva(ListaReservas *aR, int numH, char * usuario)
{
	int i;
	Reserva nuevaReserva;
	for(i=0;i<aR->numR;i++){
		if(strcmp(aR->aR[i].usuario, usuario) == 0 && aR->aR[i].habitacion.numA == numH){
			nuevaReserva = comenzarReserva();
			if(fechaCorrecta(nuevaReserva) == 1){
				aR->aR[i].entrada.anyo = nuevaReserva.entrada.anyo;
				aR->aR[i].entrada.mes = nuevaReserva.entrada.mes;
				aR->aR[i].entrada.dia = nuevaReserva.entrada.dia;
				aR->aR[i].salida.anyo = nuevaReserva.salida.anyo;
				aR->aR[i].salida.mes = nuevaReserva.salida.mes;
				aR->aR[i].salida.dia = nuevaReserva.salida.dia;
			}else{
				printf("La fecha de la reserva es incorrecta\n");fflush(stdout);
			}
		}
	}
}
void liberarMemoria(ListaReservas *aR)
{
	free(aR->aR);
}


