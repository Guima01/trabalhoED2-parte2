#include <iostream>
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

    NoB* getRaiz();

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    bool auxSearch(NoB* no, int key);
    bool search(int key);
    
    void insere(int key);


};
