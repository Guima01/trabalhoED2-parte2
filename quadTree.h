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
    NoquadTree getRaiz();
    void insert(NoquadTree *no);
    NoquadTree compara(NoquadTree *r, NoquadTree *p);
};