//

//  Node.cpp

//  Lab_4_EECS_560

//

//  Created by Michael Thornbrugh on 2/26/15.

//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.

//



#include "Node.h"



//Constructor

template <typename T>

Node<T>::Node()

{

    m_left = NULL;

    m_right = NULL;

    m_parent = NULL;

}



//Getter for m_value

template <typename T>

T Node<T>::getValue()

{

    return m_value;

}



//Getter for m_left

template <typename T>

Node<T>* Node<T>::getLeft()

{

    return m_left;

}



//Getter for m_right

template <typename T>

Node<T>* Node<T>::getRight()

{

    return m_right;

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



//Setter for m_left

template <typename T>

void Node<T>::setLeft(Node<T>* left)

{

    m_left = left;

}



//Setter for m_right

template <typename T>

void Node<T>::setRight(Node<T>* right)

{

    m_right = right;

}



//Setter for m_parent

template <typename T>

void Node<T>::setParent(Node<T>* parent)

{

    m_parent = parent;

}