#ifndef STACK_H
#define STACK_H
#include <iostream>

template<typename T>
class Node{
public:
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
    Node(T&& value) : data(std::move(value)), next(nullptr) {}
private:
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

template<typename T>
class Stack{
private:
    Node<T>* top_;
    size_t size_;

public:
    Stack() : top_(nullptr), size_(0) {};
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack(){ Clear(); };

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void Push(const T& value);
    void Push(T&& value);
    T Pop();
    T PopMove();
    T& GetFront() const;
    const T& GetFront();
    bool IsEmpty() const;
    size_t Size() const;
    void Clear();

    template<typename P>
    friend std::ostream& operator<<(std::ostream& os, const Stack<P>& stack);
    template<typename P>
    friend std::istream& operator>>(std::istream& is, Stack<P>& stack);
};

#include "stack.tpp"

#endif