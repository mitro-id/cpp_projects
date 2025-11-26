#ifndef STACK_TPP
#define STACK_TPP

#include "stack.h"
#include <stdexcept>

// реализация методов Stack
template <typename T>
Stack<T>::Stack(const Stack& other) : top_(nullptr), size_(0) {
    if (!other.is_empty()) {
        const Node* current_other = other.top_;
        Node* current_new = nullptr;
        
        top_ = new Node(current_other->data);
        current_new = top_;
        current_other = current_other->next;
        
        while (current_other != nullptr) {
            current_new->next = new Node(current_other->data);
            current_new = current_new->next;
            current_other = current_other->next;
        }
        
        size_ = other.size_;
    }
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : top_(other.top_), size_(other.size_) {
    other.top_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        
        if (!other.is_empty()) {
            const Node* current_other = other.top_;
            Node* current_new = nullptr;
            
            top_ = new Node(current_other->data);
            current_new = top_;
            current_other = current_other->next;
            
            while (current_other != nullptr) {
                current_new->next = new Node(current_other->data);
                current_new = current_new->next;
                current_other = current_other->next;
            }
            
            size_ = other.size_;
        }
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();

        top_ = other.top_;
        size_ = other.size_;

        other.top_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void Stack<T>::push(const T& value) {
    Node* node = new Node(value);
    node->next = top_;
    top_ = node;
    size_++;
}

template <typename T>
void Stack<T>::push(T&& value) {
    Node* node = new Node(std::move(value));
    node->next = top_;
    top_ = node;
    size_++;
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    T value = top_->data;
    Node* node = top_;
    top_ = top_->next;
    delete node;
    size_--;
    return value;
}

template <typename T>
T& Stack<T>::get_front() {
    if (is_empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top_->data;
}

template <typename T>
const T& Stack<T>::get_front() const {
    if (is_empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top_->data;
}

template <typename T>
bool Stack<T>::is_empty() const {
    return top_ == nullptr;
}

template <typename T>
size_t Stack<T>::size() const {
    return size_;
}

template <typename T>
void Stack<T>::clear() {
    while (!is_empty()) {
        Node* node = top_;
        top_ = top_->next;
        delete node;
    }
    size_ = 0;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return iterator(new typename Stack<T>::StackIterator(top_));
}

template <typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return iterator(new typename Stack<T>::StackIterator(nullptr));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(top_));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::end() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(nullptr));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(top_));
}

template <typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return const_iterator(new typename Stack<T>::ConstStackIterator(nullptr));
}

#endif