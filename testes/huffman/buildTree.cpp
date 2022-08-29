#include <vector>
#include "huffman.h"
#include <fstream>

using namespace std;

// vector<bool> é como um contêiner padrão especial onde cada bool usa apenas um bit de espaço
 //em vez de um byte como um bool normal faria (implementando um tipo de "bitset dinâmico"). 
 //Em troca dessa otimização, ele não oferece todos os recursos e interface de um contêiner padrão normal.
typedef vector<bool> code_t;

/* Em um map<char, code_t> , os valores de chave char geralmente são usados ​​para classificar e identificar exclusivamente os caracteres do livro,
 enquanto os valores mapeados armazenam o codigo binario associado a essa chave . Os tipos de chave e valor mapeado podem diferir
  e são agrupados no tipo de membro value_type , que é um tipo de par que combina ambos
  */
typedef map<char, code_t> codetable;

// Vector é um array dinâmico
// Vector of Pairs é um array dinâmico preenchido com pares de caractere char e sua frequencia q aparece no livro;
vector< pair<char, unsigned> > HuffmanFreqTable()
{
    fstream bookStream;

    bookStream.open(BOOK9, ios::in);

    vector< pair<char, unsigned> > freq_table;

    // armazena os pares chave-valor, onde chave é o caractere char e o valor é a freq do char;
    map<char, unsigned> cfmap;   
   	char caracter;
	while ( !bookStream.eof() )
	{
    bookStream.get(caracter);

    // se o cmap procurado for o ultimo do cfmap, adiciona um à freq desse char.
		if (cfmap.find(caracter) == cfmap.end())
		{
			cfmap.insert(make_pair(caracter,1));
		}
    // senao adiciona aquele caractere que antes nao existia na cfmap;
		cfmap[caracter] += 1;
	}

    // Retorna um iterador do primeiro elemento no contêiner do cfmap ate o ultimo
    for (map<char, unsigned>::iterator it = cfmap.begin();
         it != cfmap.end(); ++it) 
         {
          // adicionar um vetor de par a um vetor de pares existente
           freq_table.push_back(make_pair(it->first, it->second));
         }
  // vector< pair>
  return freq_table;
}

//Esse teste constrói uma arvore de huffman
int main(int argc, char *argv[])
{
    vector<pair<char, unsigned>> alph = HuffmanFreqTable();

    HuffmanTree *hftree = new HuffmanTree();

    hftree->build_tree(alph);
}