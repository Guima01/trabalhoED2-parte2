#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "QuadTree.h"

using namespace std;

QuadTree::QuadTree()
{
    this->raiz = nullptr;
}
QuadTree::~QuadTree() {}

NoquadTree QuadTree::getRaiz()
{
    return *this->raiz;
}

void QuadTree::insert(NoquadTree *no)
{

    if (this->raiz == nullptr)
    {
        raiz = no;
    }
    else
    {
        NoquadTree *aux = raiz;
        while (true)
        {
            if (no->getCoordX() < aux->getCoordX())
            {
                if (no->getCoordY() < aux->getCoordY())
                {
                    if (aux->getSw() == 0)
                    {
                        aux->setSw(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getSw();
                    }
                }
                else
                {
                    if (aux->getNw() == 0)
                    {
                        aux->setNw(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getNw();
                    }
                }
            }
            else
            {
                if (no->getCoordY() < aux->getCoordY())
                {
                    if (aux->getSe() == 0)
                    {
                        aux->setSe(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getSe();
                    }
                }
                else
                {
                    if (aux->getNe() == 0)
                    {
                        aux->setNe(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getNe();
                    }
                }
            }
        }
        aux = no;
    }
}
void QuadTree::busca(double latitude, double longitude)
{

    NoquadTree *aux = raiz;
    while (true)
    {
        if (aux->getCoordX() == latitude && aux->getCoordY() == longitude)
        {
            cout << "encontrado";
            break;
        }
        if (latitude < aux->getCoordX())
        {
            if (longitude < aux->getCoordY())
            {
                if (aux->getSw() == 0)
                {
                    cout<<"não encontrado";
                    break;
                }
                else
                {
                    aux = aux->getSw();
                }
            }
            else
            {
                if (aux->getNw() == 0)
                {
                    cout<<"não encontrado";
                    break;
                }
                else
                {
                    aux = aux->getNw();
                }
            }
        }
        else
        {
            if (longitude < aux->getCoordY())
            {
                if (aux->getSe() == 0)
                {
                    cout<<"não encontrado";
                    break;
                }
                else
                {
                    aux = aux->getSe();
                }
            }
            else
            {
                if (aux->getNe() == 0)
                {
                    cout<<"não encontrado";
                    break;
                }
                else
                {
                    aux = aux->getNe();
                }
            }
        }
    }
}

/*NoquadTree QuadTree::compara(NoquadTree *r, NoquadTree *p)
{
    if (p->getCoordX() < r->getCoordX())
    {
        if (p->getCoordY() < r->getCoordY())
        {
            return r->getSw();
        }
        else
        {
            return r->getNw();
        }
    }
    else
    {
        if (p->getCoordY() < r->getCoordY())
        {
            return r->getSe();
        }
        else
        {
            return r->getNe();
        }
    }
}*/
