#include <iostream>
#include <vector>
#include "HashEntry.h"

using namespace std;

class NoB
{
    private:
    vector<int> keys;
    vector<NoB*> filhos;
    int n;
    bool folha;

    public:
    NoB();
    ~NoB();

    void addFilho(NoB* filho, int i);
    void addKeys(int key);
    void setN();
    void setFolha();
    
    int getN();
    vector<int> getKeys();
    vector<NoB*> getFilhos();
    bool getFolha();





    
};

