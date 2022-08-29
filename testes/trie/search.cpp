#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "trie.h"
#include "processaLivro.h"
#include "list.h"
#include "config.h"


using namespace std;


int main(int argc, char *argv[])
{
    //criando a Trie p armazenar as 50 palavras mais usadas 
    Trie T;
    T.insert("bacana",0);
    T.insert("bacana1",1);
    T.insert("bacana2",2);
    T.insert("bacana3",3);
    T.insert("bacana4",4);
    T.insert("bacana5",5);  
    
    LinkedList<int> *aux = T.search("bacana3");
    cout << "Palavra: ->" << "bacana3" << endl;
    aux->printList("bacana3");
        
   
    
    return 0;   
}