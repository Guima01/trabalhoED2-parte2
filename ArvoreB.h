#include <iostream>
#include <vector>
#include "HashTable.h"
#include "NoB.h"

using namespace std;

class ArvoreB
{
    private:
    int ordem;
    NoB* raiz = NULL;
    HashTable *registros ;
    
    public:
    ArvoreB(int ordem, HashTable *tabela);
    ~ArvoreB();

    int getOrdem();
    
    NoB* getRaiz();

    HashTable* getHashTable();

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    bool auxSearch(NoB* no, int key);
    bool search(int key);

    void insert(int key);



};