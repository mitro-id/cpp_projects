#ifndef QUEUE_TPP
#define QUEUE_TPP

#include "queue.h"
#include <stdexcept>

// реализация методов Queue
template <typename T>
Queue<T>::Queue(const Queue& other) : front_(nullptr), back_(nullptr), size_(0) {
    if (!other.is_empty()) {
        const Node* current = other.front_;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }
}

template <typename T>
Queue<T>::Queue(Queue&& other) noexcept 
    : front_(other.front_), back_(other.back_), size_(other.size_) {
    other.front_ = nullptr;
    other.back_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        const Node* current = other.front_;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        clear();
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;
        
        other.front_ = nullptr;
        other.back_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void Queue<T>::push(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        front_ = new_node;
        back_ = new_node;
    } else {
        back_->next = new_node;
        back_ = new_node;
    }
    size_++;
}

template <typename T>
void Queue<T>::push(T&& value) {
    Node* new_node = new Node(std::move(value));
    if (is_empty()) {
        front_ = new_node;
        back_ = new_node;
    } else {
        back_->next = new_node;
        back_ = new_node;
    }
    size_++;
}

template <typename T>
T Queue<T>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    T value = front_->data;
    Node* temp = front_;
    front_ = front_->next;
    
    if (front_ == nullptr) {
        back_ = nullptr;
    }
    
    delete temp;
    size_--;
    return value;
}

template <typename T>
T& Queue<T>::get_front() {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return front_->data;
}

template <typename T>
const T& Queue<T>::get_front() const {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return front_->data;
}

template <typename T>
bool Queue<T>::is_empty() const {
    return front_ == nullptr;
}

template <typename T>
size_t Queue<T>::size() const {
    return size_;
}

template <typename T>
void Queue<T>::clear() {
    while (!is_empty()) {
        Node* temp = front_;
        front_ = front_->next;
        delete temp;
    }
    back_ = nullptr;
    size_ = 0;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::begin() {
    return iterator(new typename Queue<T>::QueueIterator(front_));
}

template <typename T>
typename Queue<T>::iterator Queue<T>::end() {
    return iterator(new typename Queue<T>::QueueIterator(nullptr));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::begin() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(front_));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::end() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(nullptr));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cbegin() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(front_));
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cend() const {
    return const_iterator(new typename Queue<T>::ConstQueueIterator(nullptr));
}

#endif