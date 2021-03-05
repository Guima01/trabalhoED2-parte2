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

    int* getKeys();
    void addFilho(NoB* filho, int i);
    
    NoB** getFilhos();

    void print(HashTable *registros);

    int searchPosition(int key,HashTable *tabela);

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    int keyPivo(NoB *no, int key,HashTable *registros);

    void split(int key,NoB* raiz, HashTable *tabela,int *keyPivo);

    void insereFilho(int key, HashTable *tabela);

};