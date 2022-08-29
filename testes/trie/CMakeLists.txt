add_executable(trieMainTest1 mainTest.cpp) 
target_link_libraries(trieMainTest1 PUBLIC libProcessaArquivos) 

add_executable(searchTrie search.cpp) 
target_link_libraries(searchTrie PUBLIC libProcessaArquivos) 