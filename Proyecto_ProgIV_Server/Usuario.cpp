
#include "Usuario.h"
#include <string.h>
Usuario::Usuario()
{
	nombre = new char[1];
	nombre[0] = '\0';
	primerApellido = new char[1];
	primerApellido[0] = '\0';
	segundoApellido = new char[1];
	segundoApellido[0] = '\0';
	dni = new char[1];
	dni[0] = '\0';
	usuario = new char[1];
	usuario[0] = '\0';
	contrasenya = new char[1];
	contrasenya[0] = '\0';
	telefono = 0;
	tipo = 'C';
}
Usuario::Usuario(char *n, char *a1, char *a2, char *d, char *u, char *c, int tf, char t)
{
	nombre = new char[strlen(n) +1];
	strcpy(nombre, n);
	primerApellido = new char[strlen(a1) +1];
	strcpy(primerApellido, a1);
	segundoApellido = new char[strlen(a2) +1];
	strcpy(segundoApellido, a2);
	dni = new char[strlen(d) +1];
	strcpy(dni, d);
	usuario = new char[strlen(u) +1];
	strcpy(usuario, u);
	contrasenya = new char[strlen(c) +1];
	strcpy(contrasenya, c);
	telefono = tf;
	tipo = t;
}
Usuario::Usuario(const Usuario &u)
{
	nombre = new char[strlen(u.nombre) +1];
	strcpy(nombre, u.nombre);
	primerApellido = new char[strlen(u.primerApellido) +1];
	strcpy(primerApellido, u.primerApellido);
	segundoApellido = new char[strlen(u.segundoApellido) +1];
	strcpy(segundoApellido, u.segundoApellido);
	dni = new char[strlen(u.dni) +1];
	strcpy(dni, u.dni);
	usuario = new char[strlen(u.usuario) +1];
	strcpy(usuario, u.usuario);
	contrasenya = new char[strlen(u.contrasenya) +1];
	strcpy(contrasenya, u.contrasenya);
	telefono = u.telefono;
	tipo = u.tipo;
}
void Usuario::setNombre(char *n)
{
	delete [] nombre;
	nombre = new char[strlen(n) +1];
	strcpy(nombre, n);
}
void Usuario::setprimerApellido(char *a1)
{
	delete[] primerApellido;
	primerApellido = new char[strlen(a1) +1];
	strcpy(primerApellido, a1);
}
void Usuario::setsegundoApellido(char *a2)
{
	delete[] segundoApellido;
	segundoApellido = new char[strlen(a2) +1];
	strcpy(segundoApellido, a2);
}
void Usuario::setDni(char *d)
{
	delete[] dni;
	dni = new char[strlen(d) +1];
	strcpy(dni, d);

}
void Usuario::setUsuario(char *u)
{
	delete[] usuario;
	usuario = new char[strlen(u) +1];
	strcpy(usuario, u);
}
void Usuario::setContrasenya(char *c)
{
	delete[] contrasenya;
	contrasenya = new char[strlen(c) +1];
	strcpy(contrasenya, c);
}
void Usuario::setTelefono(int tf)
{
	telefono = tf;
}
void Usuario::setTipo(char t)
{
	tipo = t;
}
char * Usuario::getNombre()
{
	return nombre;
}
char * Usuario::getprimerApellido()
{
	return primerApellido;
}
char * Usuario::getsegundoApellido()
{
	return segundoApellido;
}
char * Usuario::getDni()
{
	return dni;
}
char * Usuario::getUsuario()
{
	return usuario;
}
char * Usuario::getContrasenya()
{
	return contrasenya;
}
int Usuario::getTelefono()
{
	return telefono;
}
char Usuario::getTipo()
{
	return tipo;
}
Usuario::~Usuario() {
	delete[] nombre;
	delete[] primerApellido;
	delete[] segundoApellido;
	delete[] dni;
	delete[] usuario;
	delete[] contrasenya;
}

