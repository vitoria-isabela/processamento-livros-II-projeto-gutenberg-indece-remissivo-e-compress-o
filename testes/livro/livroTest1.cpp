#include <iostream>
#include "config.h"
#include "processaLivro.h"

using namespace std;

// Teste Lowercase
int main(int argc, char *argv[])
{
   string input = INPUT_DIR + std::string("book11.txt");
   cout << "Este é o diretorio de exemplo: " << input << endl;
   ProcessBook processBook(input);
   string word = "WordInUpperCase";
   processBook.convertWordToLowercase(word);
   cout << "Lendo o vetor: " << endl;
   std::cout << "Result:" << word << endl;
   return 0;
}