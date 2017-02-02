#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>
#include "Tablero.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

class igvEscena3D {
	protected:
		bool ejes;
		int posicion;
		int PoV;
		Tablero *tablero;
		igvFuenteLuz foco1;
		igvFuenteLuz foco2;
		igvFuenteLuz foco3;
		bool focos[3];
	public:
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
		void visualizar(void);

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
		int get_posicion(){return posicion;};
		void set_posicion(){
			++posicion;
			if(get_posicion()==3){
				posicion=0;
			}
		}
		
		int get_PoV() { return PoV; };
		void set_PoV() {
			PoV++;
			if (PoV == 3)
				PoV = 0;
		}

		Tablero* getTablero(){return tablero;};

		bool getFoco1(){return focos[0];}
		bool getFoco2(){return focos[1];}
		bool getFoco3(){return focos[2];}


		void setFoco1(){
			if(focos[1]){
				focos[1]=false;
				foco1.apagar();
			}else{
				focos[1]=true;
				foco1.encender();
			}
		}
		void setFoco2(){
			if(focos[2]){
				focos[2]=false;
				foco2.apagar();
			}else{
				focos[2]=true;
				foco2.encender();
			}
		}
		void setFoco3(){
			if(focos[3]){
				focos[3]=false;
				foco3.apagar();
			}else{
				focos[3]=true;
				foco3.encender();
			}
		}

};

#endif
