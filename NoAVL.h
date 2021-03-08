#include <string>
#include <iostream>

class NoAVL

{
public:
    // CONSTRUTOR / DESTRUTOR
    NoAVL();
    ~NoAVL();

    // SETS
    void setEsq(NoAVL *p);
    void setDir(NoAVL *p);
    void setValor(int val);
    void setAltura(int val);

    // GETS
    int getValor();
    int getAltura();
    NoAVL *getEsq();
    NoAVL *getDir();

private:
    int altura; // ALTURA DO NÓ
    NoAVL *esq; // PONTEIRO PARA O NÓ FILHO A ESQUERDA
    int valor;  // VALOR ARMAZENADO NO NÓ
    NoAVL *dir; // PONTEIRO PARA O NÓ FILHO A DIREITA
};