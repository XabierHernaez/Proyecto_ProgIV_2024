#ifndef USUARIO_H_
#define USUARIO_H_

typedef struct{
		char nombre[15];
		char primerApellido[15];
		char segundoApellido[15];
		char dni[10];
		char usuario[10];
		char contrasenya[20];
		int telefono;
		char tipo;
}Usuario;

Usuario datosUsuarioR();
Usuario datosUsuarioI();
int contraseniaCorrecta(char *conU, char *con);
char mostrarDatosUsuario(Usuario u);

#endif
