#ifndef RESERVA_H_
#define RESERVA_H_
#include "Habitacion.h"
class Reserva {

class Fecha{
	public:
		int dia;
		int mes;
		int anyo;
};
public:
	char *usuario;
	Habitacion habitacion;
	float precio;
	Fecha entrada;
	Fecha salida;
public:
	Reserva();
	Reserva(char *u, Habitacion h, Fecha e, Fecha s, float p);
	Reserva(const Reserva &r);
	void setUsuario(char* usu);
	void setHabitacion(Habitacion h);
	void setPrecio(float p);
	void setEntradaentrada(Fecha f);
	void setSalida(Fecha f);
	char* getUsuario();
	float getPrecio();
	int fechaCorrecta();
	Reserva& operator=(const Reserva &r);
	void resalizarReserva(char *usu, Habitacion h);
	int fechaDisponible(const Reserva& otraReserva) const;
	virtual ~Reserva();
};

#endif
