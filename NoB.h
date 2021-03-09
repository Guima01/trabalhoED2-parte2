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

    void salvaArquivo(HashTable *registros,int nivel, ofstream &saida);
    
    void print(HashTable *registros,int nivel);
    



    
};