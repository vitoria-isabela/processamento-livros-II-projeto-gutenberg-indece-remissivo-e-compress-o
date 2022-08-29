#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include "config.h"
#include "sort.h"
#include "processaLivro.h"

bool compareFinal(HashEntry &a, HashEntry &b)
{
    return a.getOccurrencies() > b.getOccurrencies();
}

int main(int argc, char *argv[])
{
    
HashEntry *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10 = new HashEntry[50];
HashEntry *vetor = new HashEntry[500];
fstream mostusedwords;
string dir = CASO4 + std::string("mostusedwords.txt");
mostusedwords.open(dir,ios::out); 

// ----------------------------------------------------------------------------------------------------------------

    // Não funciona se montar dessa forma
    // Erro de bad alloc
      
    // ProcessBook book1(BOOK1,1);
    // v1 = book1.getVector50();
    // for (int i = 0; i < 50; i++)
    // {
    //     vetor[i] = v1[i];
    // }
    
    // ProcessBook book2(BOOK2,2);
    // v2 = book2.getVector50();
    // for (int i = 50; i < 100; i++)
    // {
    //     vetor[i] = v2[i-50];
    // }
    
    // ProcessBook book3(BOOK3,3);
    // v3 = book3.getVector50();
    // for (int i = 100; i < 150; i++)
    // {
    //     vetor[i] = v3[i-100];
    // }

    // ProcessBook book4(BOOK4,4);
    // v4 = book4.getVector50();
    // for (int i = 150; i < 200; i++)
    // {
    //     vetor[i] = v4[i-150];
    // }
    
    // ProcessBook book5(BOOK5,5);
    // v5 = book5.getVector50();
    // for (int i = 200; i < 250; i++)
    // {
    //     vetor[i] = v5[i-200];
    // }

    // ProcessBook book6(BOOK6,6);
    // v6 = book6.getVector50();
    // for (int i = 250; i < 300; i++)
    // {
    //     vetor[i] = v6[i-250];
    // }

    // ProcessBook book7(BOOK7,7);
    // v7 = book7.getVector50();
    // for (int i = 300; i < 350; i++)
    // {
    //     vetor[i] = v7[i-300];
    // }
    
    // ProcessBook book8(BOOK8,8);
    // v8 = book8.getVector50();
    // for (int i = 350; i < 400; i++)
    // {
    //     vetor[i] = v8[i-350];
    // }

    // ProcessBook book9(BOOK9,9);
    // v9 = book9.getVector50();
    // for (int i = 400; i < 450; i++)
    // {
    //     vetor[i] = v8[i-400];
    // }

    // ProcessBook book10(BOOK10,10);
    // v10 = book10.getVector50();
    // for (int i = 450; i < 500; i++)
    // {
    //     vetor[i] = v8[i-450];
    // }

    /* ---------------------------------------------------------------------------------------------------------*/

    // Funciona sem erro se rodar desta forma

    ProcessBook book1(BOOK1,1);
    ProcessBook book2(BOOK2,2);
    ProcessBook book3(BOOK3,3);
    ProcessBook book4(BOOK4,4);
    ProcessBook book5(BOOK5,5);
    ProcessBook book6(BOOK6,6);
    ProcessBook book7(BOOK7,7);
    ProcessBook book8(BOOK8,8);
    ProcessBook book9(BOOK9,9);
    ProcessBook book10(BOOK10,10);
     
    
    
    v1 = book1.getVector50();
    for (int i = 0; i < 50; i++)
    {
        vetor[i] = v1[i];
    }
    
   
    v2 = book2.getVector50();
    for (int i = 50; i < 100; i++)
    {
        vetor[i] = v2[i-50];
    }
    
   
    v3 = book3.getVector50();
    for (int i = 100; i < 150; i++)
    {
        vetor[i] = v3[i-100];
    }

    
    v4 = book4.getVector50();
    for (int i = 150; i < 200; i++)
    {
        vetor[i] = v4[i-150];
    }
    
    
    v5 = book5.getVector50();
    for (int i = 200; i < 250; i++)
    {
        vetor[i] = v5[i-200];
    }

    
    v6 = book6.getVector50();
    for (int i = 250; i < 300; i++)
    {
        vetor[i] = v6[i-250];
    }

    
    v7 = book7.getVector50();
    for (int i = 300; i < 350; i++)
    {
        vetor[i] = v7[i-300];
    }
    
    
    v8 = book8.getVector50();
    for (int i = 350; i < 400; i++)
    {
        vetor[i] = v8[i-350];
    }

    
    v9 = book9.getVector50();
    for (int i = 400; i < 450; i++)
    {
        vetor[i] = v8[i-400];
    }

 
    v10 = book10.getVector50();
    for (int i = 450; i < 500; i++)
    {
        vetor[i] = v8[i-450];
    }
    
    
    shell_sort<HashEntry>(vetor,500, compareFinal);
    
    mostusedwords << "-------------------------------------------------------------------------------------" << endl;
    mostusedwords << "IMPRIMINDO AS 50 PALAVRAS DE MAIORES OCORRENCIAS EM TODOS OS LIVROS: " << endl;
    mostusedwords << "-------------------------------------------------------------------------------------" << endl;
   
    
    for (int i = 0; i < 50; i++)
    {
        mostusedwords << endl
        << " Numero de Ocorrencias da palavra \"" << vetor[i].getKey() << "\": " << vetor[i].getOccurrencies() << endl;
    }
    
    mostusedwords << ">>>>>>>>>>>>>>>>>>>>" << endl;
    
    
     
    return 0;
}