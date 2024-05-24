#include "Reserva.h"
#include <string.h>
Reserva::Reserva()
{
	usuario = new char[20];
	usuario[0] = '\0';
	habitacion.tipo = new char[20];
	habitacion.tipo[0] = '\0';
	habitacion.numA = 0;
	habitacion.numP = 0;
	habitacion.ocupada = 0;
	habitacion.precio = 0.0;
	precio = 0.0;
	entrada.anyo = 0;
	entrada.mes = 0;
	entrada.dia = 0;
	salida.anyo = 0;
	salida.mes = 0;
	salida.dia = 0;
}
Reserva::Reserva(char *u, Habitacion h, Fecha e, Fecha s, float p)
{
	usuario = new char[strlen(u)+1];
	strcpy(usuario, u);
	habitacion.numA = h.numA;
	habitacion.tipo = new char[strlen(h.tipo)];
	strcpy(habitacion.tipo, h.tipo);
	habitacion.numP = h.numP;
	habitacion.ocupada = h.ocupada;
	habitacion.precio = h.precio;
	entrada.anyo = e.anyo;
	entrada.mes = e.mes;
	entrada.dia = e.dia;
	salida.anyo = s.anyo;
	salida.mes = e.mes;
	salida.dia = e.dia;
	precio = p;
}
Reserva::Reserva(const Reserva &r)
{
	usuario = new char[strlen(r.usuario)+1];
	strcpy(usuario, r.usuario);
	habitacion.numA = r.habitacion.numA;
	habitacion.tipo = new char[strlen(r.habitacion.tipo)];
	strcpy(habitacion.tipo, r.habitacion.tipo);
	habitacion.numP = r.habitacion.numP;
	habitacion.ocupada = r.habitacion.ocupada;
	habitacion.precio = r.habitacion.precio;
	entrada.anyo = r.entrada.anyo;
	entrada.mes = r.entrada.mes;
	entrada.dia = r.entrada.dia;
	salida.anyo = r.salida.anyo;
	salida.mes = r.salida.mes;
	salida.dia = r.salida.dia;
	precio = r.precio;
}
void Reserva::setUsuario(char* usu)
{
	delete[] usuario;
	usuario = new char[strlen(usu)+1];
	strcpy(usuario, usu);
}
void Reserva::setHabitacion(Habitacion h)
{
	habitacion.numA = h.numA;
	delete[] habitacion.tipo;
	habitacion.tipo = new char[strlen(h.tipo)];
	strcpy(habitacion.tipo, h.tipo);
	habitacion.numP = h.numP;
	habitacion.ocupada = h.ocupada;
	habitacion.precio = h.precio;
}
void Reserva::setPrecio(float p)
{
	precio = p;
}
void Reserva::setEntradaentrada(Fecha f)
{
	entrada.anyo = f.anyo;
	entrada.mes = f.mes;
	entrada.dia = f.dia;
}
void Reserva::setSalida(Fecha f)
{
	salida.anyo = f.anyo;
	salida.mes = f.mes;
	salida.dia = f.dia;
}
char* Reserva::getUsuario()
{
	return usuario;
}
float Reserva::getPrecio()
{
	return precio;
}
int Reserva::fechaCorrecta()
{
	if ((entrada.anyo == 2024) && (entrada.mes >= 1 && entrada.mes <= 12) && (entrada.dia >= 1 && entrada.dia <= 31) && (salida.anyo >= 1) && (salida.mes >= 1 && salida.mes <= 12) && (salida.dia >= 1 && salida.dia <= 31)
		&& ((entrada.mes == salida.mes) || (entrada.mes - salida.mes == -1)) && (entrada.dia < salida.dia)) {
			return 1;
	}else{
		return 0;
	}
}
Reserva& Reserva::operator=(const Reserva &r)
{
	delete[] usuario;
	usuario = new char[strlen(r.usuario)+1];
	strcpy(usuario, r.usuario);
	habitacion.numA = r.habitacion.numA;
	habitacion.tipo = new char[strlen(r.habitacion.tipo)];
	strcpy(habitacion.tipo, r.habitacion.tipo);
	habitacion.precio = r.habitacion.precio;
	habitacion.ocupada = r.habitacion.ocupada;
	habitacion.numP = r.habitacion.numP;
	entrada.anyo = r.entrada.anyo;
	entrada.mes = r.entrada.mes;
	entrada.dia = r.entrada.dia;
	salida.anyo = r.salida.anyo;
	salida.mes = r.salida.mes;
	salida.dia = r.salida.dia;
	precio = r.precio;
	return (*this);
}
void Reserva::resalizarReserva(char *usu, Habitacion h)
{
	setUsuario(usu);
	setHabitacion(h);
	precio += h.precio * h.numP;
}
int Reserva::fechaDisponible(const Reserva& otraReserva) const
{
	if((entrada.dia - otraReserva.salida.dia < 0 && salida.dia >  otraReserva.entrada.dia&& entrada.mes == otraReserva.salida.mes) && otraReserva.habitacion.numP == habitacion.numP){
		return 1;
	}else{
		return 0;
	}
}

int Reserva::validarReserva(const Reserva &r) const
{
	if(entrada.dia == r.entrada.dia && entrada.mes == r.entrada.mes && entrada.anyo == r.entrada.anyo
			&& salida.dia == r.salida.dia && salida.mes == r.salida.mes && salida.anyo == r.salida.anyo && habitacion.numA == r.habitacion.numA){
		return 1;
	}else{
		return 0;
	}
}
Reserva::~Reserva() {
	delete[] usuario;
}

