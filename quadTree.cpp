#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "quadTree.h"

using namespace std;

QuadTree::QuadTree()
{
    this->raiz = nullptr;
}
QuadTree::~QuadTree() {}

NoquadTree *QuadTree::getRaiz()
{
    return this->raiz;
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
            cout << aux->getRegistroCoordenado().getCityName();
            break;
        }
        if (latitude < aux->getCoordX())
        {
            if (longitude < aux->getCoordY())
            {
                if (aux->getSw() == 0)
                {
                    cout << "Nao encontrado";
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
                    cout << "Nao encontrado";
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
                    cout << "Nao encontrado";
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
                    cout << "Nao encontrado";
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

void QuadTree::imprimePorNivel(NoquadTree *p, int nivel)
{
    if (p != nullptr)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << "(";
        cout << p->getRegistroCoordenado().getLatitude();
        cout << ", ";
        cout << p->getRegistroCoordenado().getLongitude();
        cout << ")" << endl;
        imprimePorNivel(p->getNw(), nivel + 1);
        imprimePorNivel(p->getNe(), nivel + 1);
        imprimePorNivel(p->getSw(), nivel + 1);
        imprimePorNivel(p->getSe(), nivel + 1);
    }
}

void QuadTree::ImprimeArquivoTexto(NoquadTree *p, int nivel, ofstream &saida)
{
    if (p != nullptr)
    {
        saida << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            saida << "--";
        saida << "(";
        saida << p->getRegistroCoordenado().getLatitude();
        saida << ", ";
        saida << p->getRegistroCoordenado().getLongitude();
        saida << ")" << endl;
        ImprimeArquivoTexto(p->getNw(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getNe(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getSw(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getSe(), nivel + 1, saida);
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
