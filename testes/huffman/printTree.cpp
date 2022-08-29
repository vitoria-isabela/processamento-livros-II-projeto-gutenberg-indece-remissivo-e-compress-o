#include <vector>
#include "huffman.h"
#include <fstream>
#include "processaLivro.h"

using namespace std;

vector< pair<char, unsigned> > HuffmanFreqTable()
{
    fstream bookStream;

    bookStream.open(BOOK1, ios::in);

    if (bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }

    vector< pair<char, unsigned> > freq_table;

    map<char, unsigned> cfmap;   
   	char caracter;
	while ( !bookStream.eof() )
	{
        bookStream.get(caracter);
		if (cfmap.find(caracter) == cfmap.end())
		{
			cfmap.insert(make_pair(caracter,1));
		}
		cfmap[caracter] += 1;
	}

    for (map<char, unsigned>::iterator it = cfmap.begin();
         it != cfmap.end(); ++it) 
         {
           freq_table.push_back(make_pair(it->first, it->second));
         }

  return freq_table;
}

//Esse teste constrói uma arvore de huffman
int main(int argc, char *argv[])
{
    ProcessBook book (BOOK9, "Book9");

    book.htree = book.htree->build_tree( book.freq_table );
    
    vector<pair<char, unsigned>> alph = HuffmanFreqTable();

    book.htree->build_lookup_table(book.htree);
    book.htree->print_tree(book.htree);
    
    
}