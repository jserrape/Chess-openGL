#ifndef PIEZA_H
#define PIEZA_H
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Casilla.h"
#include "igvMallaTriangulos.h"

using namespace std;



class Pieza {
private:
	int id;
	Casilla *ca;
	igvMallaTriangulos *malla;
	string color;
	int tipo;
	bool moviendo;
	bool inicio;
	bool transformar;
public:
    Pieza();
	Pieza(int idd,Casilla *caa,string colorr,int tipoo,igvMallaTriangulos *mallaa);
    virtual ~Pieza();

	int getId(){return id;};
	string getColor(){return color;};
	bool getMoviendo(){return moviendo;};
	void setMoviendo(bool mov){this->moviendo=mov;};
	Casilla* getCasilla(){return ca;};
	int getTipo(){return tipo;};

	bool movimientoValido(Casilla &destino, bool comer);

	void asignaCasilla(Casilla *caa);
	void transformarEnReina(igvMallaTriangulos *mallaa){
		this->malla=mallaa;
		tipo=5;
	}
	void pintarPieza(bool seleccionado,float x,float y,float z);
	bool hayQueTransformar(){return transformar;}
   
};

#endif /* PIEZA_H */