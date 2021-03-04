#ifndef ARVBINBUSCA_H_INCLUDED
#define ARVBINBUSCA_H_INCLUDED
#include "NoAVL.h"

class AVLtree
{
public:
    AVLtree();
    ~AVLtree();
    bool vazia(); // verifica se a �rvore est� vazia
    NoAVL* busca(int val);
    void insere(int val);
    void remove(int val);
    void imprime();
    int altura (NoAVL* raiz);

private:
    NoAVL* raiz; // ponteiro para o No raiz da �rvore
    NoAVL* auxBusca(NoAVL *p, int val);
    NoAVL* auxInsere(NoAVL *p, int val);
    NoAVL* auxRemove(NoAVL *p, int val);
    NoAVL* menorSubArvDireita(NoAVL *p);
    NoAVL* removeFolha(NoAVL *p);
    NoAVL* remove1Filho(NoAVL *p);
    void imprimePorNivel(NoAVL* p, int nivel);
    NoAVL* libera(NoAVL *p);

    void rebalanceamentoUp(NoAVL* no);
    void rebalancear(NoAVL* no);
    int calculaFB(NoAVL* no);
    NoAVL* rotacaoEsquerda(NoAVL* no);
    NoAVL* rotacaoDireita(NoAVL* no);
    bool verificaDesbalanceamento(NoAVL *raiz);
};

#endif // ARVBINBUSCA_H_INCLUDED
