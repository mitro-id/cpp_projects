#include "test.h"

void test_constructors() {
    
    Complex c1;
    assert(c1.real() == 0.0);
    assert(c1.imag() == 0.0);
    
    Complex c2(5.0);
    assert(c2.real() == 5.0);
    assert(c2.imag() == 0.0);
    
    Complex c3(2.0, 3.0);
    assert(c3.real() == 2.0);
    assert(c3.imag() == 3.0);
}

void test_methods() {
    
    Complex c1(3.0, 4.0);
    assert(std::abs(c1.abs() - 5.0) < 1e-10);
    
    Complex c2(2.0, -3.0);
    Complex conj = c2.conjugate();
    assert(conj.real() == 2.0);
    assert(conj.imag() == 3.0);
}

void test_arithmetic() {
    
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 2.0);
    
    Complex sum1 = c1 + c2;
    assert(sum1.real() == 3.0);
    assert(sum1.imag() == 5.0);
    
    Complex sum2 = c1 + 5.0;
    assert(sum2.real() == 7.0);
    assert(sum2.imag() == 3.0);
    
    Complex sum3 = 5.0 + c1;
    assert(sum3.real() == 7.0);
    assert(sum3.imag() == 3.0);
    
    Complex diff1 = c1 - c2;
    assert(diff1.real() == 1.0);
    assert(diff1.imag() == 1.0);
    
    Complex diff2 = c1 - 5.0;
    assert(diff2.real() == -3.0);
    assert(diff2.imag() == 3.0);
    
    Complex diff3 = 5.0 - c1;
    assert(diff3.real() == 3.0);
    assert(diff3.imag() == -3.0);
    
    Complex prod1 = c1 * c2;
    assert(prod1.real() == -4.0);
    assert(prod1.imag() == 7.0);
    
    Complex prod2 = c1 * 2.0;
    assert(prod2.real() == 4.0);
    assert(prod2.imag() == 6.0);
    
    Complex prod3 = 2.0 * c1;
    assert(prod3.real() == 4.0);
    assert(prod3.imag() == 6.0);
    
    Complex c3(4.0, 2.0);
    Complex c4(2.0, 1.0);
    Complex quot1 = c3 / c4;
    assert(std::abs(quot1.real() - 2.0) < 1e-10);
    assert(std::abs(quot1.imag() - 0.0) < 1e-10);
    
    Complex quot2 = c1 / 2.0;
    assert(quot2.real() == 1.0);
    assert(quot2.imag() == 1.5);
    
    Complex quot3 = 10.0 / c4;
    assert(std::abs(quot3.real() - 4.0) < 1e-10);
    assert(std::abs(quot3.imag() - (-2.0)) < 1e-10);
}

void test_assignment() {
    
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 2.0);

    c1 += c2;
    assert(c1.real() == 3.0);
    assert(c1.imag() == 5.0);
    
    c1 += 2.0;
    assert(c1.real() == 5.0);
    assert(c1.imag() == 5.0);
    
    c1 -= c2;
    assert(c1.real() == 4.0);
    assert(c1.imag() == 3.0);
    
    c1 -= 1.0;
    assert(c1.real() == 3.0);
    assert(c1.imag() == 3.0);
    
    Complex c3(1.0, 1.0);
    c3 *= Complex(2.0, 3.0);
    assert(c3.real() == -1.0);
    assert(c3.imag() == 5.0);
    
    c3 *= 2.0;
    assert(c3.real() == -2.0);
    assert(c3.imag() == 10.0);
    
    Complex c4(4.0, 2.0);
    c4 /= Complex(2.0, 1.0);
    assert(std::abs(c4.real() - 2.0) < 1e-10);
    assert(std::abs(c4.imag() - 0.0) < 1e-10);
    
    c4 = Complex(2, 2);
    c4 /= 2;
    assert(c4.real() == 1.0);
    assert(c4.imag() == 1.0);
}

void test_comparison() {
    
    Complex c1(2.0, 3.0);
    Complex c2(2.0, 3.0);
    Complex c3(2.0, 4.0);
    Complex c4(3.0, 3.0);
    
    assert(c1 == c2);
    assert(!(c1 == c3));
    assert(!(c1 == c4));
    
    assert(c1 == Complex(2.0, 3.0));
    assert(Complex(5.0, 0.0) == 5.0);
    assert(5.0 == Complex(5.0, 0.0));
    
    assert(c1 != c3);
    assert(c1 != c4);
    assert(!(c1 != c2));
    
    assert(c1 != 5.0);
    assert(5.0 != c1);
}

void test_io() {
    std::stringstream s;
    Complex a(0, 1);
    s << a;
    assert(s.str() == "i");
    a = Complex(1, 0);
    s.str("");
    s << a;
    assert(s.str() == "1");
    a = Complex(4, 4);
    s.str("");
    s << a;
    assert(s.str() == "4+4i");
    a = Complex(0.01, 0.01);
    s.str("");
    s << a;
    assert(s.str() == "0.01+0.01i");

    s.str("");
    s << "i";
    Complex z;
    s >> z;
    assert(z == Complex(0, 1));
    s.str("");
    s << "1";
    s >> z;
    assert(z == Complex(1, 0));
    s.clear();
    s << "3+3i";
    s >> z;
    assert(z == Complex(3, 3));
    s.str("");
    s << "0.01+0.01i";
    s >> z;
    assert(z == Complex(0.01, 0.01));
}

void test_unary() {
    
    Complex c1(2.0, -3.0);
    Complex c2 = +c1;
    assert(c2.real() == 2.0);
    assert(c2.imag() == -3.0);
    
    Complex c3 = -c1;
    assert(c3.real() == -2.0);
    assert(c3.imag() == 3.0);
    
}

void tests() {
    std::cout << "Running tests...\n\n";
    
    test_constructors();
    test_methods();
    test_unary();
    test_arithmetic();
    test_assignment();
    test_comparison();
    test_io();
    
    std::cout << "\nAll tests passed successfully!\n";
}