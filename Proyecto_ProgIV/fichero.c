#include "fichero.h"
#include <stdio.h>
#include <string.h>
void volcadoFicheroListaU(ListaUsuarios *lu, char *nomFich)
{
	FILE *pf;
	Usuario u;
	pf = fopen(nomFich, "r");
	if(pf != (FILE*)NULL){
		while(fscanf(pf, "%s %s %s %s %s %s %d %c", u.nombre, u.primerApellido, u.segundoApellido, u.dni, u.usuario, u.contrasenya, &u.telefono, &u.tipo) != EOF){
			lu->aUsuario[lu->numU] = u;
			lu->numU++;
		}
		pclose(pf);
	}
}

