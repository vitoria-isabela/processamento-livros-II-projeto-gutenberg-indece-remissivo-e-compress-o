#include <iostream>
#include "processaLivro.h"
#include "config.h"

using namespace std;

// Teste Remove Pontuation
int main(int argc, char *argv[])
{
   string input = INPUT_DIR + std::string("book11.txt");
   cout << "Este é o diretorio de exemplo: " << input << endl;
   ProcessBook processBook(input);
   string word = "Word, : With. Pontuation! %#@";
   processBook.removePontuation(word);

   cout << "Result:" << word << endl;
   return 0;
}