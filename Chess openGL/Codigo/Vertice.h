/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vertice.h
 * Author: Xenahort
 *
 * Created on 25 de noviembre de 2016, 17:04
 */

#ifndef VERTICE_H
#define VERTICE_H
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Vertice {
    private:
        float x;
        float y;
        float z;
public:
    Vertice();
    Vertice(float x,float y,float z);
    Vertice(const Vertice& orig);
    virtual ~Vertice();
    void SetZ(float z);
    float GetZ() const;
    void SetY(float y);
    float GetY() const;
    void SetX(float x);
    float GetX() const;
	void pintarVertice(){
		glVertex3f(x,y,z);
	}

};

#endif /* VERTICE_H */

