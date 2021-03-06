#include <iostream>
#include "HashTable.h"

using namespace std;

class NoB
{
    private:
    int* keys;
    NoB** filhos;
    bool folha;
    int ordem;
    int n;

    public:
    NoB(int tamanho, bool folha);
    ~NoB();

    int getN();
    void setN(int i);

    bool getFolha();
    void setFolha(bool trueOrfalse) {   folha = trueOrfalse;}

    int* getKeys();
    void setKeys(int key, int pos) { keys[pos] = key;}
    void addFilho(NoB* filho, int i);

    NoB* encontraNoFolha(NoB* raiz,int key,HashTable *registros);
    
    NoB** getFilhos();

    void print(HashTable *registros);

    int searchPosition(int key,HashTable *tabela);

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    int keyPivo(NoB *no, int key,HashTable *registros);

    NoB* split(int position,NoB* raiz, HashTable *tabela,int *keyPivo);

    void insereFilho(int key, HashTable *tabela);

};