#include <iostream>
#include <vector>
#include "NoB.h"
#include "HashEntry.h"

using namespace std;

NoB::NoB(int tamanho, bool folha)
{
    this->folha = folha;
    this->ordem = tamanho;

    this->n = 0;

    keys = new int[2 * ordem - 1];
    filhos = new NoB *[2 * ordem];
}

NoB::~NoB()
{
}

void NoB::setN(int i)
{
    this->n = i;
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


void NoB::imprime(HashTable *registros)
{

    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->imprime(registros);
        cout << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->imprime(registros);
}

void NoB::addFilho(NoB *filho, int i)
{
    this->filhos[i] = filho;
}

void NoB::split(int i, NoB *raiz, HashTable *registros)
{
    NoB *aux = new NoB(ordem, raiz->getFolha());
    aux->n = ordem - 1;

    int k;

    for (int j = 0; j < ordem - 1; j++)
    {
        aux->keys[j] = raiz->keys[j + ordem];

    }
    if (!raiz->getFolha())
    {
        for (int i = 0; i < ordem; i++)
        {
            aux->addFilho(raiz->getFilhos()[i + ordem], i);
        }
    }

    raiz->n = ordem - 1;

    for (int j = n; j >= i + 1; j--)
    {
        filhos[j + 1] = filhos[j];
    }

    addFilho(aux, i + 1);


    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];

    }
    keys[i] = raiz->keys[ordem - 1];

    n++;
}

bool NoB::menorElemento(Registro *candidatoInicio, Registro *candidatoFim)
{
    bool verificaCode = (candidatoInicio->getCode() == candidatoFim->getCode());
    if (candidatoInicio->getCode() < candidatoFim->getCode() || verificaCode)
    {
        if (verificaCode)
        {
            if (candidatoInicio->getDate() < candidatoFim->getDate())
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void NoB::insereFilho(int key, HashTable *registros)
{
    int i = n - 1;
    if (folha)
    {
        while (i >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[i])))
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        n++;
    }
    else
    {
        while (i >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[i])))
        {
            i--;
        }
        if (filhos[i + 1]->getN() == ordem - 1)
        {
            split(i + 1, filhos[i + 1], registros);
            if (!menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[i + 1])))
            {
                i++;
            }
        }
        filhos[i + 1]->insereFilho(key, registros);
    }
}