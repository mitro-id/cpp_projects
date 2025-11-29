#ifndef STACK_H
#define STACK_H

#include "dynamic_class.h"

// объявление и частичная реализация класса наследника Stack
template <typename T>
class Stack : public fwd_container<T> {
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Stack() : top_(nullptr), size_(0) {}
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack() { clear(); }

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

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

    Node* top_;
    size_t size_;

    class StackIterator : public fwd_container<T>::iterator_base {
    private:
        Node* current_;

    public:
        StackIterator(Node* node) : current_(node) {}
        
        T& operator*() override {
            return current_->data;
        }
        
        T* operator->() override {
            return &(current_->data);
        }
        
        StackIterator& operator++() override {
            current_ = current_->next;
            return *this;
        }
        
        bool operator==(const typename fwd_container<T>::iterator_base_common& other) const override {
            return current_ == static_cast<const StackIterator&>(other).current_;
        }
        
        bool operator!=(const typename fwd_container<T>::iterator_base_common& other) const override {
            return !(*this == other);
        }
        
        typename fwd_container<T>::iterator_base_common* clone() const override {
            return new StackIterator(current_);
        }
    };

    class ConstStackIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node* current_;

    public:
        ConstStackIterator(const Node* node) : current_(node) {}
        
        const T& operator*() const override {
            return current_->data;
        }
        
        const T* operator->() const override {
            return &(current_->data);
        }
        
        ConstStackIterator& operator++() override {
            current_ = current_->next;
            return *this;
        }
        
        bool operator==(const typename fwd_container<T>::iterator_base_common& other) const override {
            return current_ == static_cast<const ConstStackIterator&>(other).current_;
        }
        
        bool operator!=(const typename fwd_container<T>::iterator_base_common& other) const override {
            return !(*this == other);
        }
        
        typename fwd_container<T>::iterator_base_common* clone() const override {
            return new ConstStackIterator(current_);
        }
    };
};

#include "stack.tpp"

#endif