#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#include <GL/glut.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Vertice.h"
#include <Windows.h>

using namespace std;

class igvMallaTriangulos {
	protected:
		string pieza;

		vector<float> normales;
		vector<int> normales2;

		float *vertices;
		int contV;
		float *normaless;
		int *cuadrados;
		int contCuadrados;
		int nVertices;
		int nQuads;

	public:
		igvMallaTriangulos(string piezaa);
		~igvMallaTriangulos();
		void visualizar();



};

#endif
