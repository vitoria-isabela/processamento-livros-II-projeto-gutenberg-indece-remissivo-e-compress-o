#Livro Tests
add_executable(livroTest1 livroTest1.cpp)
target_link_libraries(livroTest1 PUBLIC libProcessaArquivos)

add_executable(livroTest2 livroTest2.cpp)
target_link_libraries(livroTest2 PUBLIC libProcessaArquivos)

add_executable(livroTest3 livroTest3.cpp)
target_link_libraries(livroTest3 PUBLIC libProcessaArquivos)

