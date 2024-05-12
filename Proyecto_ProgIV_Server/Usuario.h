
#ifndef USUARIO_H_
#define USUARIO_H_

class Usuario {
public:
	char *nombre;
	char *primerApellido;
	char *segundoApellido;
	char *dni;
	char *usuario;
	char *contrasenya;
	int telefono;
	char tipo;
public:
	Usuario();
	Usuario(char *n, char *a1, char *a2, char *d, char *u, char *c, int tf, char t);
	Usuario(const Usuario &u);
	void setNombre(char *n);
	void setprimerApellido(char *a1);
	void setsegundoApellido(char *a2);
	void setDni(char *d);
	void setUsuario(char *u);
	void setContrasenya(char *c);
	void setTelefono(int tf);
	void setTipo(char t);
	char * getNombre();
	char * getprimerApellido();
	char * getsegundoApellido();
	char * getDni();
	char * getUsuario();
	char * getContrasenya();
	int getTelefono();
	char getTipo();
	Usuario& operator=(const Usuario &u);
	int contraseniaCorrecta(char *conU);//Recibe la contraseña introducida en el incio sesion y su contraseña real
	int tipoUsuario();
	virtual ~Usuario();
};

#endif
