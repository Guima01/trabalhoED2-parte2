#include <iostream>
#include <fstream>
#include <string>
#include "AVLtree.h"
#include "HashTable.h"

using namespace std;

// CONSTRUTOR / DESTRUTOR
AVLtree::AVLtree()
{
    raiz = NULL;
}

AVLtree::~AVLtree()
{
    raiz = libera(raiz);
}

// DEMAIS FUNÇÕES
bool AVLtree::vazia()
{
    return raiz == NULL;
}

NoAVL *AVLtree::libera(NoAVL *p)
{
    if (p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}

int AVLtree::altura(NoAVL *raiz)
{
    if (raiz == NULL) 
        return 0; 
    return raiz->getAltura();
}

int AVLtree::retornaMaior(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

// INSERÇÃO
void AVLtree::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

NoAVL *AVLtree::auxInsere(NoAVL *p, int val)
{
    if (p == NULL)
    {
        p = new NoAVL();
        p->setValor(val);
        p->setEsq(NULL);
        p->setDir(NULL);
        p->setAltura(1);
    }
    else if (val < p->getValor())
        p->setEsq(auxInsere(p->getEsq(), val));
    else if (val > p->getValor())
        p->setDir(auxInsere(p->getDir(), val));
    else
        return p;

    p->setAltura(1 + retornaMaior(altura(p->getEsq()), altura(p->getDir())));

    int fb = calculaFB(p);

    // Rotação dupla a Esquerda
    if (fb == 2 && calculaFB(p->getDir()) == -1)
    {
        p->setDir(rotacaoDireita(p->getDir()));
        return rotacaoEsquerda(p);
    }

    // Rotação dupla a direita
    if (fb == -2 && calculaFB(p->getEsq()) == 1)
    {
        p->setEsq(rotacaoEsquerda(p->getEsq()));
        return rotacaoDireita(p);
    }

    // Rotação a Esquerda
    if (fb == 2 && (calculaFB(p->getDir()) == 1 || calculaFB(p->getDir()) == 0))
        return rotacaoEsquerda(p);

    // Rotação a Direita
    if (fb == -2 && (calculaFB(p->getEsq()) == -1 || calculaFB(p->getEsq()) == 0))
        return rotacaoDireita(p);

    return p;
}

// BUSCA
NoAVL *AVLtree::busca(int val)
{
    return auxBusca(raiz, val);
}

NoAVL *AVLtree::auxBusca(NoAVL *p, int val)
{
    if (p == NULL)
        return new NoAVL();
    else if (p->getValor() == val)
        return p;
    else if (val < p->getValor())
        return auxBusca(p->getEsq(), val);
    else
        return auxBusca(p->getDir(), val);
}

// IMPRESSÃO NO TERMINAL
void AVLtree::imprime(HashTable *registros)
{
    imprimePorNivel(raiz, 0, registros);
}

void AVLtree::imprimePorNivel(NoAVL *p, int nivel, HashTable *registros)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << registros->getRegistroFromTable(p->getValor())->getCode() << " ";
        cout << registros->getRegistroFromTable(p->getValor())->getDate() << endl;
        imprimePorNivel(p->getEsq(), nivel + 1, registros);
        imprimePorNivel(p->getDir(), nivel + 1, registros);
    }
}

// IMPRESSÃO DA ÁRVORE EM ARQUIVO
void AVLtree::saidaArqv(ofstream &saida, HashTable *registros)
{
    auxSaidaArqv(raiz, 0, saida, registros);
}

void AVLtree::auxSaidaArqv(NoAVL *p, int nivel, ofstream &saida, HashTable *registros)
{
    if (p != NULL)
    {
        saida << "( Nivel : ";
        saida << to_string(nivel);
        saida << " ) ";

        for (int i = 1; i <= nivel; i++)
            saida << "--";
        
        saida << registros->getRegistroFromTable(p->getValor())->getCode();
        saida << " ";
        saida << registros->getRegistroFromTable(p->getValor())->getDate();
        saida << endl;
        auxSaidaArqv(p->getEsq(), nivel + 1, saida, registros);
        auxSaidaArqv(p->getDir(), nivel + 1, saida, registros);
    }
}

// CALCULA O FATOR DE BALANCEAMENTO
int AVLtree::calculaFB(NoAVL *no)
{
    if (no == NULL)
        return 0;
    else
        return altura(no->getDir()) - altura(no->getEsq());
}

//ROTAÇÕES
NoAVL *AVLtree::rotacaoEsquerda(NoAVL *no)
{
    // Q = P->dir
    NoAVL *noDir = no->getDir();

    NoAVL *noEsq = noDir->getEsq();

    noDir->setEsq(no);
    no->setDir(noEsq);

    no->setAltura((retornaMaior(altura(no->getEsq()), altura(no->getDir())) + 1));
    noDir->setAltura((retornaMaior(altura(noDir->getEsq()), altura(noDir->getDir())) + 1));

    return noDir;
}

NoAVL *AVLtree::rotacaoDireita(NoAVL *no)
{
    NoAVL *noEsq = no->getEsq();
    NoAVL *noDir = noEsq->getDir();

    noEsq->setDir(no);
    no->setEsq(noDir);

    no->setAltura((retornaMaior(altura(no->getEsq()), altura(no->getDir())) + 1));
    noEsq->setAltura((retornaMaior(altura(noEsq->getEsq()), altura(noEsq->getDir())) + 1));

    return noEsq;
}