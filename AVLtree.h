#include <fstream>
#include "NoAVL.h"
#include "HashTable.h"

using namespace std;

class AVLtree
{
public:
    
    AVLtree(HashTable *tabela);  // CONSTRUTOR
    ~AVLtree(); // DESTRUTOR

    bool vazia(); // VERIFICA SE A ÁRVORE ESTÁ VAZIA

    NoAVL* busca(int val); // BUSCA

    void insere(int val, int &comparacoes); // INSERÇÃO

    void imprime(HashTable *registros); // IMPRESSÃO NO TERMINAL

    void saidaArqv(ofstream &saida, HashTable *registros); // IMPRESSÃO POR ARQUIVO

    int altura (NoAVL* raiz); // CALCULA A ALTURA DE UM NÓ

    bool menorElemento(Registro *candidatoInicio, Registro *candidatoFim);

    int retornaMaior(int a, int b);

private:
    NoAVL* raiz; // PONTEIRO PARA A RAIZ DA ÁRVORE
    HashTable *registros;

    // FUNÇÕES AUX
    NoAVL* auxBusca(NoAVL *p, int val); // BUSCA
    NoAVL* auxInsere(NoAVL *p, int val, int &comparacoes); // INSERÇÃO
    void auxSaidaArqv(NoAVL *p, int nivel, ofstream &saida, HashTable *registros); // IMPRESSÃO POR ARQUIVO
    
    void imprimePorNivel(NoAVL* p, int nivel, HashTable *registros); // IMPRESSÃO NO TERMINAL
    
    NoAVL* libera(NoAVL *p); // AUXILIAR DO DESTRUTOR

    int calculaFB(NoAVL* no);
    // ROTAÇÕES
    NoAVL* rotacaoEsquerda(NoAVL* no);
    NoAVL* rotacaoDireita(NoAVL* no);
};
