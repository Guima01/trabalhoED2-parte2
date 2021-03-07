#include <iostream>
#include <vector>
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

    int getOrdem();

    int getN();
    void setN(int i);

    bool getFolha();
    void setFolha(bool trueOrfalse);

    void setKeys(int key, int position);
    int* getKeys();

    NoB** getFilhos();
    void setFilhos(NoB* filho, int i);

    void print(HashTable *registros,int nivel);
    
    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    int searchPosition(int key,HashTable *tabela);

    void insertFilho(int key, HashTable *tabela);

    void split(int position,NoB* raiz, HashTable *tabela);



    
};