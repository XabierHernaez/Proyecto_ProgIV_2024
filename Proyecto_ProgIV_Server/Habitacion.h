
#ifndef HABITACION_H_
#define HABITACION_H_

class Habitacion {
public:
	int numA;
	char *tipo;
	int numP;
	float precio;
	int ocupada;
public:
	Habitacion();
	Habitacion(int nH, char * tipo, int nP, float p, int o);
	Habitacion(const Habitacion &a);
	void setNumA(int numA);
	void setTipo(char *tipo);
	void setNumP(int numP);
	void setPrecio(float precio);
	void setOcupada(int ocupada);
	int getNumA();
	char * getTipo();
	int getNumP();
	float getPrecio();
	int getOcupada();
	virtual ~Habitacion();

};

#endif
