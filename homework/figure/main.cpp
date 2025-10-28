#include <iostream>
#include "figure.h"

int main(){
    Ellipse figure1(1, 1);
    Ellipse figure2 = figure1;
    std::cout << figure1 << "\n" << figure2;
    return 0;
}