#ifndef STACK_H
#define STACK_H
#include "dynamic_class.h"
#include <iostream>

template<typename T>
class Stack: public Dynamic<T>{
protected:
    Node<T>* top_;
    size_t size_;
    
    void print(std::ostream& os) const override;
    void input(std::istream& is) override;

public:
    Stack() : top_(nullptr), size_(0) {};
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack(){ Clear(); };

    Dynamic<T>& operator=(const Dynamic<T>& other) override;
    Dynamic<T>& operator=(Dynamic<T>&& other) noexcept override;
    
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void Push(const T& value) override;
    void Push(T&& value) override;
    T Pop() override;
    T& GetFront() const override;
    bool IsEmpty() const override;
    size_t Size() const override;
    void Clear() override;
};

#include "stack.tpp"

#endif