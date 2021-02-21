#include <iostream>
#include "HashEntry.h"
#include "Registro.h"


using namespace std;

HashEntry::HashEntry(int key , Registro* registro){
    this->key = key;
    this->registro = registro;
}

HashEntry::~HashEntry(){}

int HashEntry::getKey(){
    return this->key;
}

Registro* HashEntry::getRegistro(){
    return registro;
}