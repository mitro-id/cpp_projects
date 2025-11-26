#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    Stack<int> a;
    a.push(3);
    a.push(2);
    a.push(1);
    a.push(4);
    a.pop();
    cout << a << "\n";
    return 0;
}