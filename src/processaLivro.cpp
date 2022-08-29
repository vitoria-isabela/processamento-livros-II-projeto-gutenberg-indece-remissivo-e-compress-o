#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
#include <streambuf>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <vector>
#include "config.h"
#include "trie.h"
#include "processaLivro.h"
#include "sort.h"


using namespace std;

// Construtor com seletor de função hash
ProcessBook::ProcessBook(string bookTxtFile, int hashfunctselec, int createHashReportLog)
{
    this->hashfunctselec = hashfunctselec;
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe string: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile, this->hashfunctselec);
    
  
}

// Construtor com gerador de output da hash
ProcessBook::ProcessBook(string bookTxtFile, int createHashReportLog)
{
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe string: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile);
    
  
}

//Construtor sem output
ProcessBook::ProcessBook(string bookTxtFile)
{
    cout << "Recebe string: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile);    
  
}

// Construtor Para a Trie
ProcessBook::ProcessBook(string bookTxtFile, Trie *T)
{
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe string: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    
    processBookHashAndTrie(bookTxtFile,T);   
  
}

// Construtor para a Huffman
ProcessBook::ProcessBook(string bookTxtFile, string bookname)
{
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe string: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);
    this->bookname = bookname;
    this->HuffmanFreqTable();
    this->htree = new HuffmanTree();

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
}

long ProcessBook::GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void ProcessBook::HuffmanFreqTable()
{
    map<char, unsigned> cfmap;   
   	char caracter;
	while ( !this->bookStream.eof() )
	{
        this->bookStream.get(caracter);
		if (cfmap.find(caracter) == cfmap.end())
		{
			cfmap.insert(make_pair(caracter,1));
		}
		cfmap[caracter] += 1;
	}

    for (map<char, unsigned>::iterator it = cfmap.begin();
         it != cfmap.end(); ++it) 
          {
           this->freq_table.push_back(make_pair(it->first, it->second));
         }
  
}

void ProcessBook::CompressToHuffman()
{  
         long sizeOfFile = GetFileSize(this->bookTxtFile);

        // Primeiro Passo: Construir a Tabela de Frequencia
        // Ela foi construida no construtor: HuffmanFreqTable()
        // @this->freq_table
        // obs: não está sendo feito nenhum tipo de tratamento de caracter
        // obs: a freq de caracter é feita por livro;      
        
        // Segundo Passo: Dado uma tabela de frequencia, construir uma 
        // Árvore de Huffman @htree;
        this->htree = this->htree->build_tree( this->freq_table );
        //Terceiro Passo: Dado uma Árvore de Huffman, montar a tabela de consulta;
        this->htree->build_lookup_table(this->htree);
        // Quarto Passo: Dado uma tabela de consulta, fazer o
        // Encoding/Codificação do livro;
        // obs: o livro foi lido char by char uma vez para montar a 
        // tabela de frequencia e está sendo lido agora outra vez
        // para ser codificado;
        this->htree->encode(this->bookTxtFile);
        cout << "Taxa de compressao deste arquivo: "
             << (this->htree->bitvec.size() + 7) / 8 << "/" << this->htree->bitvec.size() << " or "
             << ((float)(this->htree->bitvec.size() / 8) / sizeOfFile) << ") = " << ((float)(this->htree->bitvec.size() / 8) / sizeOfFile)*100 << "% " <<endl;

        //Quinto Passo: Imprimir na Pasta Huffman/Coded um txt
        //que emula um arquivo binário
        this->htree->bitvec_to_txt_output(bookname);     

       
}

void ProcessBook::DeCompressToHuffman()
{  
       
       this->htree->decode(this->bookname, this->htree);

       
}

void ProcessBook::CloseBook()
{
    this->bookStream.close();   
  
}

ProcessBook::ProcessBook() {}

// Destrutor do livro
ProcessBook::~ProcessBook() 
{
   cout << "Destroi Livro " << bookTxtFile << endl;
   this->bookStream.close();

   if ( this->hashTableOfProcessBook == nullptr )
   {
   delete this->htree;
   cout << "Huffman Destruída!" << endl;
   }
}

// Converte uma palavra
void ProcessBook::convertWordToLowercase(string &word)
{
    for (size_t j = 0; j < word.length(); ++j)
    {
        word[j] = tolower(word[j]);
    }
}

// Remove as pontuações, se houver na palavra
void ProcessBook::removePontuation(string &word)
{
    word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
    
}

// string ProcessBook::removerAcentos(string str)
// {
  
//    byte[] bytes = System.Text.Encoding.GetEncoding("iso-8859-8").GetBytes(str);
//    return System.Text.Encoding.UTF8.Getstring(bytes);
// }
//************************************************************************************************************

// Esta função faz o tratamento da acentuação 
// Acentos são atribuidos valores com sinal
// tirando o sinal podemos fazer uma correlação
string ProcessBook::removerAcentos(string texto)
{
    fstream report_pontuation_removal;
    string dir = OUTPUT;
    string dir2 ="remover_acentos.txt";
    dir = dir + dir2;
    report_pontuation_removal.open(dir, ios::out | ios::app );  
    report_pontuation_removal <<  "A palravra: " << texto << endl;
    
    for (int i = 0; i <texto.length(); i++)
    {       
        
        if ( texto[i] < 0)
        {
         report_pontuation_removal << " --------------------------------- " << endl;
         report_pontuation_removal << " Possui Acento, Iniciando Remoção " << endl; 
         report_pontuation_removal << " --------------------------------- " << endl; 
         unsigned char one = texto[i];
         unsigned char two = texto[i+1];
         int sum = one + two;
         report_pontuation_removal << "Valor da soma : " << sum << endl;
         
         switch (sum)
         {            
         
         // Caso 'Ç'
         case 330:
           texto[i] = 'c';      
           texto.erase( texto.begin() + i+1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;           
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;           
           break;    
         
         
         // Caso 'ç'
         case 362:
           texto[i] = 'c';      
           texto.erase( texto.begin() + i+1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;           
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;           
           break;
        
        // Caso 'À'
         case 323:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Á'
         case 324:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           break;
        
        // Caso 'Â'
         case 325:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Ã'
         case 326:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;  
           break;
        
        // Caso 'Ä'
         case 327:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           break;

         // Caso 'È'
         case 331:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           break;
        // Caso 'É'
         case 332:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Ê'
         case 333:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           break;
        
        // Caso 'Ë'
         case 334:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break; 
        
        // Caso 'Ì'
         case 335:
           texto[i] = 'i';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Í'
         case 336:
           texto[i] = 'i';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Î'
         case 337:
           texto[i] = 'i';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;

        // Caso 'Ï'
         case 338:
           texto[i] = 'i';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;
        
        // Caso 'Ò'
         case 341:
           texto[i] = 'o';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;

        // Caso 'Ó'
         case 342:
           texto[i] = 'o';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;     

        // Caso 'Ô'
         case 343:
           texto[i] = 'o';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;

        // Caso 'Õ'
         case 344:
           texto[i] = 'o';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break; 

        // Caso 'Ö'
         case 345:
           texto[i] = 'o';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;  

        // Caso 'Ù'
         case 348:
           texto[i] = 'u';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;    

        // Caso 'Ú'
         case 349:
           texto[i] = 'u';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;     

        // Caso 'Û'
         case 350:
           texto[i] = 'u';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;    

        // Caso 'Ü'
         case 351:
           texto[i] = 'u';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;
           break;                                                                                                    
               
        
        // Caso 'à'
         case 355:
           texto[i] = 'a';
           texto.erase( texto.begin() + i +1 ,texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
         
           break;
        // Caso 'á'
        case 356:
           texto[i] = 'a';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           
           break;
        // Caso 'â'
        case 357:
           texto[i] = 'a';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        // Caso 'ã'
        case 358:
           texto[i] = 'a';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
       
           break;
        
        // Caso 'ä'
        case 359:
           texto[i] = 'a';
           texto.erase( texto.begin() + i, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
           break;
        
        // Caso 'è'
        case 363:
           texto[i] = 'e';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        
        // Caso 'é'
        case 364:
           texto[i] = 'e';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
      
           break;

        // Caso 'ê'
        case 365:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1 , texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;

        // Caso 'ë'
        case 366:
           texto[i] = 'e';
           texto.erase( texto.begin() + i +1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        
        // Caso 'ì'
        case 367:
           texto[i] = 'i';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
          
           break;
        
        // Caso 'í'
        case 368:
           texto[i] = 'i';
           texto.erase( texto.begin() + i +1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 

           break;

        // Caso 'î'
        case 369:
           texto[i] = 'i';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
    
           break;
        
        // Caso 'ï'
        case 370:
           texto[i] = 'i';
           texto.erase( texto.begin() + i + 1 , texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        
        // Caso 'ò'
        case 373:
           texto[i] = 'o';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 

           break;
        
        // Caso 'ó'
        case 374:
           texto[i] = 'o';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 

           break;
        
        // Caso 'ô'
        case 375:
           texto[i] = 'o';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        
        // Caso 'õ'
        case 376:
           texto[i] = 'o';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
          
           break;
        
        // Caso 'ö'
        case 377:
           texto[i] = 'o';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
       
           break;
        
        // Caso 'ù'
        case 380:
           texto[i] = 'u';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
      
           break;
        
        // Caso 'ú'
        case 381:
           texto[i] = 'u';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
        
           break;
        
        // Caso 'û'
        case 382:
           texto[i] = 'u';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
         
           break;
        
        // Caso 'ü'
        case 383:
           texto[i] = 'u';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Acento Removido com sucesso  " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;    
           break;
        // Caso '-' ou '''
        case 354:
           texto.erase( texto.begin() + i , texto.begin() + i + 3);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Tentativa de remover a barra ou apostrofe " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl;    
           break;
                 
        // Caso 'æ'
        case 361:
           texto[i] = 'a';
           texto.erase( texto.begin() + i + 1, texto.begin() + i + 2);
           report_pontuation_removal << texto << endl;
           report_pontuation_removal << " Caractere especial removido com sucesso! " << endl; 
           report_pontuation_removal << " --------------------------------- " << endl; 
          
           break;

         default:
            report_pontuation_removal << " Caso Não Mapeado !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111 " << endl; 
            report_pontuation_removal << " Caracter Não Mapeado na posição " << i << " da palavra " << texto;
            report_pontuation_removal << " Valor do caracter não mapeado: " << sum << endl;
            report_pontuation_removal << " --------------------------------- " << endl;
            break;
         }
        
        }       
    }

    return texto;
}


// Obtem o numero de linhas do livro
int ProcessBook::getNumberLines(string bookTxtFile)
{
    int numberOfLines = 0;
    this->bookSizeInLines = numberOfLines;
    string line;
    ifstream bookInputstream;

    bookInputstream.open(bookTxtFile, ios::in);

    if (!bookInputstream.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return -1;
    }

    if (bookInputstream.is_open())
    {
        while (!bookInputstream.eof())
        {
            getline(bookInputstream, line);
            cout << line << endl;
            numberOfLines++;
        }
        bookInputstream.close();

        numberOfLines--; // debugar essa linha
        return numberOfLines;
    }
    else
        return 0;
}

// lê o livro e realiza o tratamento de cada palavra para inseri-la na tabela hash
void ProcessBook::processBookInsertsIntoHash(string bookTxtFile)
{
    // cria uma tabela hash
    HashTable *hashTable = new HashTable(50001, 3);
    this->hashTableOfProcessBook = hashTable;

    ifstream arq;
    arq.open(bookTxtFile, ios::in);

    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        bookCountLines++;
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);
            tokenStopWord = removerAcentos(tokenStopWord);

            if (tokenStopWord.length() > 3)
                // insere palavra na tabela hash
                hashTableOfProcessBook->insertKey(tokenStopWord);               
        }
    }
    hashToVector();
    
}

void ProcessBook::processBookInsertsIntoHash(string bookTxtFile, int hashfuncselect)
{
    // cria uma tabela hash
    HashTable *hashTable = new HashTable(50001, hashfuncselect, this->createHashReportLog);
    this->hashTableOfProcessBook = hashTable;

    ifstream arq;
    arq.open(bookTxtFile, ios::in);

    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);
            tokenStopWord = removerAcentos(tokenStopWord);


            if (tokenStopWord.length() > 3)
                // insere palavra na tabela hash
                hashTableOfProcessBook->insertKey(tokenStopWord);
        }
    }
    
    hashTableOfProcessBook->displayInfo();
    hashTableOfProcessBook->displayOnlyInfo(hashfuncselect);
}

void ProcessBook::processBookHashAndTrie(string bookTxtFile, Trie *T)
{
    fstream rindex;
    string dir = OUTPUT;
    string dir2 ="whatsgoingon.txt";
    dir = dir + dir2;
    rindex.open(dir, ios::out ); 
    // cria uma tabela hash
    HashTable *hashTable = new HashTable(50001,3);
    string pause;
    this->hashTableOfProcessBook = hashTable;
    bookCountLines = 0;

    rindex << "bookCountLines Inicializado: " << bookCountLines << endl;
       
    ifstream arq;
    arq.open(bookTxtFile, ios::in);

    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        bookCountLines++;
        rindex << "bookCountLines Aumentado ++: " << bookCountLines << endl;
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);
            tokenStopWord = removerAcentos(tokenStopWord);
            if (tokenStopWord.length() > 3)
                // insere palavra na tabela hash
            {
                hashTableOfProcessBook->insertKey(tokenStopWord);
                tokenStopWord = removerAcentos(tokenStopWord); 
                rindex << "Palavra: ->" << tokenStopWord << endl;            
                rindex << "Linha Atual: ->" << bookCountLines << endl;
                T->insert(tokenStopWord, bookCountLines);               
            }   
        }
    }
    hashToVector();
}

// TRIE function: Realiza a busca no livro para calcular o indice remissivo
void ProcessBook::processBookTrieIndex( Trie *T )
{
    ifstream arq;
    arq.open(bookTxtFile, ios::in);
    bookCountLines = 0;
     
    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            bookCountLines++;
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);
            tokenStopWord = removerAcentos(tokenStopWord);


            if (tokenStopWord.length() > 3){
                // insere palavra na tabela hash
                cout << "Palavra a ser procurada: " << tokenStopWord << endl;
                LinkedList<int> *aux = T->search(tokenStopWord);
                cout << &aux << endl;
                aux->add(bookCountLines);
                
            }             
        }
    }
}

bool compareByOccurrences(HashEntry &a, HashEntry &b)
{
    return a.getOccurrencies() > b.getOccurrencies();
}

// Passa para um vetor (a ser ordenado) as palavras da tabela hash.
void ProcessBook::hashToVector()
{
    // contador de posições de todas as listas em todos os buckets
    int counter = 0;
    int sizeOfhashTableOfProcessBook = hashTableOfProcessBook->getWordsCounter();
    // Cria uma lista
    LinkedList<HashEntry> *hashEntry;

    HashEntry *auxVector = new HashEntry[sizeOfhashTableOfProcessBook];

    // percorre tabela hash
    for (int i = 0; i < hashTableOfProcessBook->getTam(); i++)
    {
        // verifica se posição i do bucket é nula
        if (hashTableOfProcessBook->getPosition(i) != nullptr)
        {
            // acessando lista no indice
            hashEntry = hashTableOfProcessBook->getPosition(i);

            // percorre a lista do bucket no indice j
            for (int j = 0; j < hashEntry->length(); j++)
            {
                // verifica se a lista do bucket na posição j está vazio
                if (!hashEntry->empty())
                {

                    // adicionando os dados da lista, naquele indice, no vetor
                    auxVector[counter] = hashEntry->get(j);
                    // incrementa o contador para ir para as próximas posições do vetor
                    counter++;
                }
            }
        }
    }
    this->vectorList = auxVector;
}

void ProcessBook::sortVector(sorting_method sortMethod)
{
   switch (sortMethod)
    {
    case MERGESORT:
        merge_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;   
    case QUICKSORT:
        quick_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;
    case SHELLSORT:
        shell_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;
    }
    
    displaySortVector();

}

void ProcessBook::displaySortVector()
{       
    string dir = SORTMETHOD + to_string(this->createHashReportLog) + "sort_results.txt";
    cout << "Diretorio do report: -> " << dir << endl;
    this->sortReport.open(dir, ios::out | ios::app );    
    
    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;
    this->sortReport << "IMPRIMINDO AS 50 PALAVRAS DE MAIORES OCORRENCIAS DE CADA VETOR ORDENADO: " << endl;
    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;
   
    
    for (int i = 0; i < 50; i++)
    {
        this->sortReport << endl
        << " Numero de Ocorrencias da palavra \"" << this->vectorList[i].getKey() << "\": " << this->vectorList[i].getOccurrencies() << endl;
        
    }


    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;

}

HashEntry* ProcessBook::getVector50()
{
    fstream printSortBook;
    

    HashEntry* vectorOut = new HashEntry[50];
    shell_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences);
    
    for (int i = 0; i < 50; i++)
    {
       vectorOut[i] = this->vectorList[i];
    }
     
    string dir = CASO4 + to_string(this->createHashReportLog) + "book_words.txt";
    cout << "Diretorio do report: -> " << dir << endl;
    printSortBook.open(dir, ios::out | ios::app );    
    
    printSortBook << "---------------------------------------------------------------------------" << endl;
    printSortBook << "IMPRIMINDO AS 50 PALAVRAS DE MAIORES OCORRENCIAS DE CADA VETOR ORDENADO: " << endl;
    printSortBook << "---------------------------------------------------------------------------" << endl;
   
    
    for (int i = 0; i < 50; i++)
    {
        printSortBook << endl
        << " Numero de Ocorrencias da palavra \"" << vectorOut[i].getKey() << "\": " << vectorOut[i].getOccurrencies() << endl;
    }
    printSortBook << "---------------------------------------------------------------------------" << endl;
    printSortBook.close();    
    return vectorOut;
}