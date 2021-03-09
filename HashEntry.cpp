#include <iostream>
#include "HashEntry.h"
#include "Registro.h"


using namespace std;

HashEntry::HashEntry(int hashIndex , Registro* registro){
    this->hashIndex = hashIndex;
    this->registro = registro;
}

HashEntry::~HashEntry(){}

int HashEntry::getHashIndex(){
    return this->hashIndex;
}

Registro* HashEntry::getRegistro(){
    return registro;
}