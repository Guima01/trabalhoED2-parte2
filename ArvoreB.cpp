#include <iostream>
#include <vector>
#include <algorithm>
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

NoB *ArvoreB::getRaiz()
{
    return this->raiz;
}

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

bool ArvoreB::auxBusca(NoB *no, int key)
{
    for (int i = 0; i < no->getN(); i++)
    {
        if (no->getKeys()[i] == key)
        {
            return true;
        }
        else
        {
            if (registros->searchFromKey(key) != -1)
            {
                if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(no->getKeys()[i])))
                {
                    if (!no->getFolha())
                        return auxBusca(no->getFilhos()[i], key);
                }
                else
                {
                    if (i == no->getN() - 1)
                    {
                        if (!no->getFolha())
                            return auxBusca(no->getFilhos()[i + 1], key);
                    }
                }
            }
        }
    }
    return false;
}

bool ArvoreB::busca(int key)
{
    if (raiz->getFolha())
    {
        for (int i = 0; i < raiz->getN(); i++)
        {
            if (raiz->getKeys()[i] == key)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return auxBusca(raiz, key);
    }
}

void ArvoreB::insere(int key)
{
    if (this->raiz == NULL)
    {
        this->raiz = new NoB(ordem,true);
        this->raiz->getKeys()[0] = key;
        this->raiz->setN(1);
    }
    else
    {
        if (raiz->getN() == 2*ordem - 1 )
        {
            NoB* aux = new NoB(ordem,false);

            aux->addFilho(raiz,0);
            aux->split(0,raiz,registros);
            int i = 0;

            if(menorElemento(registros->getRegistroFromTable(aux->getKeys()[i]),registros->getRegistroFromTable(key))){
                i++; 
            }
            aux->getFilhos()[i]->insereFilho(key,registros);
            this->raiz = aux;
            //aux->insereFilho(aux->getFilhos()[position],key);
            
        }
        else
        {
            raiz->insereFilho(key,registros);
        }
    }
}