#include <iostream>
#include "list.h"

using namespace std;

// Teste Push Front
int main()
{
    LinkedList<int> array;
    array.add(4, 0);
    array.add(5, 1);
    array.add(8, 2);
    array.add(3, 3);
    array.add(1, 4);
    array.add(6, 5);
    array.add(7, 6);

    array.addFront(11);
    cout << endl;

    return 0;
}