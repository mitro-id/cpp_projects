#ifndef DYNAMIC_CLASS_H
#define DYNAMIC_CLASS_H

#include <iostream>
#include <iterator>
#include <stdexcept>

template<typename T>
class fwd_container {
public:
    // обобщающий базовый итератор
    class iterator_base_common {
    public:
        virtual ~iterator_base_common() = default;
        virtual iterator_base_common* clone() const = 0;
    };

    // итератор, от которого будут наследоваться итераторы динамических классов
    class iterator_base : public iterator_base_common {
    public:
        virtual T& operator*() = 0;
        virtual T* operator->() = 0;
        virtual iterator_base& operator++() = 0;
        virtual bool operator==(const iterator_base_common& other) const = 0;
        virtual bool operator!=(const iterator_base_common& other) const = 0;
    };

    // константный интератор, от которго будут наследоваться константные итераторы динамических классов
    class const_iterator_base : public iterator_base_common {
    public:
        virtual const T& operator*() const = 0;
        virtual const T* operator->() const = 0;
        virtual const_iterator_base& operator++() = 0;
        virtual bool operator==(const iterator_base_common& other) const = 0;
        virtual bool operator!=(const iterator_base_common& other) const = 0;
    };

    class const_iterator;

    // общий итератор
    class iterator {
    private:
        iterator_base* base_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator() : base_(nullptr) {}
        iterator(iterator_base* base) : base_(base) {}
        
        iterator(const iterator& other) : base_(other.base_ ? static_cast<iterator_base*>(other.base_->clone()) : nullptr) {}
        
        iterator(iterator&& other) noexcept : base_(other.base_) {
            other.base_ = nullptr;
        }
        
         ~iterator() { delete base_; }
        
        iterator& operator=(const iterator& other) {
            if (this != &other) {
                delete base_;
                base_ = other.base_ ? static_cast<iterator_base*>(other.base_->clone()) : nullptr;
            }
            return *this;
        }
        
        iterator& operator=(iterator&& other) noexcept {
            if (this != &other) {
                delete base_;
                base_ = other.base_;
                other.base_ = nullptr;
            }
            return *this;
        }
        
        reference operator*() { 
            if (!base_) throw std::runtime_error("Dereferencing null iterator");
            return **base_; 
        }
        
        pointer operator->() { 
            if (!base_) throw std::runtime_error("Accessing through null iterator");
            return &(**base_); 
        }
        
        iterator& operator++() {
            if (base_) {
                ++(*base_);
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            if (base_) {
                ++(*base_);
            }
            return temp;
        }

        bool operator==(const iterator& other) const {
            if (!base_ && !other.base_) return true;
            if (!base_ || !other.base_) return false;
            return *base_ == *other.base_;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        friend class const_iterator;

        iterator(const const_iterator& other);
        
        iterator& operator=(const const_iterator& other);
        
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
    };

    // общий константный итератор
    class const_iterator {
    private:
        const_iterator_base* base_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : base_(nullptr) {}
        const_iterator(const_iterator_base* base) : base_(base) {}
        
        const_iterator(const const_iterator& other) : base_(other.base_ ? static_cast<const_iterator_base*>(other.base_->clone()) : nullptr) {}
        
        const_iterator(const_iterator&& other) noexcept : base_(other.base_) {
            other.base_ = nullptr;
        }
        
         ~const_iterator() { delete base_; }

        const_iterator& operator=(const const_iterator& other) {
            if (this != &other) {
                delete base_;
                base_ = other.base_ ? static_cast<const_iterator_base*>(other.base_->clone()) : nullptr;
            }
            return *this;
        }
        
        const_iterator& operator=(const_iterator&& other) noexcept {
            if (this != &other) {
                delete base_;
                base_ = other.base_;
                other.base_ = nullptr;
            }
            return *this;
        }
        
        reference operator*() const { 
            if (!base_) throw std::runtime_error("Dereferencing null iterator");
            return **base_; 
        }
        
        pointer operator->() const { 
            if (!base_) throw std::runtime_error("Accessing through null iterator");
            return &(**base_); 
        }
        
        const_iterator& operator++() {
            if (base_) {
                ++(*base_);
            }
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator temp = *this;
            if (base_) {
                ++(*base_);
            }
            return temp;
        }
        
        bool operator==(const const_iterator& other) const {
            if (!base_ && !other.base_) return true;
            if (!base_ || !other.base_) return false;
            return *base_ == *other.base_;
        }
        
        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
        friend class iterator;

        const_iterator(const iterator& other);
        
        const_iterator& operator=(const iterator& other);
        
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    // объявление общих методов
    virtual ~fwd_container() = default;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& get_front() = 0;
    virtual const T& get_front() const = 0;
    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;

    // объявление пар begin/end
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const fwd_container<U>& container);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& is, fwd_container<U>& container);
};
#include "dynamic_class.tpp"

#endif