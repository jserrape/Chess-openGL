#include "igvTextura.h"

// Metodos constructores y destructor

igvTextura::igvTextura(char *fichero) {
  GLubyte *imagen;

	imagen = loadBMPRaw(fichero, alto, ancho);
 
	//- Generar el identificador de textura y asignarlo al atributo idTextura
	glGenTextures(1, &idTextura);

	//- Enlazar el identificador creado a GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, idTextura);

	//- Especificar la textura, asignádole como textura el array imagen
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0,GL_RGB, GL_UNSIGNED_BYTE, imagen);

	//- Modo de aplicación de la textura
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//- Parámetros de la textura: repetición y filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	delete imagen;
}

void igvTextura::aplicar(void) {
  glBindTexture(GL_TEXTURE_2D, idTextura);
}

igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura); 
}
