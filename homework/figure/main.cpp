#include <iostream>
#include "figure.h"

int main(){
    Rectangle figure1(1, 1);
    Rectangle figure2 = figure1;
    std::cout << figure1 << "\n" << figure2;
    return 0;
}