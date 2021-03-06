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

int *NoB::getKeys()
{
    return this->keys;
}

void NoB::addFilho(NoB *filho, int i)
{
    this->filhos[i] = filho;
}

NoB **NoB::getFilhos()
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
    while (i < getN())
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

NoB *NoB::split(int position, NoB *raiz, HashTable *registros, int *keyPivo)
{

    NoB *direita = new NoB(ordem, raiz->getFolha());
    int novasKeys[ordem];
    int k = 0, i;
    while (k < raiz->getN())
    {
        cout << registros->getRegistroFromTable(raiz->getKeys()[k])->getCode() << " ";
        cout << registros->getRegistroFromTable(raiz->getKeys()[k])->getDate() << endl;
        k++;
    }
    cout << registros->getRegistroFromTable(*keyPivo)->getCode() << " ";
    cout << registros->getRegistroFromTable(*keyPivo)->getDate() << endl;
    int pos = raiz->searchPosition(*keyPivo, registros);

    for (i = 0; i < raiz->getN(); i++)
    {
        novasKeys[i] = raiz->getKeys()[i];
    }
    novasKeys[i] = *keyPivo;

    while (i > position)
    {
        swap(novasKeys[i], novasKeys[i - 1]);
        i--;
    }
    cout << registros->getRegistroFromTable(novasKeys[0])->getCode() << " ";
    cout << registros->getRegistroFromTable(novasKeys[0])->getDate() << endl;
    *keyPivo = novasKeys[ordem / 2];

    i = 0;
    raiz->setN(0);

    for (int j = 0; j < ordem / 2; j++)
    {
        raiz->setKeys(novasKeys[j], i);
        i++;
        raiz->setN(i);
        cout << "Raiz :" << endl;
        cout << registros->getRegistroFromTable(raiz->getKeys()[j])->getCode() << " ";
        cout << registros->getRegistroFromTable(raiz->getKeys()[j])->getDate() << endl;
    }
    k = 0;
    for (int j = (ordem / 2) + 1; j < ordem; j++)
    {
        direita->setKeys(novasKeys[j], k);
        k++;
        direita->setN(k);
        cout << "Direita : " << endl;
        cout << registros->getRegistroFromTable(novasKeys[j])->getCode() << " ";
        cout << registros->getRegistroFromTable(novasKeys[j])->getDate() << endl;
    }
    cout << "Pivo " << endl;
    cout << registros->getRegistroFromTable(*keyPivo)->getCode() << " ";
    cout << registros->getRegistroFromTable(*keyPivo)->getDate() << endl;
    cout << "Raiz getN() " << raiz->getN() << " Direita getN() " << direita->getN() << endl;
    if (!raiz->getFolha())
    {
        int y = 0;
        for (i = ordem / 2; i < ordem + 1; i++)
        {
            direita->addFilho(raiz->getFilhos()[i], y);
            y++;
        }
    }

    cout << direita->getN() << endl;
    cout << "n " << n << endl;

    cout << direita->getN() << endl;
    return direita;
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
        for (int j = n; j >= position+1; j--)
            filhos[j + 1] = filhos[j];

        for (int p = n - 1; p >= position; p--)
        {
            keys[p] = keys[p + 1];
        }
        keys[position] = key;
        n++;
    }
}
