<div style="border: solid 1px; width: fit-content; padding: 0px 20px 20px 20px; border-color: rgba(234,234,234,1)">

  >  For better navigability, read this file in the "Wiki" section of github.
  
#### Contents
- [Overview](#overview)
- [Scope](#scope)
- [Technical Decisions](#technical-decisions)
- [Project Execution](#project-execution)
- [Final Considerations](#final-considerations)
- [Team](#team)
  
</div>

## Overview

During the Data Structure II - DCC012B course, we developed a program that performs the reading, processing and manipulation of a collection of books: through such implementations it was possible to capture the 50 words that are most repeated in each book, as well as the 50 most repeated words among all the books in the collection. In short, everything was possible through the manipulation of three TADs: one for manipulation of linked lists (TAD List), another for manipulation of Hash functions (TAD hash), a TAD for manipulation of Digital Trie Search (TaD Trie), a TAD for handling huffman compression (TAD Huffman), a TAD for handling LZW Compression (TAD LZW) and the last for handling Books (TAD ProcessBook), which were converted to TXT files (TAD book). In addition, the algorithms were designed to achieve good performance, being mapped by performance indicators, in addition to ensuring their complete functioning through unit tests. For more details on technical decisions, see Technical Decisions.

<br>

## Scope

The work was all developed through 3 main TADs:
- TAD Processes Book:
Contains the basic operations for handling words from the book. All books that are in the database will be read, being fully converted into LowerCase, any punctuation removed, as well as all prepositions, articles and other "StopWords" - term used to refer to words that should not be mapped in the table Hash and that do not refer to valid words, such as verbs, proper and common nouns. Once handled, all "valid" words will be inserted into the Hash table.

- TAD List:
The project specifies the implementation of the Linked List data structure to handle the Hash Table collisions.
To simplify the project, therefore obtaining better results, the best course of action would be to implement
a class called HashEntry that has a pointer to the next HashEntry. In that way, it would act like both an Entry 
for the Hash Table and a Linked List alike structure, rather than storing the Entry in another place, overcomplicating the access methods without reason. The collision would have been handled the same way.
Due to the project specification, this was not allowed, in our understanding.
The TAD List consists in only a header file, since its a Template and acording to the documentation of c++, separating then results in undefined references errors, as seen first hand by this team.

- TAD Hash:
  Under the hood, hash tables are arrays that come with a hash function, let’s say we want to store “foo” in our hash table. We will pass this to our hash function which will generate a number for us. We will use that number as our index to store “foo” in our hash table. A good hash function must return the same number for the same input every time otherwise we would access random parts of the hash table. using simple linked lists will cost you memory and make you not worry about collision. If you want something, you have to commit to something else. Of course, using simple linked lists would theoretically mean O(n) lookup time. After we declare a simple linked list and use it in our hash table, we will see how in the real world we have better lookup time than O(n).

- TAD Trie: This TAD was used to implement the index. Each branch of the Trie tree represents a possible brace character. We need to mark the last node of each key as the end of the word node. A Trie isEndOfWord node field is used to distinguish the node as the end of the word node. Through this TAD it would be possible to build a list with all the lines in which a given word occurs, this by consulting the TAD ProcessBook methods, which have already been implemented in part 1 of this work.

- TAD Huffman: The purpose of this TAD is to assign variable-length codes to input characters (char by char), with the assigned code lengths being based on the frequencies of the corresponding characters. The most frequent character receives the lowest code and the least frequent character receives the highest code. Finally, it would be possible to calculate the compression ratio of the Huffman compression algorithm, which would be given through the ratio of the size of the binary code of the txt file.

- TAD LZW: LZW compression is the compression of a file into a smaller file using a table-based lookup algorithm invented by Abraham Lempel, Jacob Ziv, and Terry Welch. Two commonly used file formats in which LZV compression is used are the GIF image format served on websites and the TIFF image format. LZW compression is also suitable for compressing text files.
A specific LZW compression algorithm takes each input sequence of bits of a certain length (e.g. 12 bits) and creates an entry in a table (sometimes called a "dictionary" or "codebook") for that pattern of specific bits, consisting of the pattern itself and a shorter code. As the input is read, whatever pattern has been read before results in the shorter code being replaced, effectively compressing the total amount of input to something smaller. Unlike previous approaches known as LZ77 and LZ78, the LZW algorithm includes the lookup code table as part of the compressed file. The decoding program that unzips the file is able to build the table itself using the algorithm while processing the encoded input.

<br>

## Technical Decisions

Below, all the technical decisions were mapped, as well as the path we took for each of them.

**1)How to process "StopWords"?** 

As there are a much smaller number of 3-character "StopWords", we chose to define them "by hand" in a RemoveConstStopWords() method. An important observation is that it is impossible to map all the “stopWords” of the Portuguese language, given the diversity and breadth of Portuguese grammar. But, through tests with a diverse collection of books, it was possible to analyze which “StopWords” were more repeated (not being mapped by the treatment methods and being inserted in the Hash Table) and thus, adding them in the RemoveConstStopWords() method.
Thus, the vast majority of "StopWords" were removed before the book was entered into the Hash Table.

<br>

**2)How to choose Hash table size?**

the size of the hash table was chosen based on two factors: first, we chose a hash function that has the best performance, which implies a larger hash table size and fewer collisions. Secondly, tests were performed with different sizes of txt files, in order to have a good comparison of the hash table size with the number of collisions. It was also taken into account that the size of the hash table should be a prime number.

<br>

**3)How and which files were unit tested?**

We ensure that all routines that were called in the main function as well as in the main and auxiliary TADs have been unit tested. In addition to these, most (if not all) routines that were not called - not needing to be tested - also had unit tests created. Each TAD has its unit tests mapped in a separate folder for better organization of the test folder. Each test also has a brief description of which routine it is testing and its objectivity.

<br>

**4)What sorting methods were mapped?**

Already predefined to be mapped is QuickSort(), the chosen one that was seen in the classes taught by the teacher was MergeSort() and the free choice method was ShellSort():
ShellSort is an in-place comparison sort. It is mainly the variation of sorting by exchange (bubble sort) or sorting by insertion (insertion sort). This algorithm avoids large shifts as in the case of insertion sort, if the smaller value is to the far right and has to be moved to the far left. The idea of ​​shell sort is to allow exchange of far items. This spacing is termed as interval or gap. ShellSort is more efficient compared to Insertion Sort or Bubble sort especially when –

- Smaller value elements are towards the end of the array/list;
- Large sized array/list;
- Efficiency depends on how we select the GAP/interval.

<br>

**5)And the performance of the processBookInsertsIntoHash()?**

Although the processBookInsertsIntoHash() method does not have a good performance (each line is one by one), the book was only read once, and we must take into account that the other methods have a good performance because they are part of the TAD HashTable.
<br>

<br>

**6)What was the choice to handle the processing of the book, all the way up to inserting it into the Hash table?**

After reading the book line by line (getting each word of each line separately) and also performing the treatment of each word, we chose to create an insertion method (insertKey() ) that receives each of these words and inserts it into the hash table. After this treatment, a method was created that performs the insertion of the words contained in the hash table in a vector. Finally, in this vector, the ordering methods were called, making the first 50 positions of each book vector the words that have the most frequency.

<br>

**7)How and what was the hash function chosen?**

Among the three functions implemented, the one chosen to run the code was hashFunctionWithFixValue(). In it we have the variable C which is an integer multiplier and M which is a module, used to prevent the entire sum from overflowing. These are usually chosen as prime numbers. C can be a small prime, but M must be large,
 as this function will return hash values ​​in the range 0…M-1, which must be at least as large as the size of the hash table. This approach was chosen, being the best option, as using multipliers causes each character position to “count” differently in the final sum. Finally, it is worth mentioning that our "Almost Perfect Hash" was calculated through a combination of a good size of the hash table with the chosen hash function: through tests with different file sizes it was possible to adjust the best size of the hash table, so that there aren't too many unfilled spaces in the table and there aren't too many collisions.

**8)Why can't I separate my template class definition from its declaration and put it inside a .cpp file?**

A template is not a class or a function. A template is a "pattern" that the compiler uses to generate a family of classes or functions.
In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to "fill in" the template. For example, if you're trying to use a Foo<int>, the compiler must see both the Foo template and the fact that you're trying to make a specific Foo<int>.
Your compiler probably doesn't remember the details of one .cpp file while it is compiling another .cpp file. This is called the "separate compilation model."
  > For more details, visit [this link](https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl).
   
<br>

**9)I want to test the project with a book of mine. How can I do this?**
  
The cmake needs some tweaking so it can compile the project using your book. First, let's understand a little more: the :file_folder: input contains all the books that will be read and processed by the program. Therefore, it is necessary that you insert your book(s) in this folder for the project to use it. (If you want to keep the folder naming standard, insert your book in .txt format and prefixed with book[number_to_follow_in_folder].txt.
> Note: for better program operation, eliminate the header part of the [Project Gutenberg](https://www.gutenberg.org/browse/languages/pt) books, as shown in the following example:

  ![image](https://user-images.githubusercontent.com/65192005/175754615-a007cfe6-fce8-40a6-b47c-74b4cb81a9fa.png)
  
**- You will need to add your book to some cmake configuration files:**
  
  <br>
  
- :clipboard: config.h:
  Add the '#define' of the path of the folder where your book is located, that is, the input folder. See the examples:
  
![image](https://user-images.githubusercontent.com/65192005/175754747-fcf9591b-de4d-4136-b28e-4baf1b4e420f.png)
  
  <br>
  
![image](https://user-images.githubusercontent.com/65192005/175754765-e9bdb18a-9211-4386-b1eb-e84c8f3b7c55.png)
- :clipboard: config.h.in:
  
  Adds the cmake definition tag as shown in the following example, enclosing the .txt file name between "@":
  
  ![image](https://user-images.githubusercontent.com/65192005/175754829-a64c70a0-a9bb-419c-9328-8f0c5ce517db.png)
  
  <br>
  
And in the tests that you want to include your book, call the constructor of the class processes books as follows:
  
  ![image](https://user-images.githubusercontent.com/65192005/175754905-afb00cbf-9178-4244-be21-313c00527b04.png)
  
  <br>

  That way, the inclusion of your book to be tested in the project will be configured!
  
  **10) When running the CompressToHuffman() unit test the result in the output was "Segmentation Fault". Why did this happen?**

The method removeAccents() of the TAD ProcessBook, treats characters that do not have a specific value in the ascii table, either because such a character occurs by the union of two other characters or for some other reason. Despite the large collection of accents that we deal with, there may still be a character that is not mapped in the book to be tested. Therefore, the solution is to identify in the file removeAcentos.txt (output file of the unit test execution) the last char character that was read and in which line it is. That way, you can go to this line where that character is and remove that accented character, replacing it with the unaccented character.
  
## Project Execution
> Among other options, the steps below refer to the execution of the program via the command line through the terminal.

#### Build the project

To build the project's Cmake, run the following commands:

> Build the build folder
```
cmake -B build
```

> Run the build
```
cmake --build build 
```

> To enter the build folder, run
```
cd build 
```

> Inside the build folder, just run the command
```
make
```

#### Execution of Unit Tests

In each test folder, which are inside the :file_folder: tests, there are tests referring to each TAD. For example, inside the :file_folder: tests/hash folder are the tests referring to the TAD hash methods that have passed tests.
To run the methods separately from the TAD Hash, use the command: 

<br>

``` 
./testes/hash/[nameOfTestHere]
``` 
> Don't forget to enter the build folder to run the tests! For this use the command
```
cd build
```

An example is below where the hashTest1.cpp test will be run:

![image](https://user-images.githubusercontent.com/65192005/175292230-fe67d0ad-4c48-47d9-a717-b040c6110dba.png)

<br>


To run the functions separately from the TAD List, use the command:

<br>

```
./testes/list/[nameOfTestHere]
```
<br>

To run the functions separately from the TAD Livro, use the command:

<br>

```
./testes/livro/[nameOfTestHere]
```
  
To run the functions separately from the TAD Huffman, use the command:

<br>

```
./testes/huffman/[nameOfTestHere]
```
  
To run the functions separately from the TAD Trie, use the command:

<br>

```
./testes/trie/[nameOfTestHere]
```
  
To run the functions separately from the TAD LZW, use the command:

<br>

```
./testes/lzw/[nameOfTestHere]
```
  
> To run all tests once, inside the build folder, run the following command in the terminal:

```
ctest
```
![image](https://user-images.githubusercontent.com/65192005/175294610-b4130abb-280b-458c-9c3a-2bc9c2140edb.png)


#### General Execution:

This project is divided in 4 Main Tests:

The First Test is the result of testing all of the tests in the directory ./testes, especially the ones in .test/hash. They demonstrate that the Hash Table is operational.

The Second Test is Called TestSwitchHash, it will read the book1.txt from the input folder, and create 3 hash tables
with 3 different hash funtions. The results of the test is in the folder output/Hash. The first number is the hash function that was used. The "Simple" in the name of the file will report just the collisions number and the number different words in book1.txt, rather than the full report of every method called.

The Third Test is Called TestSort, it will read the book1.txt from the input folder, and aplly 3 sorting methos to a vector built from a hashtable: QuickSort, ShellSort and MergeSort. The log will be avilibe on the output/Sort folder. The first number represents a different sorting method. Since Shell Short was the best sorting method in the result of this test, he was chosen for the next one. Delete the logs before executing this test again.

The Fourth and last test is called Test10books, it will read all 10 books from input, select the 50st most used words of wich one using Shell Sort, print them in th output/Sort/caso4 folder, each first number corresponds to the book number it came from. After that, it will produce, using the Shell Sort, the "mostusedword.txt" the contains the 50st most used words of all the 10 books.
  
 > Pay attention to the relative path of the output files, as they will correspond to their respective test. For example: when executing the HuffmanCompress unit test, the generated output file will be in the Output >> Huffman >> Coded path.

## Final Considerations

We thank our professor José Jeronimo Camata for his help and clarification of doubts during the development of this project. We would also like you, the teacher, to evaluate our project with care and zeal: it was organized and produced in a way that the code was properly commented, with well-named variables, a wide coverage of unit tests, and there was also a good use of the git technology (there was good versioning of code distributed across branches, proper use of Pull Requests, merges and commits features and also good use of "Projects" to work better with a team so that every member was kept up to date on development from the project). We consider that our work was very good, but not perfect: we faced some challenges during the development of the project, sometimes taking a long time to solve some problems. We ask that you take into account in the Functionality note (which occupies 50% of the total) all our effort and dedication throughout the development, in which the final result does not matter, also considering that the constancy of a clean development gradually leads to perfection: smile: :blush:

<br>

## Team
The team responsible for the development of this project was formed by the students of the DCC012B discipline at UFJF:
- Allan Henriques Teixeira Albuquerque Rodrigues
   - Contact: allan.henriques@estudante.ufjf.br
- Gustavo Ribeiro Martins
   - Contact: martins.gustavo@estudante.ufjf.br
- Vitoria Isabela de Oliveira
   - Contact: vitoriaisabela.oliveira@estudante.ufjf.br
<br>
