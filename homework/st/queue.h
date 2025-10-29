#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node(const T &value) : data(value), next(nullptr) {}
    Node(T &&value) : data(std::move(value)), next(nullptr) {}

private:
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
};

template <typename T>
class Queue
{
private:
    Node<T> *front_;
    Node<T> *back_;
    size_t size_;

public:
    Queue() : front_(nullptr), back_(nullptr), size_(0) {};
    Queue(const Queue &other);
    Queue(Queue &&other) noexcept;
    ~Queue() { Clear(); };

    Queue &operator=(const Queue &other);
    Queue &operator=(Queue &&other) noexcept;

    void Push(const T &value);
    void Push(T &&value);
    T Pop();
    T PopMove();
    T &GetFront() const;
    const T &GetFront();
    T &GetBack() const;
    const T &GetBack();
    bool IsEmpty() const;
    size_t Size() const;
    void Clear();

    template <typename P>
    friend std::ostream &operator<<(std::ostream &os, const Queue<P> &stack);
    template <typename P>
    friend std::istream &operator>>(std::istream &is, Queue<P> &stack);
};

#include "queue.tpp"

#endif