#include <iostream>

#include "config.h"
#include "processaLivro.h"

using namespace std;

int main(int argc, char *argv[])
{
    ProcessBook book1(BOOK9,"Book9");
    book1.DeCompressToHuffman();
}