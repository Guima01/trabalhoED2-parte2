#include <string>
#include "NoquadTree.h"

using namespace std;

class QuadTree
{

private:
    NoquadTree *raiz;

public:
    QuadTree();
    ~QuadTree();
    NoquadTree* getRaiz();
    void insert(NoquadTree *no);
    void busca (double latitude, double longitude);
    NoquadTree compara(NoquadTree *r, NoquadTree *p);
    void imprimePorNivel(NoquadTree *p, int nivel);
    void ImprimeArquivoTexto(NoquadTree *p, int nivel, ofstream &arq);
};