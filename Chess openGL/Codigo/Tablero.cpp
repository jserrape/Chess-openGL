/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tablero.cpp
 * Author: Xenahort
 * 
 * Created on 25 de noviembre de 2016, 17:43
 */

#include "Tablero.h"

Tablero::Tablero() {
	victoriasJ1=0,victoriasJ2=0;
	casillaNula=new Casilla();
	casillaNula->setId(-1);
	desplazar=false;
	listoParaComer=comer=false;
	comprobarVictoria=false;
	tamElementos=96;
	piezaO=-1;
	jugadorActual=1;
	for(int i=0;i<tamElementos;i++){
		amarillo[i]=false;
	}
	for(int i=0;i<16;i++){
		pintarPiezaJ1[i]=true;
		pintarPiezaJ2[i]=true;
	}
	generarTablero();
	
	piezasMalla[0]=new igvMallaTriangulos("peon");
	piezasMalla[1]=new igvMallaTriangulos("torre");
	piezasMalla[2]=new igvMallaTriangulos("caballo");
	piezasMalla[3]=new igvMallaTriangulos("alfil");
	piezasMalla[4]=new igvMallaTriangulos("rey");
	piezasMalla[5]=new igvMallaTriangulos("reina");

	generarPiezas();
	menu=true;
	for(int i=0;i<6;i++){
		opcionesMenu[i]=false;
	}
	opcionesMenu[1]=opcionesMenu[4]=true;
	sombras=20;
	velocidad=10;
}

Tablero::Tablero(const Tablero& orig) {
	
}

Tablero::~Tablero() {
	delete casillaNula;
	for(int i=0;i<6;i++){
		delete piezasMalla[i];
	}
}


void Tablero::funcionPrincipal(){
	if(menu){
		mostrarMenu();
	}else{
		pintarTablero();
		pintarPiezas();
		if(desplazar){
			comerPieza();		
		}
		if(comprobarVictoria){
			comprobarVictoria=false;
			if(victoriaJ1()){
				++victoriasJ1;
			}else{
				if(victoriaJ2()){
					++victoriasJ2;
				}
			}
		}
		if(victoriaJ1()){
			victoria(1);
		}else{
			if(victoriaJ2()){
				victoria(2);
			}
		}
	}
}


void Tablero::mostrarMenu(){
		glPushName(-1);
		camara->set(igvPunto3D(0, 0, 5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
		camara->aplicar();
		GLfloat negro[]={0,0,0,1};
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(-10, 10, 6.5);
			glVertex3f( 10, 10, 6.5);
			glVertex3f( 10,-10, 6.5);
			glVertex3f(-10.2,-10, 6.5);
		glEnd();
		GLfloat r[]={1,0,0,1};
		GLfloat b[]={1,1,0.5,1};
		GLfloat amar[]={1,1,0,1};
		GLfloat azul[]={0,0.5,1,1};
		GLfloat a[]={0.5,0.5,0,1};
	

		glPushName(97);
	    glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		string texto="Empezar";
		glRasterPos3f(-1, -4.60, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}
		
	    glMaterialfv(GL_FRONT,GL_EMISSION,b);
		glBegin(GL_QUADS);
			glVertex3f(-1-0.5, -4.5+0.5, 7.5);
			glVertex3f(-1-0.5, -4.5-0.5, 7.5);
			glVertex3f(1, -4.5-0.5, 7.5);
			glVertex3f(1, -4.5+0.5, 7.5);
		glEnd();


	    glMaterialfv(GL_FRONT,GL_EMISSION,azul);
		texto="PRACTICA 5. PROYECTO: AJEDREZ";
		glRasterPos3f(-3.5, 5, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}

		glMaterialfv(GL_FRONT,GL_EMISSION,a);
		texto="Calidad de las sombras";
		glRasterPos3f(-5, 3.5, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}


		glPushName(98);
		if(opcionesMenu[0]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Baja";
		glRasterPos3f(-4, 2, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(-4-0.25, 2+0.5, 7.5);
			glVertex3f(-4-0.25, 2-0.35, 7.5);
			glVertex3f(-4+1, 2-0.35, 7.5);
			glVertex3f(-4+1, 2+0.5, 7.5);
		glEnd();


		glPushName(99);
		if(opcionesMenu[1]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Media";
		glRasterPos3f(-1, 2, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(-1-0.25, 2+0.5, 7.5);
			glVertex3f(-1-0.25, 2-0.35, 7.5);
			glVertex3f(-1+1.25, 2-0.35, 7.5);
			glVertex3f(-1+1.25, 2+0.5, 7.5);
		glEnd();

		glPushName(100);
		if(opcionesMenu[2]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Alta";
		glRasterPos3f(2, 2, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(2-0.25, 2+0.5, 7.5);
			glVertex3f(2-0.25, 2-0.35, 7.5);
			glVertex3f(2+1.1, 2-0.35, 7.5);
			glVertex3f(2+1.1, 2+0.5, 7.5);
		glEnd();


		glMaterialfv(GL_FRONT,GL_EMISSION,a);
		texto="Velocidad de movimiento";
		glRasterPos3f(-5, 0.5, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}

		glPushName(101);
		if(opcionesMenu[3]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Fluido";
		glRasterPos3f(-4, -1, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(-4-0.25, -1+0.5, 7.5);
			glVertex3f(-4-0.25, -1-0.35, 7.5);
			glVertex3f(-4+1.5, -1-0.35, 7.5);
			glVertex3f(-4+1.5, -1+0.5, 7.5);
		glEnd();

		glPushName(102);
		if(opcionesMenu[4]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Rapido";
		glRasterPos3f(-1, -1, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(-1-0.25, -1+0.5, 7.5);
			glVertex3f(-1-0.25, -1-0.35, 7.5);
			glVertex3f(-1+1.6, -1-0.35, 7.5);
			glVertex3f(-1+1.6, -1+0.5, 7.5);
		glEnd();

		glPushName(103);
		if(opcionesMenu[5]){
			glMaterialfv(GL_FRONT,GL_EMISSION,amar);
		}else{
			glMaterialfv(GL_FRONT,GL_EMISSION,r);
		}
		texto="Inmediato";
		glRasterPos3f(2, -1, 7.5);
		for(int i=0;i<texto.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto[i]);
		}
		glMaterialfv(GL_FRONT,GL_EMISSION,negro);
		glBegin(GL_QUADS);
			glVertex3f(2-0.25, -1+0.5, 7.5);
			glVertex3f(2-0.25, -1-0.35, 7.5);
			glVertex3f(2+2.1, -1-0.35, 7.5);
			glVertex3f(2+2.1, -1+0.5, 7.5);
		glEnd();

		glutPostRedisplay();
}

void Tablero::victoria(int ganador){
	camara->set(igvPunto3D(0, 0, 5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
	string v1 = static_cast<std::ostringstream*>(&(std::ostringstream() << victoriasJ1))->str();
	string v2 = static_cast<std::ostringstream*>(&(std::ostringstream() << victoriasJ2))->str();
	v1+="  -  "+v2;
	string ganadorr="Ha ganado el jugador ";
	if(ganador==1){
		ganadorr+="1";
	}else{
		ganadorr+="2";
	}
	glPushName(96);
	GLfloat negro[]={0,0,0,1};
	glMaterialfv(GL_FRONT,GL_EMISSION,negro);
	glBegin(GL_QUADS);
		glVertex3f(-10, 10, 6.5);
		glVertex3f( 10, 10, 6.5);
		glVertex3f( 10,-10, 6.5);
		glVertex3f(-10.2,-10, 6.5);
	glEnd();
	GLfloat r[]={1,0,0,1};
	glMaterialfv(GL_FRONT,GL_EMISSION,r);
	glRasterPos3f(-2, 0.3, 7.5);
	for(int i=0;i<ganadorr.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,ganadorr[i]);
	}
	glRasterPos3f(-0.6, -0.5, 7.5);
	for(int i=0;i<v1.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,v1[i]);
	}

	GLfloat amarillo[]={1,1,0,1};
	glMaterialfv(GL_FRONT,GL_EMISSION,amarillo);
	glBegin(GL_QUADS);
		glVertex3f(-3.2, 1, 7);
		glVertex3f( 3.2, 1, 7);
		glVertex3f( 3.2,-1, 7);
		glVertex3f(-3.2,-1, 7);
	glEnd();
}

void Tablero::reiniciarPartida(){
	generarPiezas();
	for(int i=0;i<16;i++){
		pintarPiezaJ1[i]=true;
		pintarPiezaJ2[i]=true;
	}
	if(jugadorActual==1){
		camara->set(igvPunto3D(-5.0, camara->getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
		camara->aplicar();
	}else{
		camara->set(igvPunto3D(5.0, camara->getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
		camara->aplicar();
	}
}

void Tablero::cambiarColor(int a,bool b) { 
	if (a != -1){
		if(a==96){
			reiniciarPartida();
		}else{
			if(a>=97){

				switch (a) {
					case 97:
						menu=false;
						camara->set(igvPunto3D(-5.0, camara->getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
						camara->aplicar();
						for(int i=0;i<8;i++){
							for(int j=0;j<8;j++){
								casillas[i][j].setMallaQ(sombras);
							}
						}
						break;
					case 98:
						opcionesMenu[1]=opcionesMenu[2]=false;
						opcionesMenu[0]=true;
						sombras=10;
						break;
					case 99:
						opcionesMenu[0]=opcionesMenu[2]=false;
						opcionesMenu[1]=true;
						sombras=20;
						break;
					case 100:
						opcionesMenu[1]=opcionesMenu[0]=false;
						opcionesMenu[2]=true;
						sombras=30;
						break;
					case 101:
						opcionesMenu[5]=opcionesMenu[4]=false;
						opcionesMenu[3]=true;
						velocidad=25;
						break;
					case 102:
						opcionesMenu[5]=opcionesMenu[3]=false;
						opcionesMenu[4]=true;
						velocidad=10;
						break;
					case 103:
						opcionesMenu[3]=opcionesMenu[4]=false;
						opcionesMenu[5]=true;
						velocidad=0;
						break;
				}
			}else{
				if(!victoriaJ1() && !victoriaJ2())
					amarillo[a] = b;
			}
		}
	}
}

void Tablero::cambiarJugador(){
	if(jugadorActual==1){
		jugadorActual=2;
		camara->set(igvPunto3D(5.0, camara->getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
		camara->aplicar();
	}else{
		jugadorActual=1;
		camara->set(igvPunto3D(-5.0, camara->getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
		camara->aplicar();
	}
}

void Tablero::comerPieza(){
	pintarFichaMoviendose();
	if(listoParaComer){
		if(colorP=="blanco"){
			for(int i=0;i<16;i++){
				if(piezasJ2[i].getCasilla()->getId()==casillaD){
					pintarPiezaJ2[i]=false;
					piezasJ2[i].asignaCasilla(casillaNula); 
				}
			}
		}else{
			for(int i=0;i<16;i++){
				if(piezasJ1[i].getCasilla()->getId()==casillaD){
					pintarPiezaJ1[i]=false;
					piezasJ1[i].asignaCasilla(casillaNula); 
				}
			}
		}	
		listoParaComer=false;
	}
}

void Tablero::pintarPiezas(){
	for(int i=0;i<16;i++){
		if(pintarPiezaJ1[i]){
			glPushName(piezasJ1[i].getId());
				piezasJ1[i].pintarPieza(amarillo[piezasJ1[i].getId()],0,0,0);
		  }
		  if(pintarPiezaJ2[i]){
			glPushName(piezasJ2[i].getId());
				piezasJ2[i].pintarPieza(amarillo[piezasJ2[i].getId()],0,0,0);
		}
	}

}

void Tablero::generarTablero(){
	string colorf="blanco";
	string colorC="blanco";
	float x,z=(-4*1.5),y=0;
	int id=0;
	for(int i=0;i<8;i++){
		x=(-4*1.5);
		for(int j=0;j<8;j++){
			if(colorf=="blanco")
				colorf="negro";
			else
				colorf="blanco";
			casillas[i][j]=Casilla(Vertice(x,y,z),Vertice(x+1.5,y,z),Vertice(x+1.5,y,z+1.5),Vertice(x,y,z+1.5),id,colorf);
			x+=1.5;
			++id;
		}
		z+=1.5;
		if(colorC=="blanco"){
			colorC="negro";
			colorf="negro";
		}else{
			colorC="blanco";
			colorf="blanco";
		}
	}
}

void Tablero::generarPiezas(){
	piezasJ1[0]=Pieza(64,&casillas[0][1],"blanco",0,piezasMalla[0]);
	piezasJ1[1]=Pieza(65,&casillas[1][1],"blanco",0,piezasMalla[0]);
	piezasJ1[2]=Pieza(66,&casillas[2][1],"blanco",0,piezasMalla[0]);
	piezasJ1[3]=Pieza(67,&casillas[3][1],"blanco",0,piezasMalla[0]);
	piezasJ1[4]=Pieza(68,&casillas[4][1],"blanco",0,piezasMalla[0]);
	piezasJ1[5]=Pieza(69,&casillas[5][1],"blanco",0,piezasMalla[0]);
	piezasJ1[6]=Pieza(70,&casillas[6][1],"blanco",0,piezasMalla[0]);
	piezasJ1[7]=Pieza(71,&casillas[7][1],"blanco",0,piezasMalla[0]);

	piezasJ1[8]=Pieza(72,&casillas[0][0],"blanco",1,piezasMalla[1]);
	piezasJ1[9]=Pieza(73,&casillas[1][0],"blanco",2,piezasMalla[2]);
	piezasJ1[10]=Pieza(74,&casillas[2][0],"blanco",3,piezasMalla[3]);
	piezasJ1[11]=Pieza(75,&casillas[3][0],"blanco",4,piezasMalla[4]);
	piezasJ1[12]=Pieza(76,&casillas[4][0],"blanco",5,piezasMalla[5]);
	piezasJ1[13]=Pieza(77,&casillas[5][0],"blanco",3,piezasMalla[3]);
	piezasJ1[14]=Pieza(78,&casillas[6][0],"blanco",2,piezasMalla[2]);
	piezasJ1[15]=Pieza(79,&casillas[7][0],"blanco",1,piezasMalla[1]);
	piezasJ2[0]=Pieza(80,&casillas[0][6],"negro",0,piezasMalla[0]);
	piezasJ2[1]=Pieza(81,&casillas[1][6],"negro",0,piezasMalla[0]);
	piezasJ2[2]=Pieza(82,&casillas[2][6],"negro",0,piezasMalla[0]);
	piezasJ2[3]=Pieza(83,&casillas[3][6],"negro",0,piezasMalla[0]);
	piezasJ2[4]=Pieza(84,&casillas[4][6],"negro",0,piezasMalla[0]);
	piezasJ2[5]=Pieza(85,&casillas[5][6],"negro",0,piezasMalla[0]);
	piezasJ2[6]=Pieza(86,&casillas[6][6],"negro",0,piezasMalla[0]);
	piezasJ2[7]=Pieza(87,&casillas[7][6],"negro",0,piezasMalla[0]);

	piezasJ2[8]=Pieza(88,&casillas[0][7],"negro",1,piezasMalla[1]);
	piezasJ2[9]=Pieza(89,&casillas[1][7],"negro",2,piezasMalla[2]);
	piezasJ2[10]=Pieza(90,&casillas[2][7],"negro",3,piezasMalla[3]);
	piezasJ2[11]=Pieza(91,&casillas[3][7],"negro",4,piezasMalla[4]);
	piezasJ2[12]=Pieza(92,&casillas[4][7],"negro",5,piezasMalla[5]);
	piezasJ2[13]=Pieza(93,&casillas[5][7],"negro",3,piezasMalla[3]);
	piezasJ2[14]=Pieza(94,&casillas[6][7],"negro",2,piezasMalla[2]);
	piezasJ2[15]=Pieza(95,&casillas[7][7],"negro",1,piezasMalla[1]);
}

void Tablero::pintarTablero(){
	igvTextura t1("s1.bmp");
	igvTextura t2("s2.bmp");
	
	glInitNames();
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			glPushName(casillas[i][j].getId());
			if(casillas[i][j].getColor()=="blanco"){
				t2.aplicar();
			}else{
				t1.aplicar();
			}
			casillas[i][j].pintarCasilla(amarillo[casillas[i][j].getId()]);
		}

	}
}

void Tablero::pintarFichaMoviendose(){
		//MOVIMIENTO EN Y
		int tSleep=velocidad;
		if(velocidad==0){
			desplazar=false;
			if(colorP=="blanco"){
				if(piezasJ1[piezaO].hayQueTransformar()){
					piezasJ1[piezaO].transformarEnReina(piezasMalla[5]);
				}
				piezasJ1[piezaO].asignaCasilla(punteroAux);
				pintarPiezaJ1[piezaO]=true;
			}else{
				if(piezasJ2[piezaO].hayQueTransformar()){
					piezasJ2[piezaO].transformarEnReina(piezasMalla[5]);
				}
				piezasJ2[piezaO].asignaCasilla(punteroAux);
				pintarPiezaJ2[piezaO]=true;
			}
			if(comer){
				listoParaComer=true;
				comer=false;
				comprobarVictoria=true;
			}
			cambiarJugador();
			for(int i=0;i<64;i++){ 
				amarillo[i]=false;
			}
			glutPostRedisplay();
			return;
		}
		if(cMovimientos[0]<15){
			posMov[0]+=0.2;
			++cMovimientos[0];
			if(colorP=="blanco"){
				piezasJ1[piezaO].pintarPieza(amarillo[piezasJ1[piezaO].getId()],0,posMov[0],0);
			}else{
				piezasJ2[piezaO].pintarPieza(amarillo[piezasJ2[piezaO].getId()],0,posMov[0],0);
			}
			Sleep(tSleep);
			glutPostRedisplay();
			return;
		}
		//MOVIMIENTO EN X
		float aux1x;
		if(colorP=="blanco"){
			aux1x=piezasJ1[piezaO].getCasilla()->GetVertices().at(0).GetX();
		}else{
			aux1x=piezasJ2[piezaO].getCasilla()->GetVertices().at(0).GetX();
		}

		float aux2x=punteroAux->GetVertices().at(0).GetX();
		float auxx=(abs(aux2x-aux1x)*10);
		if(cMovimientos[1]<auxx){
			if(aux1x<aux2x){
				posMov[1]+=0.1;
			}else{
				posMov[1]-=0.1;
			}
		}
		//MOVIMIENTO EN Z
		float aux1z;
		if(colorP=="blanco"){
			aux1z=piezasJ1[piezaO].getCasilla()->GetVertices().at(0).GetZ();
		}else{
			aux1z=piezasJ2[piezaO].getCasilla()->GetVertices().at(0).GetZ();
		}
		float aux2z=punteroAux->GetVertices().at(0).GetZ();
		float auxz=(abs(aux2z-aux1z)*10);
		if(cMovimientos[2]<auxz){
			if(aux1z<aux2z){
				posMov[2]+=0.1;
			}else{
				posMov[2]-=0.1;
			}
		}
		if(cMovimientos[2]<auxz || cMovimientos[1]<auxx){
			if(colorP=="blanco"){
				piezasJ1[piezaO].pintarPieza(amarillo[piezasJ1[piezaO].getId()],posMov[1],posMov[0],posMov[2]);
			}else{
				piezasJ2[piezaO].pintarPieza(amarillo[piezasJ2[piezaO].getId()],posMov[1],posMov[0],posMov[2]);
			}
			++cMovimientos[1];
			++cMovimientos[2];
			Sleep(tSleep);
			glutPostRedisplay();
			return;
		}
		//MOVIMIENTO EN -Y
		if(cMovimientos[3]<15){
			posMov[3]-=0.2;
			++cMovimientos[3];
			if(colorP=="blanco"){
				piezasJ1[piezaO].pintarPieza(amarillo[piezasJ1[piezaO].getId()],posMov[1],posMov[3]+posMov[0],posMov[2]);
			}else{
				piezasJ2[piezaO].pintarPieza(amarillo[piezasJ2[piezaO].getId()],posMov[1],posMov[3]+posMov[0],posMov[2]);
			}
			Sleep(tSleep);
			glutPostRedisplay();
			return;
		}
		desplazar=false;
		if(colorP=="blanco"){
			if(piezasJ1[piezaO].hayQueTransformar()){
				piezasJ1[piezaO].transformarEnReina(piezasMalla[5]);
			}
			piezasJ1[piezaO].pintarPieza(amarillo[piezasJ1[piezaO].getId()],posMov[1],posMov[3]+posMov[0],posMov[2]);
			piezasJ1[piezaO].asignaCasilla(punteroAux);
			pintarPiezaJ1[piezaO]=true;
		}else{
			if(piezasJ2[piezaO].hayQueTransformar()){
				piezasJ2[piezaO].transformarEnReina(piezasMalla[5]);
			}
			piezasJ2[piezaO].pintarPieza(amarillo[piezasJ2[piezaO].getId()],posMov[1],posMov[3]+posMov[0],posMov[2]);
			piezasJ2[piezaO].asignaCasilla(punteroAux);
			pintarPiezaJ2[piezaO]=true;
		}
		if(comer){
			listoParaComer=true;
			comer=false;
			comprobarVictoria=true;
		}
		cambiarJugador();
		for(int i=0;i<64;i++){ 
			amarillo[i]=false;
		}
		glutPostRedisplay();
		Sleep(tSleep+300);
}

void Tablero::hayQueMoverPieza(int pieza,int casilla){
	Pieza *p=NULL;
	int jj;
	for(int i=0;i<16;i++){
		if(piezasJ1[i].getId()==pieza){
			p=&piezasJ1[i];
			i=16;
		}
		if(piezasJ2[i].getId()==pieza){
			p=&piezasJ2[i];
			i=16;
		}
	}
	if(p==NULL){
		return;
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(casillas[i][j].getId()==casilla){
				punteroAux=&casillas[i][j];
			}
		}
	}

	for(int i=0;i<4;i++){
		cMovimientos[i]=0;
		posMov[i]=0.0;
	}
	comer=false;
	desplazar=true;
	piezaO=pieza;
	casillaD=casilla;


	for(int i=0;i<16;i++){
		if(piezasJ1[i].getId()==pieza){
			if(jugadorActual==2){
				desplazar=false;
				return;
			}
			piezaO-=64;
			colorP=piezasJ1[i].getColor();
			pintarPiezaJ1[piezaO]=false;
			jj=1;
			continue;
		}
		if(piezasJ2[i].getId()==pieza){
			if(jugadorActual==1){
				desplazar=false;
				return;
			}
			piezaO-=(64+16);
			colorP=piezasJ2[i].getColor();
			pintarPiezaJ2[piezaO]=false;
			jj=2;
			continue;
		}
	}

	//VER SI es del JUGADOR LA PIEZA
	if(colorP=="blanco"){
		for(int i=0;i<16;i++){
			//VER SI LA CASILLA ES ALIADA
			if(piezasJ1[i].getCasilla()->getId()==casilla){
				desplazar=false;
				pintarPiezaJ1[piezaO]=true;
			}
			//VER SI LA CASILLA ES ENEMIGA
			if(piezasJ2[i].getCasilla()->getId()==casilla){
				comer=true;
			}
		}	
	}else{
		for(int i=0;i<16;i++){
			//VER SI LA CASILLA ES ALIADA
			if(piezasJ2[i].getCasilla()->getId()==casilla){
				desplazar=false;
				pintarPiezaJ2[piezaO]=true;
			}
			//VER SI LA CASILLA ES ENEMIGA
			if(piezasJ1[i].getCasilla()->getId()==casilla){
				comer=true;
			}
		}
	}
	//YA TENGO LA PIEZA A MOVER Y LA CASILLA DE DESTINO Y SI COME
	if(!p->movimientoValido(*punteroAux, comer)){
		desplazar=false;
		if(jj==1){
			pintarPiezaJ1[piezaO]=true;
		}else{
			pintarPiezaJ2[piezaO]=true;
		}
		comer=false;
		return;
	}
}

bool Tablero::victoriaJ1(){
	for(int i=8;i<16;i++){
		if(piezasJ2[i].getTipo()==4 && piezasJ2[i].getCasilla()->getId()==-1){
			return true;
		}
	}
	return false;
}

bool Tablero::victoriaJ2(){
	for(int i=8;i<16;i++){
		if(piezasJ1[i].getTipo()==4 && piezasJ1[i].getCasilla()->getId()==-1){
			return true;
		}
	}
	return false;
}