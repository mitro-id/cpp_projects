#ifndef QUEUE_H
#define QUEUE_H

#include "dynamic_class.h"


// реализация объявление и частичная реализация класса наследника Queue
template <typename T>
class Queue : public fwd_container<T> {
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Queue() : front_(nullptr), back_(nullptr), size_(0) {}
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    ~Queue() { clear(); }

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void push(const T& value) override;
    void push(T&& value) override;
    T pop() override;
    T& get_front() override;
    const T& get_front() const override;
    bool is_empty() const override;
    size_t size() const override;
    void clear() override;
    
    iterator begin() override;
    iterator end() override;
    const_iterator begin() const override;
    const_iterator end() const override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    Node* front_;
    Node* back_;
    size_t size_;

    class QueueIterator : public fwd_container<T>::iterator_base {
    private:
        Node* current_;

    public:
        QueueIterator(Node* node) : current_(node) {}
        
        T& operator*() override {
            return current_->data;
        }
        
        T* operator->() override {
            return &(current_->data);
        }
        
        QueueIterator& operator++() override {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        bool operator==(const typename fwd_container<T>::iterator_base_common& other) const override {
            const QueueIterator* derived = dynamic_cast<const QueueIterator*>(&other);
            return derived && current_ == derived->current_;
        }
        
        bool operator!=(const typename fwd_container<T>::iterator_base_common& other) const override {
            return !(*this == other);
        }
        typename fwd_container<T>::iterator_base_common* clone() const override {
            return new QueueIterator(current_);
        }
    };

    class ConstQueueIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node* current_;

    public:
        ConstQueueIterator(const Node* node) : current_(node) {}
        
        const T& operator*() const override {
            return current_->data;
        }
        
        const T* operator->() const override {
            return &(current_->data);
        }
        
        ConstQueueIterator& operator++() override {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        bool operator==(const typename fwd_container<T>::iterator_base_common& other) const override {
            const ConstQueueIterator* derived = dynamic_cast<const ConstQueueIterator*>(&other);
            return derived && current_ == derived->current_;
        }
        
        bool operator!=(const typename fwd_container<T>::iterator_base_common& other) const override {
            return !(*this == other);
        }
        typename fwd_container<T>::iterator_base_common* clone() const override {
            return new ConstQueueIterator(current_);
        }
    };
};

#include "queue.tpp"

#endif