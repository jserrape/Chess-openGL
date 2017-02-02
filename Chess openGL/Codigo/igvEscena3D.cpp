#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D () {
	PoV=1;
	ejes = false;
	posicion=0;
	tablero=new Tablero();
	igvPunto3D posicion1(-9,12,0);
	igvPunto3D direccion(0,-1,0);
	igvPunto3D posicion2(9,9,0);
	igvPunto3D posicion3(0,9,0);
	igvColor cAmbF(0.0,0.0,0.0,1.0);
	igvColor cDifF(1.0,1.0,1.0,1.0); 
	igvColor cEspF(1.0,1.0,1.0,1.0);
	foco1=igvFuenteLuz(	GL_LIGHT1,posicion1,cAmbF,cDifF,cEspF,1,0,0,direccion,40,1);
	foco2=igvFuenteLuz(	GL_LIGHT2,posicion2,cAmbF,cDifF,cEspF,1,0,0,direccion,40,1);
	foco3=igvFuenteLuz(	GL_LIGHT3,posicion3,cAmbF,cDifF,cEspF,1,0,0,direccion,40,1);
	foco3.apagar();


	focos[0]=focos[1]=focos[2]=true;
	
}

igvEscena3D::~igvEscena3D() {
	delete tablero;
}


// Metodos publicos 

void pintar_ejes(void) {
  GLfloat rojo[]={1,0,0,1.0};
  GLfloat verde[]={0,1,0,1.0};
  GLfloat azul[]={0,0,1,1.0};

  glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
	glBegin(GL_LINES);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,verde);
	glBegin(GL_LINES);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,azul);
	glBegin(GL_LINES);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}


void igvEscena3D::visualizar() {
	foco1.aplicar();
	foco2.aplicar();
	foco3.aplicar();


	glPushMatrix(); 
		if (ejes) pintar_ejes();
		tablero->funcionPrincipal();
	glPopMatrix (); // restaura la matriz de modelado
};

