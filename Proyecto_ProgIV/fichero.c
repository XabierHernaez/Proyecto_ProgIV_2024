#include "fichero.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
		fclose(pf);
	}
}
void anyadirUsuarioAlFichero(Usuario u, char *nomFich)
{
	FILE *pf;
		pf = fopen(nomFich, "a");
		if(pf != (FILE*)NULL){
			fprintf(pf, "%s %s %s %s %s %s %d %c\n", u.nombre, u.primerApellido, u.segundoApellido, u.dni, u.usuario, u.contrasenya, u.telefono, u.tipo);
			fclose(pf);
		}
}
void volcadoFicheroListaH(ListaHabitacion *aH, char * nomFich)
{
	FILE * pf;
	Habitacion h;
	char tipo[20];
	pf = fopen(nomFich, "r");
	if(pf != (FILE*)NULL){
		while(fscanf(pf, "%d %s %d %f %d", &h.numA, tipo, &h.numP, &h.precio, &h.ocupada) != EOF){
			aH->aHabitacion[aH->numH].tipo = (char*)malloc((strlen(tipo)+1)*sizeof(char));
			strcpy(aH->aHabitacion[aH->numH].tipo,tipo);
			aH->aHabitacion[aH->numH].numA = h.numA;
			aH->aHabitacion[aH->numH].numP = h.numP;
			aH->aHabitacion[aH->numH].precio = h.precio;
			aH->aHabitacion[aH->numH].ocupada = h.ocupada;
			aH->numH++;
		}
		fclose(pf);
	}
}

void volcadoListaHaFichero(ListaHabitacion aH, char *nomFich)
{
	FILE *pf;
	pf = fopen(nomFich, "w");
	if(pf != (FILE*)NULL){
		int i;
		for(i=0;i<aH.numH;i++){
			fprintf(pf, "%d %s %d %f %d\n", aH.aHabitacion[i].numA, aH.aHabitacion[i].tipo,aH.aHabitacion[i].numP, aH.aHabitacion[i].precio, aH.aHabitacion[i].ocupada);
		}
		fclose(pf);
	}
}

