#include <string>
#include <iostream>
#include "NoAVL.h"

NoAVL::NoAVL()
{
}

NoAVL::~NoAVL()
{
}

void NoAVL::setEsq(NoAVL *p)
{
    this->esq = p;
}

void NoAVL::setValor(int val)
{
    this->valor = val;
}

void NoAVL::setAltura(int val)
{
    this->altura = val;
}


void NoAVL::setDir(NoAVL *p)
{   
    this->dir = p;
}
NoAVL* NoAVL::getEsq()
{
    return this->esq;
}

int NoAVL::getValor()
{
    return this->valor;
}

NoAVL* NoAVL::getDir()
{
    return this->dir;
}

int NoAVL::getAltura()
{
    return this->altura;
}