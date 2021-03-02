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
    for (int i = 0; i < no->getKeys().size(); i++)
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
                    if (i == no->getKeys().size() - 1)
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
        for (int i = 0; i < raiz->getKeys().size(); i++)
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

int ArvoreB::searchPosition(NoB* raiz, int key)
{
    int i;
    for(int i=0; i < raiz->getKeys().size() ; i++)
    {
        if (registros->searchFromKey(key) != -1)
        {
            if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
            {
                return i;
            }
        }
    }
    return i+1;
}

int ArvoreB::keyPivo(NoB *no, int key)
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

NoB *ArvoreB::split(NoB *raiz, int pivo, int key)
{
    NoB *aux = new NoB();
    NoB *esq = new NoB();
    NoB *dir = new NoB();
    aux->addKeys(pivo);
    for (int i = 0; i < raiz->getKeys().size(); i++)
    {
        if (key == pivo)
        {
            if (menorElemento(registros->getRegistroFromTable(pivo), registros->getRegistroFromTable(raiz->getKeys()[i])))
            {
                dir->addKeys(raiz->getKeys()[i]);
                dir->addFilho(raiz->getFilhos()[i], i);
            }
            else
            {
                esq->addKeys(raiz->getKeys()[i]);
                esq->addFilho(raiz->getFilhos()[i], i);
            }
        }
        else if (raiz->getKeys()[i] != pivo)
        {
            if (menorElemento(registros->getRegistroFromTable(pivo), registros->getRegistroFromTable(raiz->getKeys()[i])))
            {
                dir->addKeys(raiz->getKeys()[i]);
                dir->addFilho(raiz->getFilhos()[i], i);
            }
            else
            {
                esq->addKeys(raiz->getKeys()[i]);
                esq->addFilho(raiz->getFilhos()[i], i);
            }
        }
    }

    if (key != pivo)
    {
        if (menorElemento(registros->getRegistroFromTable(pivo), registros->getRegistroFromTable(key)))
        {
            insere(dir, key, dir->getFolha());
        }
        else
        {
            insere(esq, key, esq->getFolha());
        }
    }
    aux->addFilho(esq, 0);
    aux->addFilho(dir, 1);
    aux->setFolha();

    if (raiz->getKeys()[0] == this->raiz->getKeys()[0])
    {
        this->raiz = aux;
    }


    return aux;
}

bool ArvoreB::insere(NoB *raiz, int key, bool ehFolha)
{
    if ( ehFolha || raiz->getFolha())
    {
        if (raiz->getN() == ordem - 1)
        {
            raiz = split(raiz, keyPivo(raiz, key), key);
            return true;
        }
        else
        {
            raiz->addKeys(key);

            for (int i = 0, j = raiz->getN(); i < raiz->getN(); i++)
            {
                if (!menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
                {
                    while (j > i + 1)
                    {
                        swap(raiz->getKeys()[j], raiz->getKeys()[j]);
                        if (!raiz->getFolha())
                        {
                            raiz->addFilho(raiz->getFilhos()[j - 1], j);
                        }
                        j--;
                    }
                    j = raiz->getN();
                }
            }
            return false;
        }
    }
    else
    {

        int position = searchPosition(raiz,key);
        cout << position << endl;
        if( insere(raiz->getFilhos()[position], key, raiz->getFilhos()[position]->getFolha()) )
        {
            while(insere(raiz,raiz->getFilhos()[position]->getKeys()[0],true));
        }
    }
    return false;
}

void ArvoreB::imprimeArvore(NoB *raiz)
{
    if (raiz->getKeys().size())
    {
        if (raiz->getFolha())
        {
            for (int i = 0; i < raiz->getKeys().size(); i++)
            {
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getCode() << " ";
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getDate() << endl;
            }
        }
        else
        {
            for (int i = 0; i < raiz->getKeys().size(); i++)
            {
                if (raiz->getFilhos()[i] != nullptr)
                    imprimeArvore(raiz->getFilhos()[i]);
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getCode() << " ";
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getDate() << endl;
                if (raiz->getFilhos()[i + 1] != nullptr)
                    imprimeArvore(raiz->getFilhos()[i + 1]);
            }
        }
    }
}
