#ifndef DYNAMIC_CLASS_H
#define DYNAMIC_CLASS_H
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
class Dynamic{
public:
    virtual ~Dynamic() = default;

    virtual void Push(const T& value) = 0;
    virtual void Push(T&& value) = 0;
    virtual T Pop() = 0;
    virtual T& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    virtual void Clear() = 0;

    virtual Dynamic &operator=(const Dynamic &other) = 0;
    virtual Dynamic &operator=(Dynamic &&other) noexcept = 0;

    template<typename P>
    friend std::ostream& operator<<(std::ostream& os, const Dynamic<P>& din){
        din.print(os);
        return os;
    };
    template<typename P>
    friend std::istream& operator>>(std::istream& is, Dynamic<P>& din){
        din.input(is);
        return is;
    };

protected:
    virtual void print(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;
};

#endif