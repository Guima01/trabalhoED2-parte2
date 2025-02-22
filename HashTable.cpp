#include <iostream>
#include <list>
#include <string>
#include "HashTable.h"
#define TAMANHOREG 1431490;

using namespace std;

//Numeros primo 1.3x maior que tamanho de registros 1860941
//1500007 ,

HashTable::HashTable(int size)
{
    float plusSize;
    if(size == 1431490 )
        plusSize=429451;
    else plusSize = 0.3*size; 
    
    this->tableSize = size + plusSize; //1860941-TAMANHOREG
    this->currentSize = 0;
    table = new HashEntry *[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
}

HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i] != NULL)
            delete table[i];
        delete[] table;
    }
};

int HashTable::hashCode(int key, int i)
{
    return (key + (i * i)) % tableSize;
}

int HashTable::mixKeysRegister(Registro *registro) //preHash
{
    string code = registro->getCode();
    string date = registro->getDate();
    int i;
    unsigned long int valor = 3; // valores testados 7 , 3
    for (i = 0; i < date.size(); i++)
    {
        if ((int)date[i] == '-')
        {
            if (i <= code.size())
                valor = 97 * valor + (int)date[i]; //valores testados : 31 , 97  , 113
        }
        else
        {
            if (i <= code.size())
                valor = 97 * valor + (int)date[i] + (int)code[i];
            else
                valor = 97 * valor + (int)date[i];
        }
    }
    return valor%tableSize; //tirei o valor%tableSize;
}

void HashTable::insert(Registro *registro)
{
    int i = 0;
    int key = mixKeysRegister(registro);
    int hashIndex = key;
    while (table[hashIndex] != NULL) // enquanto tiver conflito
    {
        i++;
        hashIndex = hashCode(key, i);
    }
    table[hashIndex] = new HashEntry(hashIndex, registro);
    currentSize++;
}

//     void HashTable::remove(int key);

int HashTable::searchFromCodeAndDate(string code, string date)
{
    int key = mixKeys(code, date);
    int i = 0;
    int hashIndex = key;
    while (table[hashIndex] != NULL){
    if(table[hashIndex]->getRegistro()->getCode() == code && table[hashIndex]->getRegistro()->getDate() == date) //verificar se nao eh o msm code e date
    {
        return hashIndex;
        
    }
        i++;
        hashIndex = hashCode(key, i);
    }
    if (table[hashIndex] == NULL)
    {
        cout << "Não consta registro com essa chave." << endl;
        return -1;
    }
    else
        return hashIndex;
}

int HashTable::searchFromKey(int key)
{
    int i = 0;
    int hashIndex = hashCode(key, i);
    while (table[hashIndex] != NULL && table[hashIndex]->getHashIndex() != key)
    {
        i++;
        hashIndex = hashCode(key, i);
    }
    if (table[hashIndex] == NULL)
    {
        cout << "Não consta registro com essa chave." << endl;
        return -1;
    }
    else
        return hashIndex;
}

Registro *HashTable::getRegistroFromTable(int key)
{
    return table[key]->getRegistro();
}

int HashTable::mixKeys(string code, string date) //preHash
{
    int i;
    unsigned long int valor = 3; // valores testados 7 , 3
    for (i = 0; i < date.size(); i++)
    {
        if ((int)date[i] == '-')
        {
            if (i <= code.size())
                valor = 97 * valor + (int)date[i]; //valores testados : 31 , 97  , 113
        }
        else
        {
            if (i <= code.size())
                valor = 97 * valor + (int)date[i] + (int)code[i];
            else
                valor = 97 * valor + (int)date[i];
        }
    }
    return valor%tableSize;
}