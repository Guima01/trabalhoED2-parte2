#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <list>
#include "HashEntry.h"
using namespace std;

class HashTable
{
private:
    HashEntry **table;
    int tableSize, currentSize;

public:
    HashTable(int size);
    ~HashTable();

    void insert(Registro *registro);
    void remove(int key);
    int searchFromKey(int key);                          // return the hashIndex
    int searchFromCodeAndDate(string code, string date); // return the hashIndex
    int hashCode(int key, int i);
    int mixKeysRegister(Registro *registro); // returns a int that can be "hashed"
    int mixKeys(string code, string date);
    int getCurrentSize() { return currentSize; };

    Registro *getRegistroFromTable(int key);
};

#endif
