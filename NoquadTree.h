#include <string>
#include "RegistrosCoordenados.h"

using namespace std;

class NoquadTree
{

private:
    RegistrosCoordenados *registroCoordenado;
    double coordX;
    double coordY;
    NoquadTree *pai;
    NoquadTree *ne;
    NoquadTree *nw;
    NoquadTree *sw;
    NoquadTree *se;

public:
    NoquadTree(RegistrosCoordenados *registro);
    ~NoquadTree();
    RegistrosCoordenados getRegistroCoordenado();
    double getCoordX();
    double getCoordY();
    NoquadTree getPai();
    NoquadTree *getNe();
    NoquadTree *getNw();
    NoquadTree *getSw();
    NoquadTree *getSe();
    void setRegistroCoordenado(RegistrosCoordenados *registro);
    void setCoordX(double x);
    void setCoordY(double y);
    void setPai(NoquadTree *no);
    void setNe(NoquadTree *no);
    void setNw(NoquadTree *no);
    void setSw(NoquadTree *no);
    void setSe(NoquadTree *no);
};