#include <string>
#include <iostream>

class NoAVL

{
public:
    NoAVL();
    ~NoAVL();

    void setEsq(NoAVL *p);
    void setDir(NoAVL *p);
    void setValor(int val);
    void setAltura(int val);

    int getValor();
    int getAltura();
    NoAVL *getEsq();
    NoAVL *getDir();

private:
    int altura;
    NoAVL *esq; // ponteiro para o filho a esquerda
    int valor;
    NoAVL *dir;
};