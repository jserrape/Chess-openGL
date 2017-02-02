/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tablero.h
 * Author: Xenahort
 *
 * Created on 25 de noviembre de 2016, 17:43
 */

#ifndef TABLERO_H
#define TABLERO_H
#include "Casilla.h"
#include "igvMallaTriangulos.h"
#include "Pieza.h"
#include "igvCamara.h"
#include "igvTextura.h"



class Tablero {
private:
	//elementos
	Casilla casillas[8][8];
	igvMallaTriangulos* piezasMalla[6];
	int tamElementos;
	bool amarillo[96];
	Pieza piezasJ1[16];
	Pieza piezasJ2[16];
	bool pintarPiezaJ1[16];
	bool pintarPiezaJ2[16];

	int jugadorActual;
	int victoriasJ1,victoriasJ2;
	igvCamara *camara;
	bool comprobarVictoria;

	//Movimiento de piezas
	bool desplazar;
	int piezaO,casillaD;
	Casilla *casillaNula;
	Casilla *punteroAux;
	string colorP;
	int cMovimientos[4];
	float posMov[4];
	bool comer,listoParaComer;


	bool menu;
	bool opcionesMenu[6];
public:
    Tablero();
    Tablero(const Tablero& orig);
    virtual ~Tablero();

	void cambiarColor(int a,bool b);
	void generarVertices();
	void generarTablero();
	void generarPiezas();
	void pintarTablero();
	void hayQueMoverPieza(int pieza,int casilla);
	void pintarFichaMoviendose();
	void pintarPiezas();
	void comerPieza();
	void funcionPrincipal();

	bool victoriaJ1();
	bool victoriaJ2();
	void victoria(int ganador);
	void reiniciarPartida();


	void mostrarMenu();
	int sombras;
	int velocidad;

	void cambiarJugador();
	int getJugador(){
		return jugadorActual;
	}

	void setCamara(igvCamara *camaraa){
		this->camara=camaraa;
	}

};

#endif /* TABLERO_H */

