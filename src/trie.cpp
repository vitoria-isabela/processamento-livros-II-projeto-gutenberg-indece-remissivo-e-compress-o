#include "trie.h"
#include <iostream>
#include <string>

using namespace std;

Trie::Trie() 
{
    root = new TrieNode();
}

void Trie::insert(string word) 
{
    TrieNode* cur = root;
    int index = 0;
    for (char c: word) {
        if(c > 47 && c < 58 )
        {
            index = c - 48 + 27;
            if (!cur->children[index]) 
            {
                cur->children[index] = new TrieNode();
            }
        }
        else
        {
            index = c - 'a';
            if (!cur->children[index]) 
            {
                cur->children[index] = new TrieNode();
            }
        }
        cur = cur->children[index];
    }
    cur->is_word = true;
}

void Trie::insert(string word, int lineNumber) 
{
    TrieNode* cur = root;
    cout << "INSERINDO A PALAVRA | " << word << " | DA LINHA | " << lineNumber << " | NA TRIE" << endl;
    int index = 0;
    for (char c: word) {
        if(c > 47 && c < 58 )
        {
            index = c - 48 + 27;
            if (!cur->children[index]) 
            {
                cur->children[index] = new TrieNode();
            }
        }
        else
        {
            index = c - 'a';
            if (!cur->children[index]) 
            {
                cur->children[index] = new TrieNode();
            }
        }
        cur = cur->children[index];
    }
    cur->is_word = true;
    cout << "Adicionado na linha: " << lineNumber << endl;
    cur->thelines.add(lineNumber); 
}



LinkedList<int>* Trie::search(string word) 
{
    cout << "Procurando a palvra: " << word << endl;
    TrieNode* cur = root;
    int index = 0;
    for (char c: word) 
    {
        if(c > 47 && c < 58 )
        {
            index = c - 48 + 27;
            if (!cur->children[index]) 
            {
               exit(1);
            }
        }
        else{        
        index = c - 'a';
        if (!cur->children[index]) {
            exit(1);
        }
        
        }
        cur = cur->children[index];
      
    }
    if(cur->is_word)
    {
        return &cur->thelines;
    } else 
    {
        cout << "Não é uma palavra valida " << word << endl;
        exit(-1);
    }
}
 
void Trie::deallocate(TrieNode* node) 
{
    for (int i = 0; i < CHILDREN; i++) {
        if (node->children[i]) {
            deallocate(node->children[i]);
        }
    }
    delete node;
}

Trie::~Trie() {
    deallocate(root);
}