#include "NoB.h"
#include <fstream>
#include "HashEntry.h"

using namespace std;

NoB::NoB(int tamanho, bool folha)
{
    this->folha = folha;
    this->ordem = tamanho;

    this->n = 0;

    this->keys = new int[2 * ordem - 1];
    this->filhos = new NoB *[2 * ordem];
}

NoB::~NoB()
{
}

int NoB::getOrdem()
{
    return this->ordem;
}

void NoB::setN(int i)
{
    this->n = i;
}

int NoB::getN()
{
    return this->n;
}

bool NoB::getFolha()
{
    return this->folha;
}

void NoB::setFolha(bool trueOrfalse)
{
    this->folha = trueOrfalse;
}

int *NoB::getKeys()
{
    return this->keys;
}

void NoB::setKeys(int key, int position)
{
    this->keys[position] = key;
}

NoB **NoB::getFilhos()
{
    return this->filhos;
}

void NoB::setFilhos(NoB *filho, int i)
{
    this->filhos[i] = filho;
}

void NoB::salvaArquivo(HashTable *registros, int nivel, ofstream &saida)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->salvaArquivo(registros, nivel + 1,saida);

       saida << "( Nivel : " ;
       saida << nivel;
       saida << " ) ";
       saida << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
       saida << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->salvaArquivo(registros, nivel + 1,saida);
}

void NoB::print(HashTable *registros, int nivel)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->print(registros, nivel + 1);
        cout << "( Nivel : " << nivel << " ) ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->print(registros, nivel + 1);
}
