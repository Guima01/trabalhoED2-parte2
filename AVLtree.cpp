#include <iostream>
#include "AVLtree.h"

using namespace std;

AVLtree::AVLtree()
{
    raiz = NULL;
}

bool AVLtree::vazia()
{
    return raiz == NULL;
}

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
    else
        p->setDir(auxInsere(p->getDir(), val));

    p->setAltura(altura(p)+1);

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

NoAVL* AVLtree::busca(int val)
{
    return auxBusca(raiz, val);
}

NoAVL* AVLtree::auxBusca(NoAVL *p, int val)
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

void AVLtree::remove(int val)
{
    raiz = auxRemove(raiz, val);
}

NoAVL *AVLtree::auxRemove(NoAVL *p, int val)
{
    if (p == NULL)
        return NULL;
    else if (val < p->getValor())
        p->setEsq(auxRemove(p->getEsq(), val));
    else if (val > p->getValor())
        p->setDir(auxRemove(p->getDir(), val));
    else
    {
        if (p->getEsq() == NULL && p->getDir() == NULL)
            p = removeFolha(p);
        else if ((p->getEsq() == NULL) || (p->getDir() == NULL))
            p = remove1Filho(p);
        else
        {
            NoAVL *aux = menorSubArvDireita(p);
            int tmp = aux->getValor();
            p->setValor(tmp);
            aux->setValor(val);
            p->setDir(auxRemove(p->getDir(), val));
        }
    }
    return p;
}

NoAVL *AVLtree::removeFolha(NoAVL *p)
{
    delete p;
    return NULL;
}

NoAVL *AVLtree::remove1Filho(NoAVL *p)
{
    NoAVL *aux;
    if (p->getEsq() == NULL)
        aux = p->getDir();
    else
        aux = p->getEsq();
    delete p;
    return aux;
}

NoAVL *AVLtree::menorSubArvDireita(NoAVL *p)
{
    NoAVL *aux = p->getDir();
    while (aux->getEsq() != NULL)
        aux = aux->getEsq();
    return aux;
}

void AVLtree::imprime()
{
    imprimePorNivel(raiz, 0);
}

void AVLtree::imprimePorNivel(NoAVL *p, int nivel)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getValor() << endl;
        imprimePorNivel(p->getEsq(), nivel + 1);
        imprimePorNivel(p->getDir(), nivel + 1);
    }
}

AVLtree::~AVLtree()
{
    raiz = libera(raiz);
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
        return -1; // altura da árvore vazia
    else
    {
        int he = altura(raiz->getEsq());
        int hd = altura(raiz->getDir());
        if (he < hd)
            return hd + 1;
        else
            return he + 1;
    }
}

void AVLtree::rebalanceamentoUp(NoAVL *no)
{
    if (no == NULL)
    {
        return;
    }
    rebalancear(no);
}

int AVLtree::calculaFB(NoAVL *no)
{
    if (no == NULL)
        return 0;
    else
        return altura(no->getDir()) - altura(no->getEsq());
}

void AVLtree::rebalancear(NoAVL *no)
{

    int fb = calculaFB(no);

    if (no == NULL)
    {
        return;
    }
    else if (fb < -1)
    {
        if (calculaFB(no->getEsq()) > 0)
        {
            no->setEsq(rotacaoEsquerda(no->getEsq()));
        }
        //no = rotacaoDireita(no);
    }
    else if (fb > 1)
    {
        if (calculaFB(no->getDir()) < 0)
        {
            no->setDir(rotacaoDireita(no->getDir()));
        }
       // no = rotacaoEsquerda(no);
    }
    else
    {
        rebalancear(no->getEsq());
        rebalancear(no->getDir());
    }
}

NoAVL* AVLtree::rotacaoEsquerda(NoAVL *no)
{
    // Q = P->dir
    NoAVL* noDir = no->getDir();
    
    NoAVL* noEsq = noDir->getEsq();

    noDir->setEsq(no);
    no->setDir(noEsq);

    no->setAltura(altura(no));
    noDir->setAltura(altura(noDir));

    return noDir;
}

NoAVL* AVLtree::rotacaoDireita(NoAVL *no)
{
    NoAVL* noEsq = no->getEsq();
    NoAVL* noDir = noEsq->getDir();

    noEsq->setDir(no);
    no->setEsq(noDir);

    no->setAltura(altura(no));
    noEsq->setAltura(altura(noEsq));

    return noEsq;
}

bool AVLtree::verificaDesbalanceamento(NoAVL *raiz)
{
    int fb = calculaFB(raiz);

    if (raiz != NULL)
    {
        if (fb > 1 || fb < -1)
            return true;
        else
        {
            verificaDesbalanceamento(raiz->getEsq());
            verificaDesbalanceamento(raiz->getDir());
            return false;
        }
    }
}