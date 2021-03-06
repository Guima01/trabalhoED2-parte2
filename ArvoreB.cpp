#include <iostream>
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
            if (registros->searchFromKey(key) != -1)
            {
                if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(no->getKeys()[i])))
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
        return auxSearch(raiz, key);
    }
}

int ArvoreB::insere(int key, NoB *folha, NoB *noPromovido)
{

    if (this->raiz == NULL)
    {
        this->raiz = new NoB(ordem, true);
        this->raiz->getKeys()[0] = key;
        this->raiz->setN(1);
    }
    else
    {

        // descer até a folha
        //identifiquei a folha , eu insiro e entro no if abaixo
        // verificar para cada nó se ele esta cheio
        // só criar nó quando estiver na raiz;

        // aux insere retorna no
        // arvb ed1

        // tenta inserir
        // verificar se era raiz
        // se era preciso criar raiz, caso contrario split
        // criar função para verificar

        if (folha->getFolha())
        {
            if (folha->getN() == ordem - 1)
            {
                if (folha == this->raiz)
                {
                    NoB *aux = new NoB(ordem, false);
                    aux->addFilho(folha, 0);
                    aux->split(0, folha, registros, &key);
                    aux->insereFilho(key, registros);
                    this->raiz = aux;
                }
                else
                {
                    noPromovido->split(0, folha, registros, &key);
                    cout << "G "<< noPromovido->getN() << endl;
                    return key;
                }
            }
            else
            {
                folha->insereFilho(key, registros);
            }
            return 0;
        }
        else
        {
            int position = folha->searchPosition(key, registros); // 0
            NoB* promoted = new NoB(ordem,folha->getFolha());
            promoted->setN(folha->getN());
            key = insere(key, folha->getFilhos()[position], promoted);      //


            if (key)
            {
                cout << "G "<< promoted->getN() << endl;
                if (folha->getN() == ordem - 1)
                {
                    noPromovido = folha->split(position, folha, registros, &key);
                    
                    return key;
                }
                else
                {
                    cout << "aq " << endl;
                    folha->addFilho(promoted,position+1);
                    folha->insereFilho(key,registros);
                }
            }
        }
    }
    return 0;
}
