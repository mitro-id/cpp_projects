#ifndef FUNC_H
#define FUNC_H

#include <cstddef>
#include <cmath>
#include <ostream>
#include <istream>
#include <iostream>

template<typename T, size_t N>
class Vector {
public:
    Vector();
    Vector(const T array[N]);
    Vector(const Vector<T, N>& other);

    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    Vector& operator=(const Vector<T, N>& other);
    Vector& operator+=(const Vector<T, N>& other);
    T operator^(const Vector<T, N>& a1) const;
    Vector operator-() const;

    T norm() const;
    T sum() const;
    Vector& exp();
    Vector& softmax();

private:
    T data[N];
};

template<typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& a1, const Vector<T, N>& a2);

template<typename T, size_t N>
Vector<T, N> operator*(T b, const Vector<T, N>& a);

template<typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& a, T b);

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& output, const Vector<T, N>& a);

template<typename T, size_t N>
std::istream& operator>>(std::istream& input, Vector<T, N>& a);

#include "func.tpp"

#endif