/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vertice.cpp
 * Author: Xenahort
 * 
 * Created on 25 de noviembre de 2016, 17:04
 */

#include "Vertice.h"

Vertice::Vertice() {
}

Vertice::Vertice(float xx,float yy,float zz) {
    this->x=xx;
    this->y=yy;
    this->z=zz;
}

Vertice::Vertice(const Vertice& orig) {
    this->x=orig.x;
    this->y=orig.y;
    this->z=orig.z;
}

Vertice::~Vertice() {
}

void Vertice::SetZ(float z) {
    this->z = z;
}

float Vertice::GetZ() const {
    return z;
}

void Vertice::SetY(float y) {
    this->y = y;
}

float Vertice::GetY() const {
    return y;
}

void Vertice::SetX(float x) {
    this->x = x;
}

float Vertice::GetX() const {
    return x;
}

