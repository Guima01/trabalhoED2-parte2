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

void ArvoreB::auxInsere(NoB *raiz, int key, int keyz)
{
    NoB *aux = new NoB();
    NoB *esq = new NoB();
    NoB *dir = new NoB();
    aux->addKeys(key);
    for (int i = 0; i < raiz->getKeys().size(); i++)
    {
        if (keyz == key)
        {
            if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
            {
                dir->addKeys(raiz->getKeys()[i]);
            }
            else
            {
                esq->addKeys(raiz->getKeys()[i]);
            }
        }
        else if (raiz->getKeys()[i] != key)
        {
            if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
            {
                dir->addKeys(raiz->getKeys()[i]);
            }
            else
            {
                esq->addKeys(raiz->getKeys()[i]);
            }
        }
    }
    if (keyz != key)
    {
        esq->addKeys(key);
    }

    aux->addFilho(esq);
    aux->addFilho(dir);

    aux->setFolha();
    *raiz = *aux;
}

void ArvoreB::insere(NoB *raiz, int key)
{
    if (raiz->getFolha())
    {
        if (raiz->getN())
        {
            if (raiz->getN() == ordem - 1)
            {
                if (raiz->getN() % 2)
                {
                    if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[(raiz->getN() / 2) - 1])))
                    {
                        auxInsere(raiz, raiz->getKeys()[(raiz->getN() / 2) - 1], key);
                    }
                    else
                    {
                        auxInsere(raiz, key, key);
                    }
                }
                else
                {
                    if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[(raiz->getN() / 2)])))
                    {
                        auxInsere(raiz, raiz->getKeys()[(raiz->getN() / 2)], key);
                    }
                    else
                    {
                        auxInsere(raiz, key, key);
                    }
                }
            }
            else
            {
                raiz->addKeys(key);

                for (int i = 0; i < raiz->getN(); i++)
                {
                    if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
                    {
                        swap(raiz->getKeys()[raiz->getKeys().size() - 1], raiz->getKeys()[i]);
                    }
                }
            }
        }
        else
        {
            raiz->addKeys(key);
        }
    }
    else
    for (int i = 0; i < raiz->getKeys().size(); i++)
    {
        if (menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[i])))
        {
            insere(raiz->getFilhos()[i], key);
        }
        else if (i == raiz->getKeys().size() - 1)
        {
            insere(raiz->getFilhos()[i + 1], key);
        }
    }
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
                imprimeArvore(raiz->getFilhos()[i]);
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getCode() << " ";
                cout << registros->getRegistroFromTable(raiz->getKeys()[i])->getDate() << endl;
                imprimeArvore(raiz->getFilhos()[i + 1]);
            }
        }
    }
}