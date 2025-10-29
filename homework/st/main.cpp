#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    Stack<int> a;
    a.Push(2);
    a.Push(3);
    a.Push(4);
    Stack<int> b(a);
    Stack<int> c;
    c = a;
    cout << a << "\n" << b << "\n" << c;
    return 0;
}