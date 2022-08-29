
#include <iostream>
#include "hash.h"
using namespace std;
 // Teste de Busca
int main()
{

    HashTable *tabela = new HashTable(10, 1);

    tabela->insertKey("obi");
    tabela->insertKey("wan");
    tabela->insertKey("kenobi");
    tabela->insertKey("anakin");
    tabela->insertKey("skywalker");
    tabela->insertKey("ashoka");
    tabela->insertKey("tano");
    tabela->insertKey("kinana");

    HashEntry *one = tabela->searchKey("ashoka");
    cout << "Palavra: " << one->getKey() << "Ocorr.: " << one->getOccurrencies() << endl;

    return 0;
}
