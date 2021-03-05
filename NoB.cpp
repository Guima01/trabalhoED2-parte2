#include <iostream>
#include "NoB.h"
#include "HashEntry.h"

using namespace std;

NoB::NoB(int tamanho, bool folha)
{
    this->folha = folha;
    this->ordem = tamanho;

    this->n = 0;

    keys = new int[ordem - 1];
    filhos = new NoB *[ordem];
}

NoB::~NoB()
{
}

int NoB::getN()
{
    return this->n;
}

void NoB::setN(int i)
{
    this->n = i;
}

bool NoB::getFolha()
{
    return this->folha;
}

int* NoB::getKeys()
{ 
    return this->keys;
}

void NoB::addFilho(NoB *filho, int i)
{
    this->filhos[i] = filho;
}

NoB** NoB::getFilhos() 
{ 
    return this->filhos;
}

void NoB::print(HashTable *registros)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->print(registros);
        cout << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->print(registros);
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

int NoB::searchPosition(int key, HashTable *registros)
{
    int i = 0;
    while ( i < getN() )
    {
        if (registros->searchFromKey(key) != -1)
        {
            if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[0])))
            {
                return i;
            }
        }
        i++;
    }
    return i;
}

int NoB::keyPivo(NoB *no, int key, HashTable *registros)
{
    if (registros->searchFromKey(key) != -1)
    {
        if (no->getN() % 2)
        {
            if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(no->getKeys()[(no->getN() / 2) - 1])))
            {
                return no->getKeys()[(no->getN() / 2) - 1];
            }
        }
        else
        {

            return no->getKeys()[(no->getN() / 2)];
        }
    }
    return key;
}

void NoB::split(int position, NoB *raiz, HashTable *registros, int *keyPivo)
{
    NoB *direita = new NoB(ordem, raiz->getFolha());
    int novasKeys[ordem];
    int k = 0, i;

    int pos = raiz->searchPosition(*keyPivo,registros);

    for ( i = 0; i < raiz->getN() ; i++)
    {
        novasKeys[i] = raiz->getKeys()[i];
    }
    novasKeys[i] = *keyPivo;

    while(i >= pos)
    {
        swap(novasKeys[i],novasKeys[pos]);
        i--;
    }

    *keyPivo = novasKeys[ordem-1];

    for (int j = (ordem / 2)+1; j < ordem - 1; j++)
    {
        direita->keys[k] = novasKeys[j];
        k++;
        direita->setN(k);
    }

    raiz->n -= k+1;


    if (!raiz->getFolha())
    {
        k = i = 0;
        for (int i = (ordem / 2)+1; i < ordem; i++)
        {
            direita->addFilho(raiz->getFilhos()[i], k);
            k++;
        }
    }

    for (int j = n; j >= position + 1; j--)
    {
        filhos[j + 1] = filhos[j];
    }

    addFilho(direita, position + 1);

    for (int j = n - 1; j >= position; j--)
    {
        keys[j + 1] = keys[j];
    }

    keys[position] = novasKeys[ordem / 2];

    n++;

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
        int position = searchPosition(key, registros);

        if (filhos[position]->getN() == ordem - 1)
        {
            split(position, filhos[position], registros, &key);
            if (!menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[i])))
            {
                position++;
            }
        }
        filhos[position]->insereFilho(key, registros);
    }
}
