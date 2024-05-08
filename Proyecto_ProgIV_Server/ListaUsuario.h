
#ifndef LISTAUSUARIO_H_
#define LISTAUSUARIO_H_
#include "Usuario.h"
class ListaUsuario {
public:
	Usuario *listaUsuario;
	int numU;
public:
	ListaUsuario();
	void anyadirUsuario(const Usuario &u);
	void visualizar();
	virtual ~ListaUsuario();
};

#endif
