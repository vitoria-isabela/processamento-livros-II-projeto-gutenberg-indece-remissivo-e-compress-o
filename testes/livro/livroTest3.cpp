#include <iostream>
#include "processaLivro.h"
#include "config.h"

using namespace std;

// Teste Obter Numero Linhas
int main(int argc, char *argv[])
{
   string input = INPUT_DIR + std::string("book11.txt");
   cout << "Este é o diretorio de exemplo: " << input << endl;
   ProcessBook processBook(input);
   string word = "Word, : With. Pontuation! %#@";
   int numberLines = processBook.getNumberLines(input);
   cout << "Result:" << numberLines << endl;

   return 0;
}