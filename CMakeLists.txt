cmake_minimum_required(VERSION 3.14)
project(dcc012b-processando-arquivos)

option(CPU_TIME  "Enable cputime build" ON)

set(INPUT_DIR "${PROJECT_SOURCE_DIR}/input/")

set(BOOK1 "${PROJECT_SOURCE_DIR}/input/book1.txt")
set(BOOK2 "${PROJECT_SOURCE_DIR}/input/book2.txt")
set(BOOK3 "${PROJECT_SOURCE_DIR}/input/book3.txt")
set(BOOK4 "${PROJECT_SOURCE_DIR}/input/book4.txt")
set(BOOK5 "${PROJECT_SOURCE_DIR}/input/book5.txt")
set(BOOK6 "${PROJECT_SOURCE_DIR}/input/book6.txt")
set(BOOK7 "${PROJECT_SOURCE_DIR}/input/book7.txt")
set(BOOK8 "${PROJECT_SOURCE_DIR}/input/book8.txt")
set(BOOK9 "${PROJECT_SOURCE_DIR}/input/book9.txt")
set(BOOK10 "${PROJECT_SOURCE_DIR}/input/book10.txt")
set(BOOK11 "${PROJECT_SOURCE_DIR}/input/book11.txt")
set(HASHTABLELOG "${PROJECT_SOURCE_DIR}/output/Hash/")
set(OUTPUT "${PROJECT_SOURCE_DIR}/output/")
set(SORTMETHOD "${PROJECT_SOURCE_DIR}/output/Sort/")
set(CASO4 "${PROJECT_SOURCE_DIR}/output/Sort/caso4/")
set(HCODED "${PROJECT_SOURCE_DIR}/output/Huffman/Coded/")
set(HDECODED "${PROJECT_SOURCE_DIR}/output/Huffman/Decoded/")


set(CMAKE_CXX_STANDARD 11)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

include_directories(${PROJECT_SOURCE_DIR}/include) 
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/include/*.h ) # armazena em "sources" todos os arquivos especificados nas pastas src e include

add_library(libProcessaArquivos ${sources}) #cria uma biblioteca 

add_subdirectory(testes) #adiciona os subdiretorios na pasta src

enable_testing()

#Testes Unitarios
#Testes para o Hash
add_test(
    NAME   TestInsert
    COMMAND $<TARGET_FILE:hashTest1> #hashTest1: é o nome do executavel.
    )
  
    add_test(
    NAME   TestRemove
    COMMAND $<TARGET_FILE:hashTest2> 
    ) 
  
    add_test(
    NAME   TestPrintInfo
    COMMAND $<TARGET_FILE:hashTest3> 
    )
  
  
    #Testes para a Lista
  
    add_test(
    NAME   TestClearInsertEmpty
    COMMAND $<TARGET_FILE:listTest1> 
    )
  
    add_test(
    NAME   TestPush_back
    COMMAND $<TARGET_FILE:listTest2> 
    )
  
    add_test(
    NAME   TestPush_front
    COMMAND $<TARGET_FILE:listTest3> 
    )
  
  
    add_test(
    NAME   TestPop_back
    COMMAND $<TARGET_FILE:listTest4> 
    )
  
    add_test(
    NAME   TestPop
    COMMAND $<TARGET_FILE:listTest5> 
    )
  
    add_test(
    NAME   TestLook_up
    COMMAND $<TARGET_FILE:listTest6> 
    )
  
    add_test(
    NAME   TestGetDataAt
    COMMAND $<TARGET_FILE:listTest7> 
    )
  
  
  
    #Testes para o Processa Livro
  
    add_test(
    NAME   TestConvertWordToLowercase
    COMMAND $<TARGET_FILE:livroTest1> 
    )
  
    add_test(
    NAME   TestRemovePontuation
    COMMAND $<TARGET_FILE:livroTest2> 
    )
  
    add_test(
    NAME   ObterNumeroLinhasLivro
    COMMAND $<TARGET_FILE:livroTest3>
    )

    #Teste da Trie (Busca Digital)
    add_test(
    NAME   TrieMainTest1
    COMMAND $<TARGET_FILE:trieMainTest1>
    )

    add_test(
    NAME   searchTrie
    COMMAND $<TARGET_FILE:searchTrie>
    )

    #Teste do huffman (Huffman Compression)
    add_test(
    NAME   HuffmanCompress
    COMMAND $<TARGET_FILE:HuffmanCompress>
    )
    
    add_test(
        NAME   HuffmanDecompress
        COMMAND $<TARGET_FILE:HuffmanDecompress>
        )

    add_test(
        NAME   buildTree
        COMMAND $<TARGET_FILE:buildTree>
        )

    add_test(
    NAME   printTree
    COMMAND $<TARGET_FILE:printTree>
    )

    #Testes Principais
    
    add_test(
    NAME TestSwitchHashFunc
    COMMAND  $<TARGET_FILE:TestSwitchHash>
    ) 

    add_test(
    NAME TestSort
    COMMAND  $<TARGET_FILE:TestSort>
    ) 

    add_test(
    NAME Test10books
    COMMAND  $<TARGET_FILE:Test10books>
    ) 
    

    
