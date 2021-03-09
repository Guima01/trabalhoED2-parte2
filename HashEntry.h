#ifndef HASHENTRY_H_INCLUDED
#define HASHENTRY_H_INCLUDED
#include "Registro.h"

using namespace std;

class HashEntry
{
private:
    int hashIndex;
    Registro* registro;
public:
    HashEntry(int hashIndex ,Registro* registro);
    ~HashEntry();
    int getHashIndex();
    Registro* getRegistro();
};

#endif // HASHENTRY_H_INCLUDED
