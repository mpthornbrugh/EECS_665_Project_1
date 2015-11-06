//
//  Node.cpp
//  Project_1
//  EECS_665
//
//  Created by Michael Thornbrugh on 9/17/15.
//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.
//

#include "Node.h"

Node::Node()
{
    m_next = NULL;
    m_parent = NULL;
    m_value = "Not Initialized";
}

std::string Node::getValue()
{
    return m_value;
}

Node* Node::getNext()
{
    return m_next;
}

Node* Node::getParent()
{
    return m_parent;
}

void Node::setValue(std::string value)
{
    m_value = value;
}

void Node::setNext(Node* next)
{
    m_next = next;
}

void Node::setParent(Node* parent)
{
    m_parent = parent;
}