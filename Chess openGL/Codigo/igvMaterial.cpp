#include "igvMaterial.h"

// Metodos constructores 

igvMaterial::igvMaterial () {
	
}

igvMaterial::~igvMaterial () {

}

igvMaterial::igvMaterial (const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {

// APARTADO C
// Aplicar los valores de los atributos del objeto igvMaterial:
// - coeficiente de reflexión de la luz ambiental
	GLfloat reflexionAmbiental[3];
	reflexionAmbiental[0]=(GLfloat)Ka[R];
	reflexionAmbiental[1]=(GLfloat)Ka[G];
	reflexionAmbiental[2]=(GLfloat)Ka[B];
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, reflexionAmbiental);
// - coeficiente de reflexión difuso
	GLfloat reflexionDifuso[3];
	reflexionDifuso[0]=(GLfloat)Kd[R];
	reflexionDifuso[1]=(GLfloat)Kd[G];
	reflexionDifuso[2]=(GLfloat)Kd[B];
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, reflexionDifuso);
// - coeficiente de reflesión especular
	GLfloat reflexionEspecular[3];
	reflexionEspecular[0]=(GLfloat)Ks[R];
	reflexionEspecular[1]=(GLfloat)Ks[G];
	reflexionEspecular[2]=(GLfloat)Ks[B];
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, reflexionEspecular);
// - exponente de Phong
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);
// establecer como color de emisión (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
	GLfloat emision[3]={0.0,0.0,0.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



