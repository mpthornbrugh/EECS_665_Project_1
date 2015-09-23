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

    std::string* nfaArray[numStates];

    Node* cur;

    for (int i = 0; i < numStates; i++) {
        nfaArray[i] = new Node();
        cur = nfaArray[i];
        for (int j = 0; j < stateCount; j++) {
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

    for (int i = 0; i < numStates; i++) {
        printStates(nfaArray[i]);
        std::cout << std::endl;
    }

    return 0;
}

