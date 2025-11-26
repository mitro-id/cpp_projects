#ifndef DYNAMIC_CLASS_TPP
#define DYNAMIC_CLASS_TPP
#include "dynamic_class.h"

// реализация операторов для пар iterator/const_iterator
template<typename T>
fwd_container<T>::iterator::iterator(const const_iterator& other) 
    : base_(other.base_ ? static_cast<iterator_base*>(other.base_->clone()) : nullptr) {}

template<typename T>
typename fwd_container<T>::iterator& fwd_container<T>::iterator::operator=(const const_iterator& other) {
    if (this != &other) {
        delete base_;
        base_ = other.base_ ? static_cast<iterator_base*>(other.base_->clone()) : nullptr;
    }
    return *this;
}

template<typename T>
bool fwd_container<T>::iterator::operator==(const const_iterator& other) const {
    if (!this->base_ && !other.base_) return true;
    if (!this->base_ || !other.base_) return false;
    return *this->base_ == *other.base_;
}

template<typename T>
bool fwd_container<T>::iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

template<typename T>
fwd_container<T>::const_iterator::const_iterator(const iterator& other)
    : base_(other.base_ ? static_cast<const_iterator_base*>(other.base_->clone()) : nullptr){}

template<typename T>
typename fwd_container<T>::const_iterator& fwd_container<T>::const_iterator::operator=(const iterator& other) {
    if (this != &other) {
        delete base_;
        base_ = other.base_ ? static_cast<const_iterator_base*>(other.base_->clone()) : nullptr;
    }
    return *this;
}

template<typename T>
bool fwd_container<T>::const_iterator::operator==(const iterator& other) const {
    if (!this->base_ && !other.base_) return true;
    if (!this->base_ || !other.base_) return false;
    return *this->base_ == *other.base_;
}

template<typename T>
bool fwd_container<T>::const_iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container) {
    auto it = container.begin();
    auto end_it = container.end();
    
    if (it != end_it) {
        os << *it;
        ++it;
    }
    
    for (; it != end_it; ++it) {
        os << " " << *it;
    }
    
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container) {
    T value;
    while (is >> value) {
        container.push(value);
        if (is.peek() == '\n' || is.eof()) {
            break;
        }
    }
    return is;
}

#endif