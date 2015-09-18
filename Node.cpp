#include "Node.h"



//Constructor

template <typename T>

Node<T>::Node()

{

    m_next = NULL;

    m_parent = NULL;

}



//Getter for m_value

template <typename T>

T Node<T>::getValue()

{

    return m_value;

}



//Getter for m_next

template <typename T>

Node<T>* Node<T>::getNext()

{

    return m_next;

}



//Getter for m_parent

template <typename T>

Node<T>* Node<T>::getParent()

{

    return m_parent;

}



//Setter for m_value

template <typename T>

void Node<T>::setValue(T value)

{

    m_value = value;

}



//Setter for m_next

template <typename T>

void Node<T>::setNext(Node<T>* next)

{

    m_next = next;

}



//Setter for m_parent

template <typename T>

void Node<T>::setParent(Node<T>* parent)

{

    m_parent = parent;

}