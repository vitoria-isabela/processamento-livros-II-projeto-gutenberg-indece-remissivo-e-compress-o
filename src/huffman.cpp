#include "huffman.h"

HuffmanTree* HuffmanTree::build_tree( vector< pair<char, unsigned> > &alph ) 
{
    // Primero, construir uma min-heap
    // E construir Nós-Folha Primeiro

    /* priority_queue fornece inserção de elementos, inspeção e remoção do elemento superior. 
    É garantido que o elemento top é o maior elemento na priority_queue , onde o
     objeto de função Compare é usado para comparações. Priority_queue não 
     permite iteração por meio de seus elementos.
    Priority_queue é um adaptador de contêiner, o que significa que é implementado 
    em cima de algum tipo de contêiner subjacente. No nosso caso, esse container sujacente é 
    o Vector of Pairs (preenchido com pares de caractere char e sua frequencia q aparece no livro)
    Armazena uma htree ordenada (min heap) num vectro<htree>, e ordena usando a função compare.
    */
    priority_queue<HuffmanTree *, vector<HuffmanTree *>, Compare > alph_heap;
    for (vector< pair<char, unsigned> >::iterator it = alph.begin();
         it != alph.end(); ++it) 
    {
        // cria um no folha passando o char e sua freq
        HuffmanTree *leaf = new HuffmanTree(it->first, it->second);
        // adicona a fplha na fila de priorid.
        alph_heap.push(leaf);
    }
    // Algoritmo de Huffman: Unir Nós Folha de Menor Frequência até que
    // sobre apenas um nó (root).
    HuffmanTree *root = nullptr;


    while (alph_heap.size() > 1)
    {
        HuffmanTree *l, *r;
        // coloca left no topo
        l = alph_heap.top();
        // função pop() é usada para remover o elemento superior da fila de prioridade
        alph_heap.pop();
        // coloca right no topo
        r = alph_heap.top();
        // função pop() é usada para remover o elemento superior da fila de prioridade
        alph_heap.pop();
        // Algoritmo de Huffman: Unir Nós Folha de Menor Frequência até que que reste apenas a raiz
        root = new HuffmanTree(0, l->cfreq + r->cfreq, l, r);
        // Coloca raiz na priorit queue
        alph_heap.push(root);
    }
    return root;
}

/**
 * Imprime os nós por ordem de comprimento: mais longos primeiro
 */
void HuffmanTree::print_tree(HuffmanTree *t) 
{
    /*  é uma fila dupla de htree e sua freq
        um deque permite a inserção e exclusão de ambas as extremidades
        são mais eficientes em comparação com os vetores
     */
	deque< pair<HuffmanTree *, int> > q;
    
    // insere na deque a htree e sua freq inicial
    q.push_back(make_pair(t, 0));
    int curlevel = -1;
    while (!q.empty()) 
    {
        // o no pai assume o primeiro da frente
        HuffmanTree *parent = q.front().first;

        int level = q.front().second;

        // remove o promeiro da frente
        q.pop_front();

        if (curlevel != level) {
            // atualiza curlevel
            curlevel = level;
            cout << "Level " << curlevel << endl;
        }
        cout << parent->cfreq << " " << parent->c << endl;

        // se tiver filho a esq, and pra esq e att level
        if (parent->left)
            q.push_back(make_pair(parent->left, level + 1));

        // se tiver filho a dir, and pra esq e att level
        if (parent->right)
            q.push_back(make_pair(parent->right, level + 1));
    }
}

/**
 * Constroi uma tabela de consulta (std::map) do (codigo do caracter) de uma  HuffmanTree, onde
 * 'code/código' é um unsigned long representando um código binário.
 */
 void HuffmanTree::build_lookup_table(HuffmanTree *htree) 
 {
    //fila dupla de pares htree-codigo binario
	deque< pair<HuffmanTree *, code_t> > q;

    q.push_back(make_pair(htree, code_t()));

    while (!q.empty())
    {
        // node : no atual
		// lc: codigo esquerda
		// rc: codigo direita
		HuffmanTree *node, *lc, *rc;

        // codigo binario
        code_t code;

        // no é o priemrio da frente
        node = q.front().first;

        // codigo é o segundo da frente
        code = q.front().second;

        // remove da fila o primeiro da frente
        q.pop_front();

        //lc assume o filho de node a esq
        lc = node->left;

        // lc assume o filho de node a dir
        rc = node->right;

		// Esta árvore de Huffman está sempre cheia
		// Ou ela tem dois filhos, ou ela não tem filhos
		// codigo de esquerda retorna 0;
		// codigo da direita retorna 1;
        if (lc) // anda ate o ultimo a esq
        { 
            code_t code_cp(code);
            q.push_back(make_pair(lc, (code.push_back(0), code)));
            q.push_back(make_pair(rc, (code_cp.push_back(1), code_cp)));
        } else // rc
        {
            // Nó Esquerdo : contém caracter
            this->lookup_table.insert(make_pair(node->c, code));
            cout << "(" << node->c << ", ";
            for (unsigned i = 0; i < code.size(); i++) 
            {
                cout << code[i];
            }
            cout << ")" << endl;
        }
    }
}

/*
 * Codifica o arquivo na tabela
 */
void HuffmanTree::encode( string str_filetoencode ) 
{
	fstream filetoencode;
	filetoencode.open( str_filetoencode, ios::in );
    // code_t é um vetor de booleanos 1 e 0
	code_t result;
	// Enquanto não chegar no fim do arquivo
    while( !filetoencode.eof() )
	{
         // caracter auxiliar
		 char caracter;
		 //pega o caracter do livro
		 filetoencode.get(caracter);
		 //vetor auxiliar b recebe o codigo binario/booleano do caracter
		 // Exemplo:
		  // O caracter a na tabela de consulta lookup
		  // tem valor 001, a->001;
		  // então b vai receber [0,0,1]		 
		  code_t b = this->lookup_table[caracter];  
         // Este Insert coloca no fim de um vetor completo 'result'
		 // Do iníco do vetor b atté o seu final
		 // gerando assim o resultado final todo em binario
		 result.insert(result.end(), b.begin(), b.end());      
	} 

	this->bitvec = result;
	this->ptr_bitvec = &result; 
}

/**
 * Procura o próximo codigo valido em um @bitter usando a Árvore de Huffman
 * Retorna a string resultante.
 * @Bitter é incrementado pelo tamanho real do próximo código que varia, e não pelo 
 * tamanho do tipo de dado que é estático.
 */
char HuffmanTree::code_lookup(code_t::iterator &biter, const code_t::iterator &biter_end,
                 const HuffmanTree *htree) 
{
    const HuffmanTree *node = htree;

    while (true) 
    {
        if (!node->left) 
        {
            // Huffman tree is full: always contains both children or none.
            break;
        }
        if (biter == biter_end) 
        {
            throw std::out_of_range("No more bits");
        }
        if (*biter) 
        {
            node = node->right;
        } else 
        {
            node =node->left;
        }
        ++biter;
    }

    return node->c;
}

/**
 * Decodifica um vetor de codigo comprimido usando a Árvore de Huffman
 * Retorna o Texto 
 */
void HuffmanTree::decode( string book,  HuffmanTree *htree )
{
	string dir2 = HDECODED;
	string dir = dir2 + book;
	fstream result;
	result.open(dir, ios::out | ios::app );

    code_t::iterator biter = this->bitvec.begin();

    while (true)
    {
        try 
        {
            result << code_lookup(biter, this->bitvec.end(), htree);
        } catch (const std::out_of_range &oor) 
        {
            // Iterator exhausted.
            break;
        }
    }
}

string HuffmanTree::bitvec_to_string() 
{
    string result;
    size_t nbits;

    nbits = bitvec.size() & 7;

    // Write the number of "hanging bits" at the first byte
    result += static_cast<char>(nbits); // at most 7

    char byte = 0;
    for (unsigned i = 0; i < this->bitvec.size(); i++) {
        unsigned boff = i & 7;
        byte |= this->bitvec[i] << boff;
        if (boff == 7) 
        {
            // Write a byte
            result += byte;
            byte = 0;
        }
    }
    if (nbits) 
    {
        result += byte;
    }
    cout << result; 
    return result;
}

// OBS: Se a codificação estiver com problema para imprimir
// Rever a lógica desta função
void HuffmanTree::bitvec_to_txt_output( string bookname ) 
{   	
    string result;
    size_t nbits;

	string dir2 = HCODED;
	string dir = dir2 + bookname;
	fstream printbinaryastxt;
	printbinaryastxt.open(dir, ios::out | ios::app );


    nbits = this->bitvec.size() & 7;

    // Write the number of "hanging bits" at the first byte
    result += static_cast<char>(nbits); // at most 7

    char byte = 0;
    for (unsigned i = 0; i < this->bitvec.size(); i++) 
    {
        unsigned boff = i & 7;
        byte |= this->bitvec[i] << boff;
        if (boff == 7) {
            // Write a byte
            result += byte;
            byte = 0;
        }
    }
    
	if (nbits) 
    {
        result += byte;
    }
    
	printbinaryastxt << result;
    
}

code_t HuffmanTree::string_to_bitvec(string packed) 
{
    code_t result;

    assert(packed.size());
    if (packed.size() == 1) 
    {
        assert(packed[0] == 0);
        return result;
    }
    unsigned nbits = packed[0];
    for (string::iterator it = packed.begin() + 1; it != packed.end(); ++it) 
    {
        for (unsigned i = 0; i < 8; i++) 
        {
            result.push_back((*it >> i) & 1);
        }
    }
    // fix the last byte
    if (nbits) 
    {
        for (unsigned i = 0; i < (8 - nbits); i++) 
        {
            result.pop_back();
        }
    }
    return result;
}


void HuffmanTree::hexdump(const unsigned char *bytes, int nbytes) 
{
    int i, j;

    for (i = 0; i < nbytes; i += 16) 
    {
        printf("%06x: ", i);
        for (j = 0; j < 16; j++) 
        {
            if (i + j < nbytes) 
            {
                printf("%02x ", bytes[i + j]);
            } else 
            {
                printf("   ");
            }
        }
        printf(" ");
        for (j = 0; j < 16; j++) 
            if (i + j < nbytes)
                printf("%c", isprint(bytes[i+j]) ? bytes[i+j] : '.');
        printf("\n");
    }
}