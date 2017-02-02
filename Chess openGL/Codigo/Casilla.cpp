/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Casilla.cpp
 * Author: Xenahort
 * 
 * Created on 25 de noviembre de 2016, 17:24
 */

#include "Casilla.h"

Casilla::Casilla() {
}
Casilla::Casilla(Vertice &v1,Vertice &v2,Vertice &v3,Vertice &v4,int idd,string colorr){
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
	this->id=idd;
	this->color=colorr;
	material= new igvMaterial(igvColor(1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0), 10);
}
Casilla::Casilla(const Casilla& orig) {
}

Casilla::~Casilla() {
}

vector<Vertice> Casilla::GetVertices() const {
    return vertices;
}

void Casilla::pintarCasilla(bool seleccionado){
		if(!seleccionado){
			material->aplicar();
		}else{
			igvMaterial matn(igvColor(1.0, 1.0, 0.0), igvColor(0.0, 0.0, 0.0), igvColor(0.0, 0.0, 0.0), 10); //seleccionado
			matn.aplicar();	
		}
		float ancho=0.5;
		//cara 1
		float x=vertices.at(0).GetX();
		float z=vertices.at(0).GetZ();

		pintar_quads(x,z,mallaQ);

		glBegin(GL_QUADS);
			glNormal3f(0,-1,0);
			//cara 2
			vertices.at(0).pintarVertice();
			glVertex3f(vertices.at(0).GetX(),vertices.at(0).GetY()-ancho,vertices.at(0).GetZ());
			glVertex3f(vertices.at(3).GetX(),vertices.at(3).GetY()-ancho,vertices.at(3).GetZ());
			vertices.at(3).pintarVertice();
			//cara 3
			vertices.at(1).pintarVertice();
			glVertex3f(vertices.at(1).GetX(),vertices.at(1).GetY()-ancho,vertices.at(1).GetZ());
			glVertex3f(vertices.at(2).GetX(),vertices.at(2).GetY()-ancho,vertices.at(2).GetZ());
			vertices.at(2).pintarVertice();
			//cara 4
			vertices.at(0).pintarVertice();
			glVertex3f(vertices.at(0).GetX(),vertices.at(0).GetY()-ancho,vertices.at(0).GetZ());
			glVertex3f(vertices.at(1).GetX(),vertices.at(1).GetY()-ancho,vertices.at(1).GetZ());
			vertices.at(1).pintarVertice();
			//cara 5
			vertices.at(2).pintarVertice();
			glVertex3f(vertices.at(2).GetX(),vertices.at(2).GetY()-ancho,vertices.at(2).GetZ());
			glVertex3f(vertices.at(3).GetX(),vertices.at(3).GetY()-ancho,vertices.at(3).GetZ());
			vertices.at(3).pintarVertice();
			//cara 6
			glVertex3f(vertices.at(0).GetX(),vertices.at(0).GetY()-ancho,vertices.at(0).GetZ());
			glVertex3f(vertices.at(1).GetX(),vertices.at(1).GetY()-ancho,vertices.at(1).GetZ());
			glVertex3f(vertices.at(2).GetX(),vertices.at(2).GetY()-ancho,vertices.at(2).GetZ());
			glVertex3f(vertices.at(3).GetX(),vertices.at(3).GetY()-ancho,vertices.at(3).GetZ());
		glEnd();

	}

void Casilla::pintar_quads(float inix, float iniz, float div) {
	float ini_x = inix;
	float ini_z = iniz;
	float tam_x = 1.5/div;
	float tam_z = 1.5/div;

	float ini_xx = 0.0;
	float ini_zz = 0.0;
	float tam_xx = 1.0/div;
	float tam_zz = -1.0/div;


	for (int i=0; i<div; i++) {
		for (int j=0; j<div; j++) {
			glNormal3f(0,1,0);
			glBegin(GL_QUADS);
				glTexCoord2f(tam_xx + (tam_xx*i),tam_zz*j);	//1,0
				glVertex3f((tam_x + (tam_x*i))+ini_x	, 0.0, (tam_z*j)+ini_z);

				glTexCoord2f(tam_xx*i,tam_zz*j); //0,0
				glVertex3f((tam_x*i)+ini_x				, 0.0,(tam_z*j)+ini_z);

				glTexCoord2f(tam_xx*i,tam_zz+(tam_zz*j));//0,1
				glVertex3f((tam_x*i)+ini_x				, 0.0,tam_z+(tam_z*j)+ini_z);

				glTexCoord2f(tam_xx + (tam_xx*i),tam_zz+(tam_zz*j));//1,1
				glVertex3f((tam_x + (tam_x*i))+ini_x	, 0.0,tam_z+(tam_z*j)+ini_z);
			glEnd();
		}
	}
}
