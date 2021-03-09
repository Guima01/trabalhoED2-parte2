#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <math.h>
#include <algorithm>
#include <chrono>
#include "quadTree.h"
#include "Registro.h"
#include "HashTable.h"
#include "ArvoreB.h"
#include "AVLtree.h"
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

void leLinha(QuadTree &quad, ifstream &arq, int linhas)
{
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

            if (i == linhas)
            {
                break;
            }
        }
    }
}

int leLinhaArquivoProcessado(vector<Registro> &registros, ifstream &arq)
{
    // HashTable *hashzada = new HashTable(1431490);
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

int leLinhaArquivoProcessadoPraN(vector<Registro> &registros, ifstream &arq, int n)
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

            if (i == n)
            {
                break;
            }
        }
        cont++;
    }
    cout << "Leitura do arquivo brazil_covid19_cities_processado.csv finalizada." << cont - 1 << endl
         << endl;
    return cont - 1;
}

void salvarArquivo(vector<Registro> &registros, ofstream &saida)
{
    saida << "date,state,name,code,cases,deaths" << endl;
    for (int i = 0; i < registros.size(); i++)
    {
        saida << registros[i].getDate() << ",";
        saida << registros[i].getState() << ",";
        saida << registros[i].getName() << ",";
        saida << registros[i].getCode() << ",";
        saida << registros[i].getCases() << ",";
        saida << registros[i].getDeaths() << endl;
    }
}

void moduloTesteAlgoritmos(string path, int id, int numeroRegistros)
{
    int identificaOrdenacao;

    cout << endl;

    cout << "Escolha a estrutura de dados" << endl;
    cout << "[1] QuadTree " << endl;
    cout << "[2] HashTable " << endl;
    cout << "[3] AVLTree " << endl;
    cout << "[4] BTree " << endl;
    cout << "[0] Sair " << endl;

    do
    {
        cin >> identificaOrdenacao;

    } while (identificaOrdenacao < 0 && identificaOrdenacao > 4);

    if (identificaOrdenacao == 1)
    {
        vector<RegistrosCoordenados> vet;
        QuadTree quad;
        path = path + "brazil_cities_coordinates.csv";
        ifstream arquivo;
        arquivo.open(path, ios::in);
        leLinha(quad, arquivo, numeroRegistros);
        arquivo.close();
        if (id == 1)
        {
            quad.imprimePorNivel(quad.getRaiz(), 0);
        }
        else if (id == 2)
        {
            ofstream saida("saidaQuadTree.txt");
            quad.ImprimeArquivoTexto(quad.getRaiz(), 0, saida);
        }
        quad.retornaRegistrosNasCoordenadas(vet, quad.getRaiz(), -27.0000, -51.0000, -27.9999, -51.9999);
    }

    else if (identificaOrdenacao == 2)
    {
        vector<Registro> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);
        int tam = leLinhaArquivoProcessado(registros, arquivoProcessado);
        HashTable *hashzada = new HashTable(1431490);
        int hashIndex;
        for (int i = 0; i < tam; i++)
        {
            hashzada->insert(&registros[i]);
        }
        ofstream saida("printandoHash.txt");
        saida << "date,state,name,code,cases,deaths" << endl;
        for (int i = 0; i < registros.size(); i++)
        {
            hashIndex = hashzada->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());
            saida << hashzada->getRegistroFromTable(hashIndex)->getDate() << ",";
            saida << hashzada->getRegistroFromTable(hashIndex)->getState() << ",";
            saida << hashzada->getRegistroFromTable(hashIndex)->getName() << ",";
            saida << hashzada->getRegistroFromTable(hashIndex)->getCode() << ",";
            saida << hashzada->getRegistroFromTable(hashIndex)->getCases() << ",";
            saida << hashzada->getRegistroFromTable(hashIndex)->getDeaths() << endl;
        }
    }
    else if (identificaOrdenacao == 3)
    {
        vector<Registro> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, numeroRegistros);
        HashTable *hashzada = new HashTable(tam);
        AVLtree *AVL = new AVLtree();

        int hashIndex;

        for (int i = 0; i < tam; i++)
        {
            if (i == numeroRegistros)
            {
                break;
            }
            hashzada->insert(&registros[i]);
            hashIndex = hashzada->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());
            AVL->insere(hashIndex);
        }

        if (id == 1)
        {
            AVL->imprime(hashzada);
        }
        else if (id == 2)
        {
            ofstream saida("saidaAVLTree.txt");
            cout << "SAIDA POR ARQUIVO" << endl;
            AVL->saidaArqv(saida, hashzada);
        }
        return;
    }
    else if (identificaOrdenacao == 4)
    {
        vector<Registro> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, numeroRegistros);
        HashTable *hashzada = new HashTable(tam);
        ArvoreB *arvb = new ArvoreB(10, hashzada);
        int comparacoes = 0;

        int hashIndex;

        for (int i = 0; i < tam; i++)
        {
            if (i == numeroRegistros)
            {
                break;
            }
            hashzada->insert(&registros[i]);
            hashIndex = hashzada->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());
            arvb->insert(hashIndex, comparacoes);
        }

        if (id == 1)
        {
            arvb->getRaiz()->print(hashzada, 0);
        }
        else if (id == 2)
        {
            ofstream saida("saidaBTree.txt");
            arvb->getRaiz()->salvaArquivo(hashzada, 0, saida);
        }
        return;
    }

    else if (identificaOrdenacao == 0)
        return;
}

void moduloTeste(string path)
{
    int id;
    do
    {
        int n;
        cout << "------------------------------" << endl;
        cout << "Digite o numero de registros:" << endl;
        cin >> n;
        if (n <= 20)
        {
            moduloTesteAlgoritmos(path, 1, n);
            return;
        }
        else if (n > 20)
        {
            moduloTesteAlgoritmos(path, 2, n);
            return;
        }
    } while (id != 0);
}

int menu()
{
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Modulo de testes" << endl;
    cout << "[2] Analise das estruturas balanceadas"<<endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void analiseParaMRegistros(HashTable *hash, vector<Registro> registros, int m)
{
    clock_t timeStart, timeStop;
    vector<Registro> registros2;
    AVLtree *avlTree = new AVLtree();
    ArvoreB *Btree20 = new ArvoreB(10, hash);
    ArvoreB *Btree200 = new ArvoreB(100, hash);
    int comparacoesBTree20 = 0;
    int comparacoesBTree200 = 0;

    registros2 = registros;
    random_shuffle(registros2.begin(), registros2.end());

    timeStart = clock();
    for (int i = 0; i < m; i++)
    {
        int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
        avlTree->insere(index);
    }
    timeStop = clock();

    cout<<"tempo de insercao AVLTree: "<<((double)(timeStop - timeStart) / CLOCKS_PER_SEC)<<endl;

    timeStart = clock();
    for (int i = 0; i < m; i++)
    {
        int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
        Btree20->insert(index,comparacoesBTree20);
    }
    timeStop = clock();

    cout<<"tempo de insercao BTree20: "<<((double)(timeStop - timeStart) / CLOCKS_PER_SEC)<<endl;
    cout<<"numero de comparacoes BTree20: "<< comparacoesBTree20 <<" para "<< m << " registros"<<endl;


    timeStart = clock();
    for (int i = 0; i < m; i++)
    {
        int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
        Btree200->insert(index, comparacoesBTree200);
    }
    timeStop = clock();

    cout<<"tempo de insercao BTree200: "<<((double)(timeStop - timeStart) / CLOCKS_PER_SEC)<<endl;
    cout<<"numero de comparacoes BTree200: "<< comparacoesBTree200 <<" para "<< m << " registros"<<endl;
}

void seleciona(int selecao, string path)
{
    vector<Registro> registros;
    switch (selecao)
    {
    case 1:
    {
        moduloTeste(path);
        break;
    }
    case 2:
    {
        int arr[5] = {10000, 50000, 100000, 500000, 1000000};
        vector<Registro> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);
        int tam = leLinhaArquivoProcessado(registros, arquivoProcessado);
        HashTable *hash = new HashTable(1431490);
        int hashIndex;
        for (int i = 0; i < tam; i++)
        {
            hash->insert(&registros[i]);
        }
        for (int i = 0; i < 5; i++)
        {
            analiseParaMRegistros(hash, registros, arr[i]);
        }
        break;
    }

    }
}

void mainMenu(string path)
{
    int selecao = menu();
    while (selecao != 0)
    {
        seleciona(selecao, path);
        selecao = menu();
    }
}

int main(int argc, char const *argv[])
{

    string path = argv[1];
    mainMenu(path);

    return 0;
}
//  g++ -o parte2 -O3 *.cpp
//  parte2.exe ./Arquivos/