#include "listaUsuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liberarMemoriaLU(ListaUsuarios *lu)
{
	free(lu->aUsuario);
}
void anyadirUsuario(ListaUsuarios *lU, Usuario u)
{
	if(lU->numU == 0){
		lU->aUsuario = (Usuario*)malloc(1*sizeof(Usuario));
	}else{
		Usuario *aux = (Usuario*)malloc(lU->numU*sizeof(Usuario));
		for(int i=0;i<lU->numU;i++){
			aux[i] = lU->aUsuario[i];
		}
		free(lU->aUsuario);
		lU->aUsuario = (Usuario*)malloc((lU->numU+1)*sizeof(Usuario));
		for(int i=0;i<lU->numU;i++){
			lU->aUsuario[i] = aux[i];
		}
		free(aux);
	}
	lU->aUsuario[lU->numU] = u;
	(lU->numU)++;
}
void visualizarLU(ListaUsuarios lU)
{
	for(int i=0;i<lU.numU;i++){
		printf("%s %s %s %s %s %s %d %c\n", lU.aUsuario[i].nombre,
				lU.aUsuario[i].primerApellido,
				lU.aUsuario[i].segundoApellido,
				lU.aUsuario[i].dni,
				lU.aUsuario[i].usuario,
				lU.aUsuario[i].contrasenya,
				lU.aUsuario[i].telefono,
				lU.aUsuario[i].tipo);fflush(stdout);

	}
}
void eliminarUsuario(ListaUsuarios *lU, int pos)
{
    for(int i = pos; i < lU->numU - 1; i++){
        lU->aUsuario[i] = lU->aUsuario[i + 1];
    }
    lU->numU--;
}

void borrarUsuariosSinReserva(ListaUsuarios *lU, char **listaU, int contU)
{
    char opcion;

    for (int j = 0; j < lU->numU; j++) {
        int sinReserva = 1;
        for (int i = 0; i < contU; i++) {
            if (strcmp(listaU[i], lU->aUsuario[j].usuario) == 0) {
                sinReserva = 0;
                break;
            }
        }

        if (sinReserva) {
            mostrarDatosUsuario2(lU->aUsuario[j]);
            printf("Quieres borrar este usuario sin reserva [S/N]: ");
            fflush(stdout);
            fflush(stdin);
            scanf("%c", &opcion);
            if (opcion == 'S') {
                eliminarUsuario(lU, j);
                j--;
            }
        }
    }
}
/*
ListaUsuarios reservarMemoriaLU(int tam)
{
	ListaUsuarios lu;
	lu.tam = tam;
	lu.numU = 0;
	lu.aUsuario = (Usuario*)malloc(tam * sizeof(Usuario));
	return lu;
}
int buscarUsuario(ListaUsuarios lu, char *usuario)
{
	int pos = 0, enc = 0;
	while(!enc && pos < lu.numU){
		if(strcmp(lu.aUsuario[pos].usuario, usuario) == 0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc){
		return pos;
	}else{
		return -1;
	}
	return pos;
}
*/
