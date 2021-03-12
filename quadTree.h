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
    void imprimePorNivel(NoquadTree *p, int nivel);
    void ImprimeArquivoTexto(NoquadTree *p, int nivel, ofstream &arq);
    void retornaRegistrosNasCoordenadas(vector<RegistrosCoordenados> &vet, NoquadTree *p, double latitude1, double longitude1, double latitude2, double longitude2);
};