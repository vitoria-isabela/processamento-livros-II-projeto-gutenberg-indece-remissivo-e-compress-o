#include "hash.h"
#include "config.h"
#include <math.h>

HashTable::HashTable(int tam, int selectorHashFunction)
{
    this->selectorHashFunction = selectorHashFunction;
    this->tam = tam;
    this->hashTable = new LinkedList<HashEntry> *[tam];
    for (int i = 0; i < tam; i++)
        this->hashTable[i] = nullptr;
}

HashTable::HashTable(int tam, int selectorHashFunction, int createreportlog)
{
    this->selectorHashFunction = selectorHashFunction;
    this->tam = tam;
    this->hashTable = new LinkedList<HashEntry> *[tam];
    for (int i = 0; i < tam; i++)
        this->hashTable[i] = nullptr;
    string dir = HASHTABLELOG + to_string(createreportlog) + "hashlog.txt";
    cout << "Diretorio do report: -> " << dir << endl;
    this->reportlog.open(dir, ios::out );
    
    if (this->reportlog.is_open())
    {
        cout << "Registrando Metedos da Hash" << endl;
        this->reportlog << "---------------------------- TABALA HASH INICIADA------------------------------------" << endl;
    }
    else
    {
        cout << "Nao foi possivel criar o log da hashtable" << endl;        
    }

}

HashTable::~HashTable()
{
   ClearHashTable();           
}

void HashTable::ClearHashTable()
{
    cout << "Destroi Tabela Hash " << endl;
     for (int i = 0; i < getTam(); i++)
    {
        if ( getPosition(i) != nullptr)
        {
            // acessando lista no indice
            getPosition(i)->clear();
        }
    }

}



LinkedList<HashEntry> *HashTable::getPosition(int index)
{
    if (index < getTam())
        return this->hashTable[index];
    return nullptr;
}

// escolhe qual hashFunctions ser� usado
int HashTable::returnIndexOfHashFunction(string word)
{
    int index = 0;
    switch (this->selectorHashFunction)
    {
    case 1:
        index = hashFunctionSumAsciiValue(word);
        return index;
        break;
    case 2:
        index = hashFunctionPow(word);
        return index;
        break;
    default:
        index = hashFunctionWithFixValue(word);
        return index;
        break;
    }
}
// Hash Functions
int HashTable::hashFunctionSumAsciiValue(const string word)
{
    int hash = 0;
    for (int i = 0; i < word.length(); i++)
    {
        hash += word[i];
    }

    hash = abs(hash % tam);

    return hash;
}

int HashTable::hashFunctionPow(const string key)
{
    int hashCode = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hashCode += key[i] * pow(getTam(), i);
    }

    hashCode = abs(hashCode % tam);

    return hashCode;
}

// Onde C � um multiplicador inteiro e M � um m�dulo, usado para evitar que a soma inteira transborde.
// Estes s�o geralmente escolhidos como n�meros primos. C pode ser um primo pequeno, mas M precisa ser grande,
// pois essa fun��o retornar� valores de hash no intervalo 0� M-1, que deve ser pelo menos t�o grande quanto o tamanho da tabela de hash.
int HashTable::hashFunctionWithFixValue(const string s)
{
    int C = 51;
    int M = 6999;
    int h = 0;
    for (int i = 0; i < s.length(); i++)
        h = (C * h + s[i]) % M;

    h = abs(h % tam);
    return h;
}

// getters e setters | HashEntry
string HashEntry::getKey() { return this->key; }
unsigned int HashEntry::getOccurrencies() { return this->occurrences; }

void HashEntry::setKey(string key) { this->key = key; }
void HashEntry::setWordCounter(int wordCounter) { this->occurrences = wordCounter; }
void HashEntry::setOccurrencies(unsigned int occurrences) { this->occurrences = occurrences; }

// getters e setters | HashTable
int HashTable::getTam() { return this->tam; }

unsigned int HashTable::getWordsCounter() { return this->wordsCounter; }

// Fun��o Insere palavra na tabela hash
void HashTable::insertKey(string word)
{
    this->reportlog << "Inserindo Chave ---------------------" << endl;
    // calcula hash para saber se ter� conflito
    int index = returnIndexOfHashFunction(word);

    // se a lista da posi��o index estiver
    //  vazia ser� a primeira inser��o da palavra na tabela hash
    if (this->hashTable[index] == nullptr)
    {

        this->hashTable[index] = new LinkedList<HashEntry>();
        this->reportlog << " INDEX|BUCKET de: " << word << ": " << index << endl;
        // primeira inser��o
        HashEntry newEntry(word, 1);
        // primeira iser��o de palavra no vetor
        // vectorHashEntry->push_back(newEntry);

        this->hashTable[index]->add(newEntry);
        wordsCounter++;
    }
    else
    {
        // se n�o for a primeira inser��o ou h� conflito, ou � mesma palavra
        // pesquisa na tabela hash se a palavra ja existe
        this->reportlog << " Search: Encontrar a Palavra-> " << word << endl;
        HashEntry *_search = searchKey(word);

        if (_search == nullptr)
        {

            this->reportlog << " COLISAO!" << endl;
            collisionsNumber++;
            this->reportlog << " Numero de colisoes " << collisionsNumber << endl;
            HashEntry newEntry(word, 1);
            this->hashTable[index]->add(newEntry);
            wordsCounter++;
            return;
        }

        if (_search->getKey() == word)

        {
            this->reportlog << " MESMA PALAVRA ";
            this->reportlog << "Numero Anterior Ocorrencias da Palavra: " << _search->getOccurrencies();
            int occurrences = (_search->getOccurrencies() + 1);            
            _search->setOccurrencies(occurrences);
            this->reportlog << "|| Numero ATUALIZADO Ocorrencias da Palavra: " << _search->getOccurrencies() << endl;
            //
            wordsCounter++;
        } // se nao existir, houve colisao (� uma palavra diferente, mas que ocupa o mesmo indice calculado na hashFunction)
    }
}

// Fun��o Busca
HashEntry *HashTable::searchKey(string word)
{
    // calcula o index da tabela hash
    int index = returnIndexOfHashFunction(word);
    this->reportlog << " BUSCA INICIADA : " << endl;
    this->reportlog << " INDEX DA PALAVRA : " << word << " ->: " << index << endl;
    // Construindo iterador para nevegar na lista encadeada
    // hashTable[index] � o indice da tabela e
    // en s�o os n�s da lista pertecente a esse �ndice

    // Inicio da lista pertencente ao index
    LinkedList<HashEntry> *en = hashTable[index];

    // verifica se o iterator n�o est� vazio
    if (en == nullptr)
        return nullptr;

    // Node<T> *temp = head;
    Node<HashEntry> *temp = en->getHead();

    while (temp != nullptr)
    {
        if (temp->getData().getKey() == word)
        {
            this->reportlog << " Encontrei palavra: " << word << endl;
            return temp->getDataPtr();
        }
        temp = temp->getNext();
    }
    this->reportlog << " BUSCA Finalizada: Não Exite Palavra " << endl;
    return nullptr;
}

void HashTable::removeKey(string word)
{
    this->reportlog << " Deletando paravra: " << word << "..." << endl;
    int index = returnIndexOfHashFunction(word);
    HashEntry *toDelete = searchKey(word);

    if (toDelete != nullptr)
    {
        this->hashTable[index]->remove_item(toDelete);
        this->reportlog << " Palavra Deletada! " << endl;
    }
}

void HashTable::displayInfo()
{
    this->reportlog << "---------------------------- TABALA HASH FINALIZADA------------------------------------" << endl;
    this->reportlog << " Informando o numero de colisoes: " << this->collisionsNumber << endl;
    this->reportlog << " Informando o numero de itens da Tabela: " << this->wordsCounter << endl;
    this->reportlog.close();
}

void HashTable::displayOnlyInfo(int num)
{
    fstream simpleLog;
    string dir = HASHTABLELOG + to_string(num) + "hashSimpleLog.txt";
    simpleLog.open(dir, ios::out );
    simpleLog << "---------------------------- TABALA HASH FINALIZADA------------------------------------" << endl;
    simpleLog << " Informando o numero de colisoes: " << this->collisionsNumber << endl;
    simpleLog << " Informando o numero de itens da Tabela: " << this->wordsCounter << endl;
    simpleLog.close();
}