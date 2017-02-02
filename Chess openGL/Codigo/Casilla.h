/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Casilla.h
 * Author: Xenahort
 *
 * Created on 25 de noviembre de 2016, 17:24
 */

#ifndef CASILLA_H
#define CASILLA_H
#include "Vertice.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include "igvMaterial.h"
#include "igvColor.h"
#include "igvTextura.h"
using namespace std;



class Casilla {
private:
    vector<Vertice> vertices;
	int id;
	string color;
	igvMaterial *material;
	int mallaQ;
public:
    Casilla();
    Casilla(Vertice &v1,Vertice &v2,Vertice &v3,Vertice &v4,int idd,string colorr);
    Casilla(const Casilla& orig);
    virtual ~Casilla();
    vector<Vertice> GetVertices() const;

	int getId(){return id;};
	void setId(int idd){this->id=idd;};

	void pintarCasilla(bool seleccionado);
    void pintar_quads(float inix, float iniz, float div);
	string getColor(){return color;}
	void setMallaQ(int mall){
		this->mallaQ=mall;
	}
};

#endif /* CASILLA_H */

