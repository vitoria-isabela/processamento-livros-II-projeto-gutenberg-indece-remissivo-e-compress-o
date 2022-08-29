#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "config.h"

#include "processaLivro.h"

int main(int argc, char *argv[])
{
    
    
// # Teste1 Funciona

    ProcessBook book1(BOOK1,1);
    ProcessBook book1_2(BOOK1,2);
    ProcessBook book1_3(BOOK1,3);
    
 
     
    
    book1.sortVector(QUICKSORT);        
    book1_2.sortVector(SHELLSORT);    
    book1_3.sortVector(MERGESORT);

  
   
   
    return 0;
}