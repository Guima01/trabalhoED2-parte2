#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "NoquadTree.h"

NoquadTree::NoquadTree(RegistrosCoordenados *registro)
{
    this->registroCoordenado = registro;
    this->coordX = registro->getLatitude();
    this->coordY = registro->getLongitude();
    this->pai = nullptr;
    this->ne = nullptr;
    this->nw = nullptr;
    this->se = nullptr;
    this->sw = nullptr;
}
NoquadTree::~NoquadTree() {}

RegistrosCoordenados NoquadTree::getRegistroCoordenado(){
    return *this->registroCoordenado;
}
double NoquadTree::getCoordX(){
    return this->coordX;
}
double NoquadTree::getCoordY(){
    return this->coordY;
}
NoquadTree NoquadTree::getPai(){
    return *this->pai;
}
NoquadTree *NoquadTree::getNe(){
    return this->ne;
}
NoquadTree *NoquadTree::getNw(){
    return this->nw;
}
NoquadTree *NoquadTree::getSw(){
    return this->sw;
}
NoquadTree *NoquadTree::getSe(){
    return this->se;
}

void NoquadTree::setRegistroCoordenado(RegistrosCoordenados *registro){
    this->registroCoordenado = registro;
}
void NoquadTree::setCoordX(double x){
    this->coordX = x;
}
void NoquadTree::setCoordY(double y){
    this->coordY = y;
}
void NoquadTree::setPai(NoquadTree *no){
    this->pai = no;
}
void NoquadTree::setNe(NoquadTree *no){
    this->ne = no;
}
void NoquadTree::setNw(NoquadTree *no){
    this->nw = no;
}
void NoquadTree::setSw(NoquadTree *no){
    this->sw = no;
}
void NoquadTree::setSe(NoquadTree *no){
    this->se = no;
}