#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include "igvMallaTriangulos.h"

// Metodos constructores 

igvMallaTriangulos::igvMallaTriangulos(string piezaa) {
	this->pieza=piezaa;
	string nombreFichero=this->pieza+".obj";
	fstream fe(nombreFichero,ios::in);
	if (!fe) {
		cout<<"error al leer el fichero"<<endl;
	}else{
		cout<<"Fichero encontrado: "<<nombreFichero<<endl;
	}
	string s;
	float x,y,z;
	int vertice,textura,normal;
	while(getline(fe, s)){
		if(s[0]=='n'&& s[1]=='v'){
			istringstream isstream(s);
			string tempStr;
			isstream >> tempStr; // basura
			isstream >> tempStr; // n
			nVertices=atoi(tempStr.c_str());
			vertices = new float[nVertices];
			contV=0;
		}
		if(s[0]=='n'&& s[1]=='f'){
			istringstream isstream(s);
			string tempStr;
			isstream >> tempStr; // basura
			isstream >> tempStr; // n
			nQuads=atoi(tempStr.c_str());
			cuadrados = new int[nQuads];
			contCuadrados=0;
		}
		if(s[0]=='v'&& s[1]==' '){
			istringstream isstream(s);
			string tempStr;
			isstream >> tempStr; //'v' basura
			isstream >> tempStr; // v1
			x=(float)atof(tempStr.c_str());
			vertices[contV++]=x;
			isstream >> tempStr; //v2
			y=(float)atof(tempStr.c_str());
			vertices[contV++]=y;
			isstream >> tempStr; //v3
			z=(float)atof(tempStr.c_str());
			vertices[contV++]=z;
		}
		if(s[0]=='v'&& s[1]=='n'){
			istringstream isstream(s);
			string tempStr;
			isstream >> tempStr; //'v' basura
			isstream >> tempStr; // vn1
			x=(float)atof(tempStr.c_str());
			normales.push_back(x);
			isstream >> tempStr; //vn2
			y=(float)atof(tempStr.c_str());
			normales.push_back(y);
			isstream >> tempStr; //vn3
			z=(float)atof(tempStr.c_str());
			normales.push_back(z);
		}
		if(s[0]=='f'&& s[1]==' '){
			//cout<<"cara: "<<s<<endl;
			string delimiter = "/";
			istringstream isstream(s);
			string tempStr;
			isstream >> tempStr; //'f' basura

			isstream >> tempStr; // f1
			size_t pos = 0;
			string token;
			tempStr+="/";
			pos = tempStr.find(delimiter);
			vertice = (atoi((tempStr.substr(0, pos)).c_str())-1);
			cuadrados[contCuadrados++]=vertice;
			//cout<<vertice<<endl;
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			textura = atoi((tempStr.substr(0, pos)).c_str());
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			normal = (atoi((tempStr.substr(0, pos)).c_str())-1);
			normales2.push_back(normal);
			tempStr.erase(0, pos + delimiter.length());
			//cout<<vertice<<"  "<<normal<<endl;
			
			//Sleep(2000);

			isstream >> tempStr; // f2
			pos = 0;
			tempStr+="/";
			pos = tempStr.find(delimiter);
			vertice = (atoi((tempStr.substr(0, pos)).c_str())-1);
			cuadrados[contCuadrados++]=vertice;
			//cout<<vertice<<endl;
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			textura = atoi((tempStr.substr(0, pos)).c_str());
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			normal = (atoi((tempStr.substr(0, pos)).c_str())-1);
			normales2.push_back(normal);
			tempStr.erase(0, pos + delimiter.length());
			//cout<<vertice<<"  "<<normal<<endl;
			
			//Sleep(2000);

			isstream >> tempStr; // f3
			pos = 0;
			tempStr+="/";
			pos = tempStr.find(delimiter);
			vertice = (atoi((tempStr.substr(0, pos)).c_str())-1); 
			cuadrados[contCuadrados++]=vertice;
			//cout<<vertice<<endl;
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			textura = atoi((tempStr.substr(0, pos)).c_str());
			tempStr.erase(0, pos + delimiter.length());
			pos = tempStr.find(delimiter);
			token = tempStr.substr(0, pos);
			normal = (atoi((tempStr.substr(0, pos)).c_str())-1); 
			normales2.push_back(normal);
			tempStr.erase(0, pos + delimiter.length());
			//cout<<vertice<<"  "<<normal<<endl;
			
			//Sleep(2000);

			if(this->pieza!="reina"){
				isstream >> tempStr; // f4
				pos = 0;
				tempStr+="/";
				pos = tempStr.find(delimiter);
				vertice = (atoi((tempStr.substr(0, pos)).c_str())-1); 
				cuadrados[contCuadrados++]=vertice;
				//cout<<vertice<<endl;
				tempStr.erase(0, pos + delimiter.length());
				pos = tempStr.find(delimiter);
				token = tempStr.substr(0, pos);
				textura = atoi((tempStr.substr(0, pos)).c_str());
				tempStr.erase(0, pos + delimiter.length());
				pos = tempStr.find(delimiter);
				token = tempStr.substr(0, pos);
				normal = (atoi((tempStr.substr(0, pos)).c_str())-1); 
				normales2.push_back(normal);
				tempStr.erase(0, pos + delimiter.length());
			}
		}
	}
	normaless = new float[nVertices];
	for(int i=0;i<nQuads;i++){
		normaless[(cuadrados[i]*3)+0]=normales[(normales2.at(i)*3)+0];
		normaless[(cuadrados[i]*3)+1]=normales[(normales2.at(i)*3)+1];
		normaless[(cuadrados[i]*3)+2]=normales[(normales2.at(i)*3)+2];
	}
	normales.clear();normales2.clear();
}



igvMallaTriangulos::~igvMallaTriangulos() {
	delete []vertices;
	delete []cuadrados;
	delete []normaless;
}


// Metodos publicos 

void igvMallaTriangulos::visualizar(void) {

	glScalef(0.08,0.08,0.08);
	glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,vertices);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT,0,normaless);
		if(this->pieza=="reina")
			glDrawElements(GL_TRIANGLES,nQuads,GL_UNSIGNED_INT,cuadrados);
		else
			glDrawElements(GL_QUADS,nQuads,GL_UNSIGNED_INT,cuadrados);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

