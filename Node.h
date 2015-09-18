#ifndef __Lab5__Node__

#define __Lab5__Node__



#include <iostream>



template <typename T>

class Node

{

private:

    Node<T>* m_next;

    Node<T>* m_parent;

    T m_value;

public:

    /**

     *  @pre    None

     *  @post   Creates and initializes a Node class

     *  @return m_left and m_right have been set to NULL

     */

    Node();

    

    /**

     *  @pre    The template value T has been initialized

     *  @post   None

     *  @return The template value T has been returned

     */

    T getValue();

    

    /**

     *  @pre    m_left has been initialized

     *  @post   None

     *  @return m_left has been returned

     */

    Node<T>* getNext();

    

    Node<T>* getParent();

    

    /**

     *  @pre    None

     *  @post   template value T has been set to value

     *  @return None

     */

    void setValue(T value);

    

    /**

     *  @pre    None

     *  @post   m_left has been set to left

     *  @return None

     */

    void setNext(Node<T>* next);

    

    void setParent(Node<T>* parent);

};



#endif /* defined(__Lab5__Node__) */