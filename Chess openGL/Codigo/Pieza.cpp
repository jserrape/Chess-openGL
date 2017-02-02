#include "Pieza.h"


Pieza::Pieza() {
}

Pieza::Pieza(int idd,Casilla *caa,string colorr,int tipoo,igvMallaTriangulos *mallaa){
	this->malla=mallaa;
	this->id=idd;
	this->ca=caa;
	this->color=colorr;
	this->tipo=tipoo;
	this->moviendo=false;
	this->inicio=true;
	this->transformar=false;
}


Pieza::~Pieza() {
}

void Pieza::asignaCasilla(Casilla *caa){
		this->ca=caa;
}


void Pieza::pintarPieza(bool seleccionado,float x,float y,float z){
	if(ca!=NULL){
		if(seleccionado){
			GLfloat rojo[]={0.6,0.6,0.1,1};
			glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
		}else{
			if(color=="blanco"){
				igvMaterial matb(igvColor(0.8, 0.8, 0.8), igvColor(0.8, 0.8, 0.8), igvColor(0.2, 0.2, 0.2), 10); //blancas
				matb.aplicar();
			}else{
				igvMaterial matn(igvColor(0.2, 0.2, 0.2), igvColor(0.2, 0.2, 0.2), igvColor(0.2, 0.2, 0.2), 10); //negras
				matn.aplicar();	
			}
			}
		glPushMatrix();
			glTranslatef((ca->GetVertices().at(0).GetX()+1.5/2.0)+x, (ca->GetVertices().at(0).GetY())+y, (ca->GetVertices().at(0).GetZ()+1.5/2.0)+z);
			if(tipo==3 ||  tipo == 4 ){
				glRotated(90,0,1,0);
			}
			if(tipo==2 && color=="blanco"){
				glRotated(180,0,1,0);
			}
			malla->visualizar();
		glPopMatrix ();
	}
}


bool Pieza::movimientoValido(Casilla &destino, bool comer){
	float xOrigen=(ca->GetVertices().at(0).GetX()+6)-(((ca->GetVertices().at(0).GetX()+6)/1.5)*0.5);
	float zOrigen=(ca->GetVertices().at(0).GetZ()+6)-(((ca->GetVertices().at(0).GetZ()+6)/1.5)*0.5);
	float xDestino=(destino.GetVertices().at(0).GetX()+6)-(((destino.GetVertices().at(0).GetX()+6)/1.5)*0.5);
	float zDestino=(destino.GetVertices().at(0).GetZ()+6)-(((destino.GetVertices().at(0).GetZ()+6)/1.5)*0.5);
	int mx=xDestino-xOrigen;
	int mz=zDestino-zOrigen;
	cout<<"Movimiento: "<<mx<<"  "<<mz<<endl;
	switch (tipo) {
		case 0:{
			cout<<"Se va a proceder a mover el peon"<<endl;
			if(color=="blanco"){
				if( (1==mx && 0==mz) && !comer ){
					this->inicio=false;
					if(xDestino==7){
						this->transformar=true;
					}
					return true;
				}
				if( 2==mx && 0==mz && inicio && !comer){
					this->inicio=false;
					return true;
				}
				if(comer && ( (1==mx && 1==mz) || (1==mx && -1==mz) )){
					this->inicio=false;
					if(xDestino==7){
						this->transformar=true;
					}
					return true;
				}
				if(comer && ( (1==mx && 1==mz) || (1==mx && 1==mz) )){
					this->inicio=false;
					if(xDestino==7){
						this->transformar=true;
					}
					return true;
				}
			}else{
				if( -1==mx && 0==mz  && !comer){
					this->inicio=false;
					if(xDestino==0){
						this->transformar=true;
					}
					return true;
				}
				if( -2==mx && 0==mz && inicio  && !comer){
					this->inicio=false;
					return true;
				}
				if(comer && ( (-1==mx && 1==mz) || (-1==mx && -1==mz) )){
					this->inicio=false;
					if(xDestino==0){
						this->transformar=true;
					}
					return true;
				}
				if(comer && ( (-1==mx && 1==mz) || (-1==mx && 1==mz) )){
					this->inicio=false;
					if(xDestino==0){
						this->transformar=true;
					}
					return true;
				}
			}
			return false;
		}
		case 1:{
			cout<<"Se va a proceder a mover la torre"<<endl;
			int mXt[]={0,0,0,0,0,0,0,-1,-2,-3,-4,-5,-6,-7,0,0,0,0,0,0,0,1,2,3,4,5,6,7};
			int mZt[]={-1,-2,-3,-4,-5,-6,-7,0,0,0,0,0,0,0,1,2,3,4,5,6,7,0,0,0,0,0,0,0};
			for(int i=0;i<28;i++){
				if(mXt[i]==mx && mZt[i]==mz){
					return true;
				}
			}
			return false;
		}
		case 2:{
			cout<<"Se va a proceder a mover el caballo"<<endl;
			int mXc[]={-2,-2,-1,-1,1,1,2,2};
			int mZc[]={1,-1,2,-2,2,-2,1,-1};
			for(int i=0;i<8;i++){
				if(mXc[i]==mx && mZc[i]==mz){
					return true;
				}
			}
			return false;
		}
		case 3:{
			cout<<"Se va a proceder a mover el alfil"<<endl;
			int mXa[]={1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7};
			int mZa[]={1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7};
			for(int i=0;i<28;i++){
				if(mXa[i]==mx && mZa[i]==mz){
					return true;
				}
			}
			return false;
		}
		case 4:{
			cout<<"Se va a proceder a mover el rey"<<endl;
			int mXr[]={-1,-1,-1,0,0,1,1,1};
			int mZr[]={1,0,-1,1,-1,1,0,-1};
			for(int i=0;i<8;i++){
				if(mXr[i]==mx && mZr[i]==mz){
					return true;
				}
			}
			return false;
		}
		case 5:{
			cout<<"Se va a proceder a mover la reina"<<endl;
			int mXrr[]={0,0,0,0,0,0,0,-1,-2,-3,-4,-5,-6,-7,0,0,0,0,0,0,0,1,2,3,4,5,6,7,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7};
			int mZrr[]={-1,-2,-3,-4,-5,-6,-7,0,0,0,0,0,0,0,1,2,3,4,5,6,7,0,0,0,0,0,0,0,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7};
			for(int i=0;i<56;i++){
				if(mXrr[i]==mx && mZrr[i]==mz){
					return true;
				}
			}
			return false;
		}
	}
	cout<<"Pieza no registrada"<<endl;
	return false;
}