#ifndef STACK_TPP
#define STACK_TPP
#include "stack.h"

template <typename T>
Stack<T>::Stack(const Stack &other) : top_(nullptr), size_(0)
{
    try{
        if (!other.IsEmpty())
        {
            Node<T>* current_other = other.top_;
            Node<T>* current_new = nullptr;
            
            top_ = new Node<T>(current_other->data);
            current_new = top_;
            current_other = current_other->next;
            
            while (current_other != nullptr)
            {
                current_new->next = new Node<T>(current_other->data);
                current_new = current_new->next;
                current_other = current_other->next;
            }
            
            size_ = other.size_;
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Stack copy constructor: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Stack copy constructor");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Stack copy constructor: " << e.what() << std::endl;
        throw;
    }
}

template <typename T>
Stack<T>::Stack(Stack &&other) noexcept : top_(other.top_), size_(other.size_)
{
    other.top_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Dynamic<T>& Stack<T>::operator=(const Dynamic<T>& other) {
    const Stack<T>* stack_ptr = dynamic_cast<const Stack<T>*>(&other);
    if (!stack_ptr) {
        throw std::bad_cast();
    }
    return *this = *stack_ptr;
}

template <typename T>
Dynamic<T>& Stack<T>::operator=(Dynamic<T>&& other) noexcept {
    Stack<T>* stack_ptr = dynamic_cast<Stack<T>*>(&other);
    if (stack_ptr) {
        return *this = std::move(*stack_ptr);
    }
    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    try{
        if (this != &other)
        {
            Clear();
            
            if (!other.IsEmpty())
            {
                Node<T>* current_other = other.top_;
                Node<T>* current_new = nullptr;
                
                top_ = new Node<T>(current_other->data);
                current_new = top_;
                current_other = current_other->next;
                
                while (current_other != nullptr)
                {
                    current_new->next = new Node<T>(current_other->data);
                    current_new = current_new->next;
                    current_other = current_other->next;
                }
                
                size_ = other.size_;
            }
        }
        return *this;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Stack::operator=: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Stack::operator=");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Stack::operator=: " << e.what() << std::endl;
        throw;
    }
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other) noexcept
{
    if (this != &other)
    {
        Clear();

        top_ = other.top_;
        size_ = other.size_;

        other.top_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void Stack<T>::Push(const T &value)
{
    try
    {
        Node<T> *node = new Node<T>(value);
        node->next = top_;
        top_ = node;
        size_++;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Stack::Push: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Stack::Push");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Stack::Push: " << e.what() << std::endl;
        throw;
    }
}

template <typename T>
void Stack<T>::Push(T &&value)
{
    try
    {
        Node<T> *node = new Node<T>(std::move(value));
        node->next = top_;
        top_ = node;
        size_++;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Stack::Push: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Stack::Push");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Stack::Push: " << e.what() << std::endl;
        throw;
    }
}

template <typename T>
T Stack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Stack is empty");
    }
    try
    {
        T value = top_->data;
        Node<T> *node = top_;
        top_ = top_->next;
        delete node;
        size_--;
        return value;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Stack::Pop: " << e.what() << std::endl;
        throw;
    }
}

template <typename T>
T &Stack<T>::GetFront() const
{
    if (IsEmpty())
    {
        throw std::runtime_error("Empty error in Stack::GetFront");
    }
    return top_->data;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
    return top_ == nullptr;
}

template <typename T>
size_t Stack<T>::Size() const
{
    return size_;
}

template <typename T>
void Stack<T>::Clear()
{
    while (!IsEmpty())
    {
        Node<T> *node = top_;
        top_ = top_->next;
        delete node;
    }
    size_ = 0;
}

template <typename T>
void Stack<T>::print(std::ostream& os) const {
    Node<T> *node = top_;
    os << "TOP -> ";
    while (node)
    {
        os << node->data << " ";
        node = node->next;
    }
}

template <typename T>
void Stack<T>::input(std::istream& is) {
    T value;
    while (is >> value)
    {
        Push(value);
        if (is.peek() == '\n' || is.eof())
        {
            break;
        }
    }
}

#endif