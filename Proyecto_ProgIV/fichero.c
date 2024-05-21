#include "fichero.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ficheroLog(char *mensaje, char *usuario, char * nomFich)
{
	FILE * pf;
	pf = fopen(nomFich, "a");
	if(pf != (FILE*)NULL){
		fprintf(pf, "%s - Usuario: %s\n", mensaje, usuario);
		fclose(pf);
	}
}

