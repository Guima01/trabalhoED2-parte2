#include <iostream>
#include <fstream>
#include "NoB.h"
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

//Retorna true se candidatoInicio seja um elemento anterior ao candidatoFim apos ordena
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

//Verifica a posicao de insercao
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

void NoB::insertFilho(int key, HashTable *registros)
{
    // Começa pelo ultimo elemento
    int position = this->getN() - 1;

    if (this->getFolha())
    {
        //Percorrer o no e reeordenar as chaves até encontrar a posição de insercao
        while (position >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(this->getKeys()[position])))
        {
            this->setKeys(this->getKeys()[position], position + 1);
            position--;
        }

        this->setKeys(key, position + 1);
        this->setN(this->getN() + 1);
    }
    else
    {
        //Encontre a posição de inserção
        while (position >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(this->getKeys()[position])))
        {
            position--;
        }
        // Se o filho estiver cheio realizar a cisao
        if (this->getFilhos()[position + 1]->getN() == 2 * this->getOrdem() - 1)
        {
            split(position + 1, this->getFilhos()[position + 1], registros);

            //Verifica a posição correta de inserçao
            if (!menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(keys[position + 1])))
            {
                position++;
            }
        }
        // Insere no filho
        this->getFilhos()[position + 1]->insertFilho(key, registros);
    }
}

void NoB::split(int position, NoB *raiz, HashTable *registros)
{
    NoB *direita = new NoB(raiz->getOrdem(), raiz->getFolha());

    int elementsDireita = 0;

    // Aloca a 2º metade das chaves da raiz
    // Define aumento de chaves do novo nó

    while (elementsDireita < raiz->getOrdem() - 1)
    {
        direita->setKeys(raiz->getKeys()[elementsDireita + raiz->getOrdem()], elementsDireita);
        elementsDireita++;
        direita->setN(elementsDireita);
    }

    // Cisao na raiz, agora ela tera metade de suas chaves
    raiz->setN(elementsDireita);

    // Se a raiz não é folha, entao raiz tem filhos, alocar a 2º metade de filhos de raiz no novo nó
    if (!raiz->getFolha())
    {
        for (int i = 0; i <= raiz->getOrdem(); i++)
        {
            direita->setFilhos(raiz->getFilhos()[i + raiz->getOrdem()], i);
        }
    }

    // Mover os nós filhos para poder alocar o novo nó
    for (int j = raiz->getN(); j >= position + 1; j--)
    {
        this->setFilhos(this->getFilhos()[j], j + 1);
    }

    this->setFilhos(direita, position + 1);

    // Mover as chaves até a posicao de insercao
    for (int j = raiz->getN() - 1; j >= position; j--)
    {
        this->setKeys(this->getKeys()[j], j + 1);
    }

    // Alocar o elemento mediano da raiz
    this->setKeys(raiz->getKeys()[raiz->getOrdem() - 1], position);
    this->setN(this->getN() + 1);
}
