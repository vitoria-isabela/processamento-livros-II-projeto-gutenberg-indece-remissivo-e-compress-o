add_subdirectory(hash) #adiciona os subdiretorios na pasta testes

add_subdirectory(list) #adiciona os subdiretorios na pasta testes

add_subdirectory(livro) #adiciona os subdiretorios na pasta testes

add_subdirectory(trie) #adiciona os subdiretorios na pasta testes

add_subdirectory(huffman)

add_executable(TestSwitchHash TestSwitchHashFunc.cpp) # coloca como param o nome do executavel e o arquivo .cpp
target_link_libraries(TestSwitchHash PUBLIC libProcessaArquivos) # cria link o hashTest1 (teste1.cpp) com a libProcessaArquivos

add_executable(TestSort TestSort.cpp) # coloca como param o nome do executavel e o arquivo .cpp
target_link_libraries(TestSort PUBLIC libProcessaArquivos) # cria link o hashTest1 (teste1.cpp) com a libProcessaArquivos

add_executable(Test10books Test10books.cpp) # coloca como param o nome do executavel e o arquivo .cpp
target_link_libraries(Test10books PUBLIC libProcessaArquivos) # cria link o hashTest1 (teste1.cpp) com a libProcessaArquivos