#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"
#include <Windows.h>

extern igvInterfaz interfaz; 

igvInterfaz::igvInterfaz () {
	modo = IGV_VISUALIZAR;
	objeto_seleccionado = -1;
	boton_retenido = false;
}

igvInterfaz::~igvInterfaz () {}


void igvInterfaz::crear_mundo(void) {
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(-5.0, 8, 0),igvPunto3D(0,0,0),igvPunto3D(0,1.0,0),
		                                -1*4.5, 1*4.5, -1*4.5, 1*4.5, -1*3, 200);
	interfaz.escena.getTablero()->setCamara(&camara);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){																
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana,_alto_ventana);
	glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); 
	glClearColor(1.0,1.0,1.0,0.0); 

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	crear_mundo(); 
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); 
}


void igvInterfaz::set_glutSpecialFunc(int key, int x, int y) {
	switch (key) {
		case (GLUT_KEY_RIGHT): 
			
			break;
		case (GLUT_KEY_LEFT): 
			
			break;
		case (GLUT_KEY_UP): 
			interfaz.camara.incrementaAltura();
			if(interfaz.escena.getTablero()->getJugador()==1){
				interfaz.camara.set(igvPunto3D(-5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
			}else{
				interfaz.camara.set(igvPunto3D(5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
			}
			interfaz.camara.aplicar();
			break;
		case (GLUT_KEY_DOWN): 
			interfaz.camara.decrementaAltura();
			if(interfaz.escena.getTablero()->getJugador()==1){
				interfaz.camara.set(igvPunto3D(-5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
			}else{
				interfaz.camara.set(igvPunto3D(5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
			}
			interfaz.camara.aplicar();
			break;
	}

	glutPostRedisplay(); 
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 'v': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
			switch (interfaz.escena.get_PoV()) {
			case 0:
				if(interfaz.escena.getTablero()->getJugador()==1){
					interfaz.camara.set(igvPunto3D(-5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
				}else{
					interfaz.camara.set(igvPunto3D(5.0, interfaz.camara.getAltura(), 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
				}
				break;
			case 1:
				if(interfaz.escena.getTablero()->getJugador()==1){
					interfaz.camara.set(igvPunto3D(0, 5.0, 0), igvPunto3D(0, 0, 0), igvPunto3D(1.0, 0, 0));
				}else{
					interfaz.camara.set(igvPunto3D(0, 5.0, 0), igvPunto3D(0, 0, 0), igvPunto3D(-1.0, 0, 0));
				}
				break;
			case 2:
				interfaz.camara.set(igvPunto3D(0, interfaz.camara.getAltura(), -5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
				break;
			}
			interfaz.camara.aplicar();
			interfaz.escena.set_PoV();
		break;
		case '1': 
			interfaz.escena.setFoco1();
			break;
		case '2': 
			interfaz.escena.setFoco2();
			break;
		case '3': 
			interfaz.escena.setFoco3();
			break;
		case '4': 
			//interfaz.escena.setFoco4();
			break;
		case '-': // zoom in
			interfaz.camara.zoomIn();
			interfaz.camara.aplicar();
			break;
		case '+': // zoom out
			interfaz.camara.zoomOut();
			interfaz.camara.aplicar();
			break;
		case 'e': // activa/desactiva la visualizacion de los ejes
			interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	  break;
    case 27: // tecla de escape para SALIR
      exit(1);
    break;
  }
	glutPostRedisplay(); 
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	GLuint lista_impactos[1024]; 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	if (interfaz.modo == IGV_SELECCIONAR) {
		interfaz.escena.getTablero()->cambiarColor(interfaz.objeto_seleccionado, false);
		interfaz.inicia_seleccion(1024,lista_impactos);
	}

	interfaz.camara.aplicar();

	interfaz.escena.visualizar();

	if (interfaz.modo == IGV_SELECCIONAR) {
		interfaz.finaliza_seleccion(1024,lista_impactos); 
		interfaz.escena.getTablero()->cambiarColor(interfaz.objeto_seleccionado, true);
	}	else {
		glutSwapBuffers();
	}
}

void igvInterfaz::set_glutMouseFunc(GLint boton,GLint estado,GLint x,GLint y) {
    if (boton == GLUT_LEFT_BUTTON) {
		bool aux;
		if(estado == GLUT_DOWN){
			aux=true;
		}else{
			aux=false;
		}
        interfaz.boton_retenido =  aux;
        if (interfaz.boton_retenido)  interfaz.modo = IGV_SELECCIONAR;
        interfaz.cursorX = x;
        interfaz.cursorY = y;
    }
        glutPostRedisplay();
}

void igvInterfaz::set_glutMotionFunc(GLint x,GLint y) {
	interfaz.cursorX = x;
    interfaz.cursorY = y;

	glutPostRedisplay();
}

void igvInterfaz::set_glutIdleFunc() {

}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutSpecialFunc(set_glutSpecialFunc);

	glutMouseFunc(set_glutMouseFunc); 
	glutMotionFunc(set_glutMotionFunc); 
	glutIdleFunc(set_glutIdleFunc);
}

void igvInterfaz::inicia_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {
	glSelectBuffer(TAMANO_LISTA_IMPACTOS, lista_impactos);

	glRenderMode(GL_SELECT);

	camara.establecerSeleccion(2,2,cursorX,cursorY);

}

int procesar_impactos(int numero_impactos,GLuint *lista_impactos) {
	GLuint minimaZ = 0xffffffff;
    int aux = -1;
	int j=0;
    for (int i=0; i<numero_impactos; ++i) {
		if (lista_impactos[j+1] < minimaZ) {
			minimaZ = lista_impactos[j+1];
			aux = j;
		}
		j = j + 3 + lista_impactos[j];
    }

	if (lista_impactos[aux] > 0) {
		return lista_impactos[aux + 2 + lista_impactos[aux]];
     }

	return(-1);
}

void igvInterfaz::finaliza_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {
	int num_impactos = glRenderMode(GL_RENDER);

	if (num_impactos > 0){
		int aux=objeto_seleccionado;
		objeto_seleccionado = procesar_impactos(num_impactos, lista_impactos);
		if(objeto_seleccionado>=0 && objeto_seleccionado<=63 && aux>=64){
			cout<<"Hay que mover una ficha"<<endl;
			interfaz.escena.getTablero()->hayQueMoverPieza(aux,objeto_seleccionado);
		}
	}else{
		objeto_seleccionado = -1;
	}

	interfaz.modo = IGV_VISUALIZAR;

	camara.establecerVisualizacion();
}
