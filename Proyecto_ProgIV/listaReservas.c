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
void liberarMemoria(ListaReservas *aR)
{
	free(aR->aR);
}


