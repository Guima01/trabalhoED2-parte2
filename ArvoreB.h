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

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    void insereFilho(int key);

    NoB* getRaiz();
    bool aqueleAux(NoB*raiz, int key);
    bool busca(int key);
    bool auxBusca(NoB* no, int key);
    int searchPosition(NoB* raiz, int key);
    
    void insere(int key);


    
    NoB* split(NoB* raiz, int pivo, int key);
    
    int keyPivo(NoB *no , int key);
    void imprimeArvore(NoB *raiz);



};