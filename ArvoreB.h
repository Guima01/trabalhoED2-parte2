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

    void calculaTotalCasosCidade(NoB* no, string code, int &comparacoes, int &totalCasos);

    void insereNo(NoB* raiz, int key, int &comparacoes);
    void cisaoFilho(NoB* raiz, int position, int &comparacoes);
    void insere(int key, int &comparacoes);




};