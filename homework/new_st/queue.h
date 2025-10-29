#ifndef QUEUE_H
#define QUEUE_H
#include "dynamic_class.h"

template <typename T>
class Queue: public Dynamic<T>
{
private:
    Node<T> *front_;
    Node<T> *back_;
    size_t size_;

    void print(std::ostream& os) const override;
    void input(std::istream& is) override;

public:
    Queue() : front_(nullptr), back_(nullptr), size_(0) {};
    Queue(const Queue &other);
    Queue(Queue &&other) noexcept;
    ~Queue() { Clear(); };

    Dynamic<T>& operator=(const Dynamic<T>& other) override;
    Dynamic<T>& operator=(Dynamic<T>&& other) noexcept override;

    Queue &operator=(const Queue &other);
    Queue &operator=(Queue &&other) noexcept;

    void Push(const T& value) override;
    void Push(T&& value) override;
    T Pop() override;
    T& GetFront() const override;
    T& GetBack() const;
    bool IsEmpty() const override;
    size_t Size() const override;
    void Clear() override;
};

#include "queue.tpp"

#endif