#ifndef PROCESSALIVRO_H
#define PROCESSALIVRO_H
#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"
#include "trie.h"
#include "huffman.h"

using namespace std;




class ProcessBook
{
private:
    // tamanho do livro contado em linhas
    int bookSizeInLines;

    // arquivo do livro em txt
    string bookTxtFile;

    // nome do livro
    string bookname;

    // arquivo do livro em ascii
    fstream bookStream; // fstream do livro

    //Report dos Metodos de Ordenação
    fstream sortReport;
    
    //seletor da funcao hash
    int hashfunctselec;

    //cria diertorio para hash report log
    int createHashReportLog = 0;


public:
    // Construtores
    ProcessBook(string bookTxtFile);
    ProcessBook(string bookTxtFile, int createHashReportLog);
    ProcessBook(string bookTxtFile,  int hashfuncselect , int createHashReportLog);
    ProcessBook(string bookTxtFile, Trie *T);
    ProcessBook(string bookTxtFile, string bookname);
    ProcessBook();

    // Destrutor
    ~ProcessBook();
    //Fecha Livro
    void CloseBook();
    // Transformar texto para letras minúsculas
    void convertWordToLowercase(string &word);
    // Remove pontuações
    void removePontuation(string &word);

    void stripPunct(string &word);

    // obter numero de linhas do livro
    int getNumberLines(string bookTxtFile);

    // lê o livro e realiza o tratamento de cada palavra para inseri-la na tabela hash
    void processBookInsertsIntoHash(string bookTxtFile);
    void processBookInsertsIntoHash(string bookTxtFile, int hashfuncselect);
    void processBookHashAndTrie(string bookTxtFile, Trie *T);
    void CompressToHuffman();
    void DeCompressToHuffman();
    long GetFileSize(std::string filename);
    
    HuffmanTree *htree;


    // Passa para um vetor (a ser ordenado) as palavras da tabela hash.
    void hashToVector();

    void sortVector(sorting_method sortMethod);
   
    // exibe as 50 palavras que mais se repetem em cada
    void displaySortVector();
    
    HashTable *hashTableOfProcessBook;

    //Metodo da busca digital
    void processBookTrieIndex( Trie *T );
    
    string removerAcentos(string texto);

    // vetor usado para ordenar as listas
    HashEntry *vectorList;
    
    HashEntry* getVector50();

    HashEntry *List;
    
    // Adicionando vetores para tabelas de frequencia
    
    vector< pair<char, unsigned> > freq_table; // vetor/tabela de frequencia (caracter,frequencia)
	
    vector< pair<char, unsigned> > *ptr_freq_table = &freq_table;

    void HuffmanFreqTable();

    // vetor para armazenar todos os vetores refrentes a cada livro;
    HashEntry *vectorOfVectors;

    int bookCountLines = 0;

#pragma region getters_e_setters
    // getters
    int getSizeBookInLines();
    // setters
    void setSizeBookInLines(int bookSizeInLines);

#pragma endregion getters_e_setters
};

#endif /* PROCESSALIVRO_H */
