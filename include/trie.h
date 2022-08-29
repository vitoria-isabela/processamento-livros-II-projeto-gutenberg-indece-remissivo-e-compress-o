
#ifndef TRIE_H
#define TRIE_H

#include<bits/stdc++.h>
#include "list.h"

# define CHILDREN 36

using namespace std;
// Trie node
class trie;
class TrieNode
{    
    friend class Trie;
    public:
        TrieNode() : is_word(false) {
            for (int i = 0; i < CHILDREN; i++) {
                children[i] = nullptr;
            }
        }

        TrieNode* getChild(char c) {
            return children[c - 'a'];
        }

        bool isEndOfWord() {
            return is_word;
        }

        bool isLastNode()
        {
            for (int i = 0; i < CHILDREN; i++)
            {
                if (children[i])
                    return false;
            }
            return true;
        }

        LinkedList<int> thelines;

    private: 
        bool      is_word;
        TrieNode* children[CHILDREN];
};

class Trie {
    public:
        Trie();
        ~Trie();
        void insert(string word);
        void insert(string word, int lineNumber);
        bool virtualSearch(string word);
        LinkedList<int> *search(string word);        
    private:
        TrieNode* root;
        void deallocate(TrieNode* node);
};

#endif /* TRIE_H */
