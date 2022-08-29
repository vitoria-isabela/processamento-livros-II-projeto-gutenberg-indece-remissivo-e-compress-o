#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <queue>
#include <map>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "config.h"

using namespace std;


// declaração de tipos

typedef vector<bool> code_t;
typedef map<char, code_t> codetable;
// Classe Árvore de Huffman
// Representa um nó de Huffman

class HuffmanTree 
{
	public:
    
	char c; // character num alfabeto
    int cfreq; // frequencia de c.
    HuffmanTree *left; //nó da esquerda
    HuffmanTree *right; //nó da direita

	map<char, code_t> lookup_table; // tabela de consulta caracter -> codigo binario
	map<char,code_t> *ptr_lookup_table = &lookup_table;
	code_t bitvec;
	code_t *ptr_bitvec = &bitvec; //vetor de bits codificados
    
	public:
    //construtor
	HuffmanTree(char c, int cfreq, HuffmanTree *left=nullptr, HuffmanTree *right=nullptr) 
	{
      this->c = c;
	  this-> cfreq = cfreq;
	  this->left = left;
	  this->right = right;
	}

	HuffmanTree( ) 
	{ }

    //destrutor
    ~HuffmanTree() {
        delete left, delete right;
    }

    //construir arvore de huffman
	HuffmanTree* build_tree( vector< pair<char, unsigned> > &alph );
    //imprime arvore de huffman por ordem de comprimento dos nós
	void print_tree(HuffmanTree *t);
	//construir tabela de consulta
	void build_lookup_table(HuffmanTree *htree);
	//codifica o arquivo
	void encode( string str_filetoencode );

	char  code_lookup(code_t::iterator &biter, const code_t::iterator &biter_end, const HuffmanTree *htree);

	void decode( string book, HuffmanTree *htree );
    	
	string bitvec_to_string();

	void bitvec_to_txt_output( string bookname );

	code_t string_to_bitvec(string packed);

	void hexdump(const unsigned char *bytes, int nbytes);
};

// Classe para comparar dois nós
class Compare {
	friend class HuffmanTree;
    public:
        bool operator()(HuffmanTree *a, HuffmanTree *b) {
            return a->cfreq > b->cfreq;
        }
    };

#endif