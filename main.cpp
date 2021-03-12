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
    string code;
    for (int i = 0; getline(arq, str); i++)
    {
        if (i != 0)
        {
            RegistrosCoordenados *registroCoordenado = new RegistrosCoordenados();
            vector<string> stringDados = split(str, ',');
            registroCoordenado->setStateCode(atoi(stringDados[0].c_str()));
            code = stringDados[1];
            code = code.erase(code.size() - 1);
            registroCoordenado->setCityCode(code);
            removeAccents(stringDados[2]);
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
    cout << "Leitura do arquivo brazil_covid19_cities_processado.csv finalizada." << cont << endl
         << endl;
    return cont;
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
    else if (identificaOrdenacao == 3 || identificaOrdenacao == 4)
    {
        vector<Registro> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int comparacoes = 0;
        int hashIndex;
        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, numeroRegistros);
        HashTable *hash = new HashTable(tam);

        AVLtree *AVL = new AVLtree(hash);
        int ordem = 1;
        if (identificaOrdenacao == 4)
        {
            cout << "Criar arvore B de ordem "; // ordem par
            cin >> ordem;
            ordem = ordem / 2;
        }

        ArvoreB *arvb = new ArvoreB(ordem, hash);

        for (int i = 0; i < tam; i++)
        {
            if (i == numeroRegistros)
            {
                break;
            }
            hash->insert(&registros[i]);
            hashIndex = hash->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());

            if (identificaOrdenacao == 3)
            {
                AVL->insere(hashIndex, comparacoes);
            }
            else
            {
                arvb->insere(hashIndex, comparacoes);
            }
        }

        if (id == 1)
        {
            if (identificaOrdenacao == 3)
            {
                AVL->imprime(hash);
            }
            else
            {
                arvb->getRaiz()->print(hash, 0);
            }
        }
        else if (id == 2)
        {
            if (identificaOrdenacao == 3)
            {
                ofstream saida("saidaAVLTree.txt");
                cout << "SAIDA POR ARQUIVO" << endl;
                AVL->saidaArqv(saida, hash);
            }
            else
            {
                ofstream saida("saidaBTree.txt");
                arvb->getRaiz()->salvaArquivo(hash, 0, saida);
            }
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
    cout << "[2] Analise das estruturas balanceadas" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void analiseParaMRegistros(HashTable *hash, vector<RegistrosCoordenados> registrosCoordenados, vector<Registro> registros, int m, ofstream &saida, string codigo)
{
    clock_t timeStart, timeStop;
    vector<Registro> registros2;
    registros2 = registros;

    int comparacaoBTree20Media = 0;
    int comparacaoBTree200Media = 0;
    int comparacaoAvlMedia = 0;

    double tempoMediaAvl = 0;
    double tempoMediaBtree20 = 0;
    double tempoMediaBtree200 = 0;

    double tempoMedioBuscaAvl = 0;
    double tempoMedioBuscaBtree20 = 0;
    double tempoMedioBuscaBtree200 = 0;

    double totalCasosMedioAvl = 0;
    double totalCasosMedioBtree20 = 0;
    double totalCasosMedioBtree200 = 0;

    double comparacaoMediaBuscaBTree20 = 0;
    double comparacaoMediaBuscaBTree200 = 0;
    double comparacaoMediaBuscaAvl = 0;

    double tempoMedioBuscaAvlS2 = 0;
    double tempoMedioBuscaBtree20S2 = 0;
    double tempoMedioBuscaBtree200S2 = 0;

    double totalCasosMedioAvlS2 = 0;
    double totalCasosMedioBtree20S2 = 0;
    double totalCasosMedioBtree200S2 = 0;

    double comparacaoMediaBuscaBTree20S2 = 0;
    double comparacaoMediaBuscaBTree200S2 = 0;
    double comparacaoMediaBuscaAvlS2 = 0;

    for (int i = 0; i < 5; i++)
    {
        AVLtree *avlTree = new AVLtree(hash);
        ArvoreB *Btree20 = new ArvoreB(10, hash);
        ArvoreB *Btree200 = new ArvoreB(100, hash);

        int comparacaoBTree20 = 0;
        int comparacaoBTree200 = 0;
        int comparacaoAvl = 0;

        int comparacaoBuscaBtree20 = 0;
        int comparacaoBuscaBtree200 = 0;
        int comparacaoBuscaAVLtree = 0;

        int totalCasosBtree20 = 0;
        int totalCasosBtree200 = 0;
        int totalCasosAVLtree = 0;

        int comparacaoBuscaBtree20S2 = 0;
        int comparacaoBuscaBtree200S2 = 0;
        int comparacaoBuscaAVLtreeS2 = 0;

        int totalCasosBtree20S2 = 0;
        int totalCasosBtree200S2 = 0;
        int totalCasosAVLtreeS2 = 0;

        random_shuffle(registros2.begin(), registros2.end());

        //AVL
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            avlTree->insere(index, comparacaoAvl);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore AVL :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoAvl << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMediaAvl += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        comparacaoAvlMedia += comparacaoAvl;

        //BTree20
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            Btree20->insere(index, comparacaoBTree20);
        }

        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBTree20 << " para " << m << " registros" << endl;

        tempoMediaBtree20 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        comparacaoBTree20Media += comparacaoBTree20;

        //S1
        timeStart = clock();
        Btree20->calculaTotalCasosCidade(Btree20->getRaiz(), codigo, comparacaoBuscaBtree20, totalCasosBtree20);
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S1 Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos da cidade selecionada: " << totalCasosBtree20 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree20 << " para " << m << " registros" << endl;

        tempoMedioBuscaBtree20 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree20 += totalCasosBtree20;
        comparacaoMediaBuscaBTree20 += comparacaoBuscaBtree20;

        //S2
        timeStart = clock();
        for (int i = 0; i < registrosCoordenados.size(); i++)
        {
            Btree20->calculaTotalCasosCidade(Btree20->getRaiz(), registrosCoordenados[i].getCityCode(), comparacaoBuscaBtree20S2, totalCasosBtree20S2);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S2 Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos das cidades no intervalo selecionado: " << totalCasosBtree20S2 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree20S2 << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMedioBuscaBtree20S2 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree20S2 += totalCasosBtree20S2;
        comparacaoMediaBuscaBTree20S2 += comparacaoBuscaBtree20S2;

        //BTree200
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            Btree200->insere(index, comparacaoBTree200);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBTree200 << " para " << m << " registros" << endl;

        tempoMediaBtree200 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        comparacaoBTree200Media += comparacaoBTree200;

        //S1
        timeStart = clock();
        Btree200->calculaTotalCasosCidade(Btree200->getRaiz(), codigo, comparacaoBuscaBtree200, totalCasosBtree200);
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos da cidade selecionada: " << totalCasosBtree200 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree200 << " para " << m << " registros" << endl
              << endl;

        tempoMedioBuscaBtree200 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree200 += totalCasosBtree200;
        comparacaoMediaBuscaBTree200 += comparacaoBuscaBtree200;

        //S2
        timeStart = clock();
        for (int i = 0; i < registrosCoordenados.size(); i++)
        {
            Btree200->calculaTotalCasosCidade(Btree200->getRaiz(), registrosCoordenados[i].getCityCode(), comparacaoBuscaBtree200S2, totalCasosBtree200S2);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S2 Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos das cidades no intervalo selecionado: " << totalCasosBtree200S2 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree200S2 << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMedioBuscaBtree200S2 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree200S2 += totalCasosBtree200S2;
        comparacaoMediaBuscaBTree200S2 += comparacaoBuscaBtree200S2;
    }

    saida << "MEDIAS" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore AVL : " << tempoMediaAvl / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoAvlMedia / 5 << " para " << m << " registros" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore B de ordem 20 : " << tempoMediaBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoBTree20Media / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S1 Arvore B de ordem 20 : " << tempoMedioBuscaBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoMediaBuscaBTree20 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos durante a execução : " << totalCasosMedioBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S2 Arvore B de ordem 20 : " << tempoMedioBuscaBtree20S2 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos das cidades no intervalo selecionado: " << totalCasosMedioBtree20S2 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoMediaBuscaBTree20S2 / 5 << " para " << m << " registros" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore B de ordem 200 : " << tempoMediaBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoBTree200Media / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S1 Arvore B de ordem 200 : " << tempoMedioBuscaBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoMediaBuscaBTree200 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos durante a execução : " << totalCasosMedioBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S2 Arvore B de ordem 200 : " << tempoMedioBuscaBtree200S2 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos das cidades no intervalo selecionado: " << totalCasosMedioBtree200S2 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes durante a execução : " << comparacaoMediaBuscaBTree200S2 / 5 << " para " << m << " registros" << endl
          << endl
          << endl
          << endl
          << endl;
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

        int hashIndex;
        int tam = leLinhaArquivoProcessado(registros, arquivoProcessado);

        ofstream saida("Analise das estruturas.txt");
        HashTable *hash = new HashTable(1431490);

        for (int i = 0; i < tam; i++)
        {
            hash->insert(&registros[i]);
        }

        QuadTree quad;
        string caminho2 = path + "brazil_cities_coordinates.csv";
        ifstream arquivo;
        arquivo.open(caminho2, ios::in);
        leLinha(quad, arquivo, 5571);
        arquivo.close();

        string codigo;
        double latitude1;
        double longitude1;
        double latitude2;
        double longitude2;

        cout << "Digite o codigo da cidade para S1:" << endl;
        cin >> codigo;
        cout << "Digite a latitude 1 para S2:" << endl;
        cin >> latitude1;
        cout << "Digite a longitude 1 para S2:" << endl;
        cin >> longitude1;
        cout << "Digite a latitude 2 para S2:" << endl;
        cin >> latitude2;
        cout << "Digite a longitude 2 para S2:" << endl;
        cin >> longitude2;

        vector<RegistrosCoordenados> registrosCoordenados;

        quad.retornaRegistrosNasCoordenadas(registrosCoordenados, quad.getRaiz(), latitude1, longitude1, latitude2, longitude2);

        for (int i = 0; i < 5; i++)
        {
            analiseParaMRegistros(hash, registrosCoordenados, registros, arr[i], saida, codigo);
        }
        break;
    }

    default:
        break;
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