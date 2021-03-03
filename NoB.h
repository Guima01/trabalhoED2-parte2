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
    int * getKeys() { return this->keys;}
    void reduzN() {       this->n--;}
    void addFilho(NoB* filho, int i);
    void addKeys(int key);
    void setN(int i);
    void setFolha();
    void setChave(int i,int ch){keys[i]=ch;};
    int getN();
    //vector<int> getKeys();
    void imprime(HashTable *registros);
    
    NoB** getFilhos() { return this->filhos;}
    bool getFolha();

    void split(int key,NoB* raiz, HashTable *tabela);
    int searchPosition(int key,HashTable *tabela);
    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);
    void insereFilho(int key, HashTable *tabela);





    
};

