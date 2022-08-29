#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "trie.h"
#include "processaLivro.h"
#include "config.h"


using namespace std;


int main(int argc, char *argv[])
{
    //criando a Trie p armazenar as 50 palavras mais usadas 
    Trie T;
    // Lendo o livro e Descubrindo as 50 palavras mais usadas
    ProcessBook book1(BOOK1, &T);    
    // Armazena o vetor p inserir na trie
    HashEntry *v1 = new HashEntry[50];    
    v1 = book1.getVector50();
    //Inserindo na trie
    
    for (int i=0; i<50; i++)
    {
     LinkedList<int> *aux = T.search( v1[i].getKey() );
     cout << "Palavra: ->" << v1[i].getKey() << endl;
     aux->printList(v1[i].getKey());

    }
    return 0;   
}