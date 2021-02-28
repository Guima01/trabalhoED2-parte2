#include <iostream>
#include <vector>
#include "HashTable.h"
#include "NoB.h"

using namespace std;

class ArvoreB
{
    private:
    int ordem;
    NoB* raiz = new NoB();
    HashTable *registros ;
    

    public:
    ArvoreB(int ordem, HashTable *tabela);
    ~ArvoreB();

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    NoB* getRaiz();

    bool busca(int key);
    bool auxBusca(NoB* no, int key);

    void insere(NoB* raiz, int key);
    void auxInsere(NoB* raiz, int key, int keyz);

    void imprimeArvore(NoB *raiz);



};