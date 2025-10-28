#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <cmath>

class Complex {
public:
    Complex() : real_(0.0), imag_(0.0) {}
    Complex(double r_) : real_(r_), imag_(0.0) {}
    Complex(double r_, double i_) : real_(r_), imag_(i_) {}

    double real() const;
    double imag() const;
    double abs() const;
    Complex conjugate() const;

    Complex operator+() const;
    Complex operator-() const;

    Complex& operator=(const double rhs);
    Complex& operator=(const Complex &rhs);

    Complex& operator+=(const Complex& rhs);
    Complex& operator+=(const double rhs);

    Complex& operator-=(const Complex& rhs);
    Complex& operator-=(const double rhs);

    Complex& operator*=(const Complex& rhs);
    Complex& operator*=(const double rhs);

    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double rhs);

    bool operator==(const Complex& rhs) const;
    bool operator==(const double rhs) const;

    bool operator!=(const Complex& rhs) const;
    bool operator!=(const double rhs) const;
 
private:
    double real_;
    double imag_;
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator+(const Complex& rhs, const double lhs);
Complex operator+(const double lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& rhs, const double lhs);
Complex operator-(const double lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& rhs, const double lhs);
Complex operator*(const double lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& rhs, const double lhs);
Complex operator/(const double lhs, const Complex& rhs);

bool operator==(const double lhs, const Complex& rhs);
bool operator!=(const double lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& output, Complex& rhs);
std::istream& operator>>(std::istream& intput, Complex& rhs);

#endif