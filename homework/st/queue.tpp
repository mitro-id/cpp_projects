#ifndef QUEUE_TPP
#define QUEUE_TPP
#include "queue.h"

template <typename T>
Queue<T>::Queue(const Queue &other) : front_(nullptr), back_(nullptr), size_(0)
{
    if (!other.IsEmpty())
    {
        Node<T> *node = other.front_;
        while (node != nullptr)
        {
            Push(node->data);
            node = node->next;
        }
        size_ = other.size_;
    }
} // +

template <typename T>
Queue<T>::Queue(Queue &&other) noexcept : front_(other.front_), back_(other.back_), size_(other.size_)
{
    other.front_ = nullptr;
    other.back_ = nullptr;
    other.size_ = 0;
} // +

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other)
{
    if (!other.IsEmpty() && this != &other)
    {
        Clear();
        Node<T> *node = other.front_;
        while (node != nullptr)
        {
            Push(node->data);
            node = node->next;
        }
        size_ = other.size_;
    }
    return *this;
} // +

template <typename T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept
{
    if (this != &other)
    {
        Clear();

        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;

        other.front_ = nullptr;
        other.back_ = nullptr;
        other.size_ = 0;
    }
    return *this;
} // +

template <typename T>
void Queue<T>::Push(const T &value)
{
    try
    {
        Node<T> *new_node = new Node<T>(value);
        if (IsEmpty())
        {
            front_ = new_node;
            back_ = new_node;
        }
        else
        {
            back_->next = new_node;
            back_ = new_node;
        }
        size_++;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Queue::Push: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Queue::Push");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unxcepted error in Queue::Push: " << e.what() << std::endl;
        throw;
    }
} // +

template <typename T>
void Queue<T>::Push(T &&value)
{
    try
    {
        Node<T> *new_node = new Node<T>(std::move(value));
        if (IsEmpty())
        {
            front_ = new_node;
            back_ = new_node;
        }
        else
        {
            back_->next = new_node;
            back_ = new_node;
        }
        size_++;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory error in Queue::Push: " << e.what() << std::endl;
        throw std::runtime_error("Memory error in Queue::Push ");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unxcepted error in Queue::Push: " << e.what() << std::endl;
        throw;
    }
} // +

template <typename T>
T Queue<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }

    try
    {
        T value = front_->data;
        Node<T> *temp = front_;
        front_ = front_->next;

        if (front_ == nullptr)
        {
            back_ = nullptr;
        }

        delete temp;
        size_--;
        return value;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Queue::Pop: " << e.what() << std::endl;
        throw;
    }
} // +

template <typename T>
T Queue<T>::PopMove()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }

    try
    {
        T value = std::move(front_->data);
        Node<T> *temp = front_;
        front_ = front_->next;

        if (front_ == nullptr)
        {
            back_ = nullptr;
        }

        delete temp;
        size_--;
        return value;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error in Queue::Pop: " << e.what() << std::endl;
        throw;
    }
} // +

template <typename T>
T &Queue<T>::GetFront() const
{
    if (IsEmpty())
    {
        throw std::runtime_error("Empty error Queue::GetFront");
    }
    return front_->data;
} // +

template <typename T>
const T &Queue<T>::GetFront()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Empty error Queue::GetFront");
    }
    return front_->data;
} // +

template <typename T>
T &Queue<T>::GetBack() const
{
    if (IsEmpty())
    {
        throw std::runtime_error("Empty error Queue::GetBack");
    }
    return back_->data;
} // +

template <typename T>
const T &Queue<T>::GetBack()
{
    if (IsEmpty())
    {
        throw std::runtime_error("Empty error Queue::GetBack");
    }
    return back_->data;
} // +

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return front_ == nullptr;
} // +

template <typename T>
size_t Queue<T>::Size() const
{
    return size_;
} // +

template <typename T>
void Queue<T>::Clear()
{
    while (!IsEmpty())
    {
        Node<T> *node = front_;
        front_ = front_->next;
        delete node;
    }
    size_ = 0;
} // +

template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &queue)
{
    Node<T> *node = queue.front_;
    os << "FRONT -> ";
    while (node)
    {
        os << node->data << " ";
        node = node->next;
    }
    os << " <- BACK";
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, Queue<T> &queue)
{
    T value;
    while (is >> value)
    {
        queue.Push(value);
        if (is.peek() == '\n')
        {
            break;
        }
    }
    return is;
}

#endif