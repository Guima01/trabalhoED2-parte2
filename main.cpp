#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <math.h>
#include <algorithm>
#include "quadTree.h"
#include "Registro.h"
#include "HashTable.h"
#include "ArvoreB.h"
#define TAMANHOREG 1431490;

using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

void removeAccents(string &str)
{
    string accent_chars = "ÁÀÃÂÇáàãâçÉÊéêÍíÑÓÔÕñóôõÚÜúü";
    string unnacent_chars = "AAAAAAAACCaaaaaaaaccEEEEeeeeIIiiNNOOOOOOnnooooooUUUUuuuu";
    for (int j = 0; str[j] != *"\0"; j++)
    {
        for (int i = 0; i < accent_chars.size(); i = i + 1)
        {
            if (str[j] == accent_chars[i])
            {
                if (str[j + 1] == accent_chars[i + 1])
                {
                    str[j] = unnacent_chars[i];
                    if (str[j] == *"\0")
                    {
                        break;
                    }
                    str.erase(str.begin() + j + 1);
                    break;
                }
                else
                {
                    i++;
                }
            }
        }
        if (str[j] == ' ' && (str[j + 1] >= 'a' && str[j + 1] <= 'z'))
        {
            str[j + 1] = str[j + 1] + 'A' - 'a';
        }
    }
}

void leLinha(ifstream &arq)
{
    QuadTree quad;
    string str;
    for (int i = 0; getline(arq, str); i++)
    {
        if (i != 0)
        {
            RegistrosCoordenados *registroCoordenado = new RegistrosCoordenados();
            vector<string> stringDados = split(str, ',');
            registroCoordenado->setStateCode(atoi(stringDados[0].c_str()));
            registroCoordenado->setCityCode(atoi(stringDados[1].c_str()));
            removeAccents(stringDados[2]); //não sei se vai ser necessário
            registroCoordenado->setCityName(stringDados[2]);

            registroCoordenado->setLatitude(stod(stringDados[3].c_str()));
            registroCoordenado->setLongitude(stod(stringDados[4].c_str()));

            if (stringDados[5] == "FALSE")
            {
                registroCoordenado->setCapital(false);
            }
            else
            {
                registroCoordenado->setCapital(true);
            }
            NoquadTree *no = new NoquadTree(registroCoordenado);
            quad.insert(no);
        }
    }
    quad.busca(-22.2779, -46.3716);
}

int leLinhaArquivoProcessado(vector<Registro> &registros, ifstream &arq)
{
    HashTable *hashzada = new HashTable(1431490);
    string str;
    int cases, deaths, cont = 0;
    for (int i = 0; getline(arq, str); i++)
    {
        if (i != 0)
        {
            Registro *registra = new Registro();

            vector<string> stringDados = split(str, ',');

            cases = atoi(stringDados[4].c_str());
            deaths = atoi(stringDados[5].c_str());

            registra->setDate(stringDados[0]);
            registra->setState(stringDados[1]);
            registra->setName(stringDados[2]);
            registra->setCode(stringDados[3].substr(0, 6));
            registra->setCases(cases);
            registra->setDeaths(deaths);

            registros.push_back(*registra);
        }
        cont++;
    }
    cout << "Leitura do arquivo brazil_covid19_cities_processado.csv finalizada." << cont - 1 << endl
         << endl;
    return cont - 1;
}



int main(int argc, char const *argv[])
{

    // string path = argv[1];
    // path = path + "brazil_cities_coordinates.csv";
    // ifstream arquivo;
    // arquivo.open(path, ios::in);
    // leLinha(arquivo);

    /// Testes -> Registros diários e tabela hash

    vector<Registro> registros;
    string caminho = argv[1];
    caminho += "brazil_covid19_cities_processado.csv";
    ifstream arquivoProcessado;
    arquivoProcessado.open(caminho, ios::in);

    int tam = leLinhaArquivoProcessado(registros, arquivoProcessado);
    HashTable *hashzada = new HashTable(tam);
    ArvoreB *arvb = new ArvoreB(5,hashzada);

    int hashIndex;
    int v[100];
    int i;

    for(i=0 ; i<tam ; i++)
    {
        if( i == 8)         
            break;
        else
        {
            hashzada->insert(&registros[i]);
            hashIndex = hashzada->searchFromCodeAndDate(registros[i].getCode(),registros[i].getDate());
            v[i] = hashIndex;
        }
    }

    i--;

    while(i >=0)
    {
        arvb->insere(v[i],arvb->getRaiz(),nullptr);
        i--;
    }

    cout << endl << endl;
    arvb->getRaiz()->print(hashzada);

    //cout << arvb->search(hashIndex) << endl;
    return 0;
}
//g++ -o parte2 -O3 *.cpp
//./parte2.exe ./Arquivos/
//https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/