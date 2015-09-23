//
//  main.cpp
//  Project_1
//  EECS_665
//
//  Created by Michael Thornbrugh on 9/17/15.
//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <stdlib.h>
#include "Node.cpp"
#include "Node.h"

std::string findEClosure(Node** statesArray, int state, int numStates) {
    // Initialization
    bool visitedArr[numStates];
    for (int i = 0; i < numStates; i++) {
        visitedArr[i] = false;
    }
    std::string closure = "";

    // Create a double stack
    // The first stack keeps track of the Nodes to track next states
    // The second stack keeps track of the current node state
    std::stack<Node*> stack;
    std::stack<int> numStack;

    // Add on the initial state to the stacks
    stack.push(statesArray[state-1]);
    numStack.push(state);

    while (!stack.empty()) {
        // Get the next items of the double stack
        Node* current = stack.top();
        int currentNum = numStack.top();
        stack.pop();
        numStack.pop();

        // Add the state that we just got to the closure
        visitedArr[currentNum-1] = true;

        // Add any possibly visited states to the double stack
        while (current->getNext() != NULL) {
            current = current->getNext();
        }
        std::string possibleMoves = current->getValue();
        // If there is somewhere to go along E
        if (possibleMoves.compare("") != 0) {
            // Loop over all states
            while (possibleMoves.compare("") != 0) {
                // Get the first state to move to
                std::string substring = possibleMoves.substr(0, 1);
                possibleMoves = possibleMoves.erase(0, 1);
                // Since we only get once character it will grab the ','
                if (substring.compare(",") != 0) {
                    // Push this state onto the stack
                    int newNum = atoi(substring.c_str());
                    stack.push(statesArray[newNum - 1]);
                    numStack.push(newNum);
                }
            }
        }
    }

    for (int i = 0; i < numStates; i++) {
        if (visitedArr[i]) {
            closure += string(itoa(i+1));
            closure += ",";
        }
    }
    closure.erase(closure.end()-1, 1);
    return closure;
}

void printStates(Node* root) {
	while (root->getNext() != NULL) {
		std::cout << root->getValue() << " | ";
		root = root->getNext();
	}
	std::cout << root->getValue();
    std::cout << std::endl;
}

void printArray(Node** arr, int x) {
    for (int i = 0; i < x; i++) {
        printStates(arr[i]);
        std::cout << std::endl;
    }
}

int getNumStates(Node* root) {
    int count = 0;
    while (root->getNext() != NULL) {
        count++;
        root = root->getNext();
    }
    count++;
    return count;
}

std::string removeBraces(std::string s) {
	s.erase(0, 1);
	s.erase(s.size() - 1);
	return s;
}

void addState(Node* root, std::string state) {
	if (root->getValue().compare("Not Initialized") == 0) {
		root->setValue(state);
		return;
	}

	Node* current = root;
	
	while (current->getNext() != NULL) {
		current = current->getNext();
	}

	Node* newNode = new Node();
	newNode->setValue(state);

	current->setNext(newNode);
}

int main(int argc, const char * argv[])
{   
    std::string x;

    for (int i = 0; i < 2; i++) {//Removing 'Initial State'
    	std::cin >> x;
    }

    std::cin >> x;

    x = removeBraces(x);

    int initialState = atoi(x.c_str());

    for (int i = 0; i < 2; i++) {//Removing 'Final State'
    	std::cin >> x;
    }

    std::cin >> x;

    x = removeBraces(x);

    int finalState = atoi(x.c_str());

    for (int i = 0; i < 2; i++) {//Removing 'Total States'
    	std::cin >> x;
    }

    std::cin >> x;

    int numStates = atoi(x.c_str());

    std::cout << "Start State: " << initialState << std::endl;
    std::cout << "Final State: " << finalState << std::endl;
    std::cout << "Number of States: " << numStates << std::endl;

    Node* statesRoot = new Node();

    std::cin >> x;//Removing 'State'

    while (1) {
    	std::cin >> x;
    	if (atoi(x.c_str()) == initialState) {
    		break;
    	}
    	addState(statesRoot, x);
    }

    int stateCount = getNumStates(statesRoot);

    std::string statesArray[stateCount];
    Node* temp = statesRoot;
    int tempCount = 0;

    while (temp->getNext() != NULL) {
        statesArray[tempCount] = temp->getValue();
        tempCount++;
        temp = temp->getNext();
    }
    statesArray[tempCount] = temp->getValue();

    Node* nfaArray[numStates];

    Node* cur;

    for (int i = 0; i < numStates; i++) {
        nfaArray[i] = new Node();
        cur = nfaArray[i];
        std::cin >> x;
        x = removeBraces(x);
        if (x.compare("") == 0) {
            cur->setValue("");
        }
        else {
            cur->setValue(x);
        }
        for (int j = 0; j < stateCount - 1; j++) {
            std::cin >> x;
            x = removeBraces(x);
            if (x.compare("") == 0) {
                Node* newNode = new Node();
                newNode->setValue("");
                cur->setNext(newNode);
            }
            else {
                Node* newNode = new Node();
                newNode->setValue(x);
                cur->setNext(newNode);
            }
            cur = cur->getNext();
        }
        std::cin >> x; //Removes the State Number
    }

    std::string initialEClosure = findEClosure(nfaArray, initialState, numStates);

    std::cout << initialEClosure << std::endl;

    return 0;
}

