#include <iostream>
#include <vector>
#include "NoB.h"
#include "HashEntry.h"


using namespace std;

NoB::NoB()
{
    this->folha = true;
    this->n = 0;

    for(int i=0 ; i < 5 ; i++)
    {
        this->filhos.push_back(nullptr);
    }
}

NoB::~NoB()
{
    
}

void NoB::setN()
{
    this->n++;
}

void NoB::setFolha()
{
    this->folha = false;
}

int NoB::getN()
{
    return this->n;
}

bool NoB::getFolha()
{
    return this->folha;
}

vector<int> NoB::getKeys()
{
    return this->keys;
}

vector<NoB*> NoB::getFilhos()
{
    return this->filhos;
}

void NoB::addKeys(int key)
{
    this->keys.push_back(key);
    this->n++;
}

void NoB::addFilho(NoB *filho, int i)
{

    this->filhos[i] = filho;
}