// Teste Insert
#include <iostream>
#include "hash.h"
using namespace std;

int main()
{

    HashTable *tabela = new HashTable(5, 1);
    tabela->insertKey("obi");
    tabela->insertKey("wan");
    tabela->insertKey("kenobi");

    return 0;
}