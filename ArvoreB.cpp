#include <iostream>
#include <algorithm>
#include <fstream>
#include "ArvoreB.h"
#include "HashTable.h"

using namespace std;

ArvoreB::ArvoreB(int ordem, HashTable *tabela)
{
    this->registros = tabela;
    this->ordem = ordem;
}

ArvoreB::~ArvoreB()
{
}

int ArvoreB::getOrdem()
{
    return this->ordem;
}

NoB *ArvoreB::getRaiz()
{
    return this->raiz;
}

HashTable *ArvoreB::getHashTable()
{
    return this->registros;
}

//Retorna true se candidatoInicio seja um elemento anterior ao candidatoFim apos ordenaçao
bool ArvoreB::menorElemento(Registro *candidatoInicio, Registro *candidatoFim)
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

//Retorna verdade caso seja encontrado a chave
bool ArvoreB::auxSearch(NoB *no, int key)
{
    for (int i = 0; i < no->getN(); i++)
    {
        if (no->getKeys()[i] == key)
        {
            return true;
        }
        else
        {
            // Se a key existir na tabela hash
            if (this->getHashTable()->searchFromKey(key) != -1)
            {
                if (menorElemento(this->getHashTable()->getRegistroFromTable(key), this->getHashTable()->getRegistroFromTable(no->getKeys()[i])))
                {
                    if (!no->getFolha())
                        return auxSearch(no->getFilhos()[i], key);
                }
                else
                {
                    if (i == no->getN() - 1)
                    {
                        if (!no->getFolha())
                            return auxSearch(no->getFilhos()[i + 1], key);
                    }
                }
            }
        }
    }
    return false;
}

bool ArvoreB::search(int key)
{
    if (this->getRaiz()->getFolha())
    {
        for (int i = 0; i < this->getRaiz()->getN(); i++)
        {
            if (this->getRaiz()->getKeys()[i] == key)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return auxSearch(this->getRaiz(), key);
    }
}

void ArvoreB::splitChildren(NoB *raiz, int position)
{
    NoB *filhoRaiz = raiz->getFilhos()[position];

    NoB *novoNo = new NoB(raiz->getOrdem(), filhoRaiz->getFolha());

    for( int j = 0; j < getOrdem()-1 ; j++)
    {
        novoNo->setKeys(filhoRaiz->getKeys()[ j + getOrdem() ], j );
    }

    if( ! filhoRaiz->getFolha() )
    {
        for( int j = 0 ; j < getOrdem() ; j++)
        {
            novoNo->setFilhos(filhoRaiz->getFilhos()[ j + getOrdem() ], j );
        }
    }

    novoNo->setN(getOrdem()-1);

    filhoRaiz->setN(getOrdem()-1);
    
    insertNo(raiz,filhoRaiz->getKeys()[getOrdem()-1]);

    raiz->setFilhos( novoNo, position+1 );

}

void ArvoreB::insertNo(NoB *raiz, int key)
{
    int position = raiz->getN();
    while( position > 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[position-1])) )
    {
        raiz->setKeys(raiz->getKeys()[ position - 1 ], position);
        raiz->setFilhos(raiz->getFilhos()[ position ], position+1);
        position--;
    }

    raiz->setFilhos(raiz->getFilhos()[position], position+1);
    raiz->setKeys(key,position);
    raiz->setN(raiz->getN() + 1);
}

void ArvoreB::insert(int key)
{
    if (this->raiz == NULL)
    {
        this->raiz = new NoB(this->getOrdem(), true);
        this->raiz->getKeys()[0] = key;
        this->raiz->setN(1);
    }
    else
    {
        if (this->raiz->getN() == 2 * this->getOrdem() - 1)
        {
            NoB *novaRaiz = new NoB(this->getOrdem(), false);

            novaRaiz->setFilhos(raiz, 0);

            this->raiz = novaRaiz;

            splitChildren(novaRaiz,0);
        }

        NoB *novoNo = this->raiz;

        while (!novoNo->getFolha())
        {
            int position = novoNo->getN() - 1;

            while (position >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(novoNo->getKeys()[position])))
            {
                position--;
            }

            position++;

            if (novoNo->getFilhos()[position]->getN() == 2 * novoNo->getOrdem() - 1)
            {
                splitChildren(novoNo,position);

                if (menorElemento(registros->getRegistroFromTable(novoNo->getKeys()[position]), registros->getRegistroFromTable(key)))
                {
                    position++;
                }
            }

            novoNo = novoNo->getFilhos()[position];
        }

        insertNo(novoNo,key);
    }
}
