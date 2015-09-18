//

//  Node.h

//  Lab_4_EECS_560

//

//  Created by Michael Thornbrugh on 2/26/15.

//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.

//



//

//  Node.h

//  Lab5

//

//  Created by Michael Thornbrugh on 3/7/14.

//  Copyright (c) 2014 Michael Thornbrugh. All rights reserved.

//



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