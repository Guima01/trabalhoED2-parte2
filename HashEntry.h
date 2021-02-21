#ifndef HASHENTRY_H_INCLUDED
#define HASHENTRY_H_INCLUDED
#include "Registro.h"

using namespace std;

class HashEntry
{
private:
    int key;
    Registro* registro;
public:
    HashEntry(int key ,Registro* registro);
    ~HashEntry();
    int getKey();
    Registro* getRegistro();
};

#endif // HASHENTRY_H_INCLUDED
