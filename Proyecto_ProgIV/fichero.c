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
void volcadoListaRFichero(ListaReservas aR, char *nomFich)
{
	FILE *pf;
	pf = fopen(nomFich, "w");
	if(pf != (FILE*)NULL){
		int i;
		for(i=0;i<aR.numR;i++){
			fprintf(pf, "%s %d/%d/%d %d/%d/%d %d %s %d %f %d %f\n", aR.aR[i].usuario,aR.aR[i].entrada.anyo, aR.aR[i].entrada.mes, aR.aR[i].entrada.dia, aR.aR[i].salida.anyo,
					aR.aR[i].salida.mes, aR.aR[i].salida.dia, aR.aR[i].habitacion.numA, aR.aR[i].habitacion.tipo, aR.aR[i].habitacion.numP, aR.aR[i].habitacion.precio, aR.aR[i].habitacion.ocupada, aR.aR[i].precio);
		}
		fclose(pf);
	}
}
void volcadoFicheroListaR(ListaReservas *aR, char *nomFich)
{
	FILE *pf;
	Reserva r;
	char usuario[10];
	char tipo[20];
	pf = fopen(nomFich, "r");
	if(pf != (FILE*)NULL){
		while(fscanf(pf, "%s %d/%d/%d %d/%d/%d %d %s %d %f %d %f", usuario, &r.entrada.anyo,&r.entrada.mes,&r.entrada.dia, &r.salida.anyo,
				&r.salida.mes, &r.salida.dia, &r.habitacion.numA,
				tipo, &r.habitacion.numP, &r.habitacion.precio,&r.habitacion.ocupada, &r.precio) != EOF){
			aR->aR[aR->numR].usuario = (char*)malloc((strlen(usuario)+1)*sizeof(char));
			strcpy(aR->aR[aR->numR].usuario, usuario);
			aR->aR[aR->numR].entrada.anyo = r.entrada.anyo;
			aR->aR[aR->numR].entrada.mes = r.entrada.mes;
			aR->aR[aR->numR].entrada.dia = r.entrada.dia;
			aR->aR[aR->numR].salida.anyo = r.salida.anyo;
			aR->aR[aR->numR].salida.mes = r.salida.mes;
			aR->aR[aR->numR].salida.dia = r.salida.dia;
			aR->aR[aR->numR].habitacion.numA = r.habitacion.numA;
			aR->aR[aR->numR].habitacion.tipo = (char*)malloc((strlen(tipo)+1)*sizeof(char));
			strcpy(aR->aR[aR->numR].habitacion.tipo, tipo);
			aR->aR[aR->numR].habitacion.numP = r.habitacion.numP;
			aR->aR[aR->numR].habitacion.precio = r.habitacion.precio;
			aR->aR[aR->numR].habitacion.ocupada = r.habitacion.ocupada;
			aR->aR[aR->numR].precio = r.precio;
			(aR->numR)++;
		}
	}

}
