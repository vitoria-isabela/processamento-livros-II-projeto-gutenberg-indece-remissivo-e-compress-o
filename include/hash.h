#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "math.h"
#include "list.h"

typedef enum
{
    SHELLSORT,
    MERGESORT,
    QUICKSORT
} sorting_method;

typedef enum
{
    SUMASCII,
    POW,
    FIXEDVALUE
} hashFunction_method;

using namespace std;

class HashEntry
{
    // palavra
    string key;
    // contador dessa palavra
    unsigned int occurrences;

public:
    HashEntry(string word, unsigned int wordCounter)
    {
        this->key = word;
        this->occurrences = wordCounter;
    }

    HashEntry() {}

    bool compareByOccurrences(HashEntry &a, HashEntry &b);

    // getters e setters
    string getKey();
    unsigned int getOccurrencies();

    void setKey(string key);
    void setWordCounter(int wordCounter);
    void setOccurrencies(unsigned int occurrences);
};

class HashTable
{
    int tam;
    fstream reportlog;
    int selectorHashFunction = 0;
    // conta todas as palavras tratadas do livro
    unsigned int wordsCounter;

public:
    // Variáveis da tabela hash
    LinkedList<HashEntry> **hashTable;

    LinkedList<HashEntry> *getPosition(int index);

    HashEntry *inicializador = nullptr;

    int collisionsNumber = 0;
    // Construtor
    HashTable(int tam, int selectorHashFunction, int createreportlog);
    // Construtor
    HashTable(int tam, int selectorHashFunction);
    //Destrutor
    ~HashTable();

    void ClearHashTable();

    int returnIndexOfHashFunction(string word);

    // Hash Functions
    int hashFunctionPow(const string key);

    int hashFunctionSumAsciiValue(const string word);

    int hashFunctionWithFixValue(const string);

    // Função Busca
    HashEntry *searchKey(string word);

    // Função Remove
    void removeKey(string word);

    // Função Insere String
    void insertKey(string word);

    // Função Insere String
    // void insertKey(int key);

    // Imprime Colisões
    void displayInfo();
    void displayOnlyInfo(int num);



    // getter e setters do tamanho da tabela hash
    int getTam();

    unsigned int getWordsCounter();
};

#endif /* HASH_H */