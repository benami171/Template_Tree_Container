#include "Node.hpp"

template <typename T>
Node<T>::Node(T value) : value(value) {}

template <typename T>
T Node<T>::getValue() const
{
    return value;
}