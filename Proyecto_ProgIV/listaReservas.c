#include "listaReservas.h"
#include <stdlib.h>
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
void liberarMemoria(ListaReservas *aR)
{
	free(aR->aR);
}


