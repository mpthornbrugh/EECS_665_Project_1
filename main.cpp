//
//  main.cpp
//  Project_1
//
//  Created by Michael Thornbrugh on 9/17/15.
//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Node.cpp"
#include "Node.h"

void printStates(Node* root) {
	while (root->getNext() != NULL) {
		std::cout << root->getValue() << " | ";
		root = root->getNext();
	}
	std::cout << root->getValue();
    std::cout << std::endl;
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
	std::cout << "Adding " << state << std::endl;
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

    std::string statesArray[getNumStates(statesRoot)];
    Node* temp = statesRoot;
    int tempCount = 0;

    while (temp->getNext() != NULL) {
        statesArray[tempCount] = temp->getValue();
        tempCount++;
        temp = temp->getNext();
    }
    statesArray[tempCount] = temp->getValue();

    for (int i = 0; i < getNumStates(statesRoot); i++) {
        std::cout << statesArray[i] << std::endl;
    }

    // printStates(statesRoot);
    // std::cout << getNumStates(statesRoot) << std::endl;
    //Currently x has the number of the initialState

    return 0;
}

