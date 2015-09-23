//
//  Node.h
//  Project_1
//  EECS_665
//
//  Created by Michael Thornbrugh on 9/17/15.
//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.
//

#ifndef __Node__
#define __Node__

#include <iostream>

class Node
{
private:
    Node* m_next;
    Node* m_parent;
    std::string m_value;
public:
    Node();
    
    std::string getValue();
    
    Node* getNext();
    
    Node* getParent();
    
    void setValue(std::string value);
    
    void setNext(Node* next);
    
    void setParent(Node* parent);
};

#endif /* defined(__Node__) */