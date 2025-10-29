#ifndef FUNC_TPP
#define FUNC_TPP

#include "func.h"
#include <algorithm>

template<typename T, size_t N>
Vector<T, N>::Vector() {
    std::fill(data, data + N, T());
}

template<typename T, size_t N>
Vector<T, N>::Vector(const T array[N]) {
    std::copy(array, array + N, data);
}

template<typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N>& other) {
    std::copy(other.data, other.data + N, data);
}

template<typename T, size_t N>
T& Vector<T, N>::operator[](size_t i) {
    return data[i];
}

template<typename T, size_t N>
const T& Vector<T, N>::operator[](size_t i) const {
    return data[i];
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& other) {
    if (this != &other) {
        std::copy(other.data, other.data + N, data);
    }
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
        data[i] += other[i];
    }
    return *this;
}

template<typename T, size_t N>
T Vector<T, N>::operator^(const Vector<T, N>& a) const {
    T s = T();
    for (size_t i = 0; i < N; ++i) {
        s += data[i] * a[i];
    }
    return s;
}

template<typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-() const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = -data[i];
    }
    return result;
}

template<typename T, size_t N>
T Vector<T, N>::norm() const {
    T s = T();
    for (size_t i = 0; i < N; ++i) {
        s += data[i] * data[i];
    }
    return std::sqrt(s);
}

template<typename T, size_t N>
T Vector<T, N>::sum() const {
    T s = T();
    for (size_t i = 0; i < N; ++i) {
        s += data[i];
    }
    return s;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::exp() {
    for (size_t i = 0; i < N; ++i) {
        data[i] = std::exp(data[i]);
    }
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::softmax() {
    this->exp();
    T s = this->sum();
    for (size_t i = 0; i < N; ++i) {
        data[i] /= s;
    }
    return *this;
}

template<typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& a1, const Vector<T, N>& a2) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = a1[i] + a2[i];
    }
    return result;
}

template<typename T, size_t N>
Vector<T, N> operator*(T b, const Vector<T, N>& a) {
    Vector<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = b * a[i];
    }
    return result;
}

template<typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& a, T b) {
    return b * a;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& output, const Vector<T, N>& a) {
    output << "(";
    for (size_t i = 0; i < N; ++i) {
        if (i > 0) output << ", ";
        output << a[i];
    }
    output << ")";
    return output;
}

template<typename T, size_t N>
std::istream& operator>>(std::istream& input, Vector<T, N>& a) {
    char ch;
    input >> std::ws;
    
    if (input.peek() != '(') {
        input.setstate(std::ios::failbit);
        return input;
    }
    input >> ch;
    
    for (size_t i = 0; i < N; ++i) {
        input >> std::ws;
        
        T value;
        if (!(input >> value)) {
            input.setstate(std::ios::failbit);
            return input;
        }
        a[i] = value;
        
        input >> std::ws;
        if (i < N - 1) {
            if (input.peek() == ',') {
                input >> ch;
            } else {
                input.setstate(std::ios::failbit);
                return input;
            }
        }
    }
    
    input >> std::ws;
    if (input.peek() != ')') {
        input.setstate(std::ios::failbit);
        return input;
    }
    input >> ch;
    
    return input;
}

#endif