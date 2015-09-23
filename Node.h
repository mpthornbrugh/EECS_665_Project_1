#ifndef __Lab5__Node__
#define __Lab5__Node__

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

#endif /* defined(__Lab5__Node__) */