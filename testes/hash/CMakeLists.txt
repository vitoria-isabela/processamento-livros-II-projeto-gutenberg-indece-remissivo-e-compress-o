# Region Tests Hash
add_executable(hashTest1 hashTest1.cpp) # coloca como param o nome do executavel e o arquivo .cpp
target_link_libraries(hashTest1 PUBLIC libProcessaArquivos) # cria link o hashTest1 (teste1.cpp) com a libProcessaArquivos

add_executable(hashTest2 hashTest2.cpp) 
target_link_libraries(hashTest2 PUBLIC libProcessaArquivos) 

add_executable(hashTest3 hashTest3.cpp) 
target_link_libraries(hashTest3 PUBLIC libProcessaArquivos) 

add_executable(hashTest4 hashTest4.cpp) 
target_link_libraries(hashTest4 PUBLIC libProcessaArquivos) 

