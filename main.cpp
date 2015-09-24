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
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Node.cpp"
#include "Node.h"

// This function is used to find the number of state variables since the number is dynamic
int getNumStates(Node* root) {
    int count = 0;
    while (root->getNext() != NULL) {
        count++;
        root = root->getNext();
    }
    count++;
    return count;
}

// Function used after converting to determine which new states are the final states.
std::string getFinalStates(Node* root, std::string originalFinalStates) {
    std::string finalStates = "";

    int numNewStates = getNumStates(root);

    bool visitedArr[numNewStates];
    for (int i = 0; i < numNewStates; i++) {
        visitedArr[i] = false;
    }

    // Loop through all of the original final states
    while (originalFinalStates.compare("") != 0) {
        std::size_t commaPos = originalFinalStates.find(',');
        std::string substring;
        if (commaPos == std::string::npos) {
            substring = originalFinalStates;
            originalFinalStates = "";
        }
        else {
            substring = originalFinalStates.substr(0, commaPos);
            originalFinalStates = originalFinalStates.substr(commaPos+1);
        }
        // Loop through all of the new states
        for (int i = 0; i < numNewStates; i++) {
            std::string previousStateCorrelations = root->getValue();
            if (previousStateCorrelations.find(substring) != std::string::npos) {
                visitedArr[i] = true;
            }
            if (root->getNext() == NULL) {
                break;
            }
            root = root->getNext();
        }
    }

    for (int i = 0; i < numNewStates; i++) {
        if (visitedArr[i]) {
            std::stringstream ss;
            ss << (i+1);
            finalStates += ss.str();
            finalStates += ",";
        }
    }
    finalStates = finalStates.substr(0, finalStates.size() - 1);

    return finalStates;
}

// Function used to determine whether a state is already in dStates or not
bool inList(std::string newState, Node* root) {
    while (root->getNext() != NULL) {
        if (root->getValue().compare(newState) == 0) {
            return true;
        }
        else {
            root = root->getNext();
        }
    }
    if (root->getValue().compare(newState) == 0) {
        return true;
    }
    return false;
}

// This function is used to calculate the move of a state along a specific term.
// The moveAlong is the term i.e. a,b,c,....
// The moveNumber is the number in the list the term is i.e b would be 2 in the example just above.
std::string move(std::string currentState, Node** statesArray, std::string moveAlong, int moveNumber, int numStates) {
    //Initialization
    bool visitedArr[numStates];
    for (int i = 0; i < numStates; i++) {
        visitedArr[i] = false;
    }
    std::string moveVal = "";

    // A stack used to track next nodes
    std::stack<Node*> stack;

    std::string possibleMoves = currentState;

    // Add the current states to the stack
    if (possibleMoves.compare("") != 0) {
        // Loop over all states
        while (possibleMoves.compare("") != 0) {
            // Get the first state to move to
            std::size_t commaPos = possibleMoves.find(',');
            std::string substring;
            if (commaPos == std::string::npos) {
                substring = possibleMoves;
                possibleMoves = "";
            }
            else {
                substring = possibleMoves.substr(0, commaPos);
                possibleMoves = possibleMoves.substr(commaPos+1);
            }
            int newNum = atoi(substring.c_str());
            stack.push(statesArray[newNum - 1]);
        }
    }  

    while (!stack.empty()) {
        // Get the next item off the stack
        Node* currentNode = stack.top();
        stack.pop();

        // Loop through the state to get to the need moving states
        for (int i = 0; i < moveNumber; i++) {
            currentNode = currentNode->getNext();
        }

        possibleMoves = currentNode->getValue();

        // Check that the current state has anywhere to go on the given moveAlong
        if (possibleMoves.compare("") != 0) {
            // Loop over all states
            while (possibleMoves.compare("") != 0) {
                // Get the first state to move to
                std::size_t commaPos = possibleMoves.find(',');
                std::string substring;
                if (commaPos == std::string::npos) {
                    substring = possibleMoves;
                    possibleMoves = "";
                }
                else {
                    substring = possibleMoves.substr(0, commaPos);
                    possibleMoves = possibleMoves.substr(commaPos+1);
                }
                int newNum = atoi(substring.c_str());
                stack.push(statesArray[newNum - 1]);
                visitedArr[newNum - 1] = true;
            }
        }
    }

    for (int i = 0; i < numStates; i++) {
        if (visitedArr[i]) {
            std::stringstream ss;
            ss << (i+1);
            moveVal += ss.str();
            moveVal += ",";
        }
    }
    moveVal = moveVal.substr(0, moveVal.size() - 1);
    return moveVal;
}

// This function is used to find the E Closure of a state
std::string findEClosure(Node** statesArray, std::string state, int numStates) {
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

    // Add the current states to the stack
    if (state.compare("") != 0) {
        // Loop over all states
        while (state.compare("") != 0) {
            // Get the first state to move to
            std::size_t commaPos = state.find(',');
            std::string substring;
            if (commaPos == std::string::npos) {
                substring = state;
                state = "";
            }
            else {
                substring = state.substr(0, commaPos);
                state = state.substr(commaPos+1);
            }
            // Push this state onto the stack
            int newNum = atoi(substring.c_str());
            stack.push(statesArray[newNum - 1]);
            numStack.push(newNum);
        }
    }

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
                std::size_t commaPos = possibleMoves.find(',');
                std::string substring;
                if (commaPos == std::string::npos) {
                    substring = possibleMoves;
                    possibleMoves = "";
                }
                else {
                    substring = possibleMoves.substr(0, commaPos);
                    possibleMoves = possibleMoves.substr(commaPos+1);
                }
                // Push this state onto the stack
                int newNum = atoi(substring.c_str());
                stack.push(statesArray[newNum - 1]);
                numStack.push(newNum);
            }
        }
    }

    for (int i = 0; i < numStates; i++) {
        if (visitedArr[i]) {
            std::stringstream ss;
            ss << (i+1);
            closure += ss.str();
            closure += ",";
        }
    }
    closure = closure.substr(0, closure.size() - 1);
    return closure;
}

// This function is used primarily for testing in order to display the state variables
void printStates(Node* root) {
	while (root->getNext() != NULL) {
		std::cout << root->getValue() << " | ";
		root = root->getNext();
	}
	std::cout << root->getValue();
    std::cout << std::endl;
}

// This function is used primarily for testing in order to dipslay the state tree
void printArray(Node** arr, int x) {
    for (int i = 0; i < x; i++) {
        printStates(arr[i]);
        std::cout << std::endl;
    }
}

// This is a helper function used in order to remove the { and } from strings
std::string removeBraces(std::string s) {
	s.erase(0, 1);
	s.erase(s.size() - 1);
	return s;
}

// This is used in order to create the state variable list
void addState(Node* root, std::string state) {
    // If the root isn't initialized then we are at the first state
	if (root->getValue().compare("Not Initialized") == 0) {
		root->setValue(state);
		return;
	}

	Node* current = root;
	
    // Go through the list and find the last element
	while (current->getNext() != NULL) {
		current = current->getNext();
	}

    // Add the new state onto the list.
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

    std::string finalState = x;

    for (int i = 0; i < 2; i++) {//Removing 'Total States'
    	std::cin >> x;
    }

    std::cin >> x;

    int numStates = atoi(x.c_str());

    Node* statesRoot = new Node();

    std::cin >> x;//Removing 'State'

    // Reading in the state variables into the statesRoot variable
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

    // This is used to convert the linked list version of the states into an array version making the states easier to access
    while (temp->getNext() != NULL) {
        statesArray[tempCount] = temp->getValue();
        tempCount++;
        temp = temp->getNext();
    }
    statesArray[tempCount] = temp->getValue();

    Node* nfaArray[numStates];

    Node* cur;

    // This is the logic to read in the remainder of the file and create the tree of states
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

    int numEndingStates = 0;

    std::stringstream ss;
    ss << initialState;

    std::string initialEClosure = findEClosure(nfaArray, ss.str(), numStates);
    numEndingStates++;

    std::cout << "E-closure(I0) = {" << initialEClosure << "} = " << numEndingStates << std::endl << std::endl;

    std::queue<std::string> EClosureQueue;
    EClosureQueue.push(initialEClosure);

    Node* dStates = new Node();
    dStates->setValue(initialEClosure);

    std::string mappings = "";

    int markNum = 1;

    while (!EClosureQueue.empty()) {
        std::string currentState = EClosureQueue.front();
        EClosureQueue.pop();

        std::cout << "Mark " << markNum << std::endl;

        ss.str("");
        ss << markNum;
        std::string markedState = ss.str();

        markNum++;

        for (int i = 0; i < stateCount-1; i++) {
            //std::cout << "move(" << currentState << ", " << statesArray[i] << ")" << std::endl;
            std::string moveState = move(currentState, nfaArray, statesArray[i] , i, numStates);

            if (moveState.compare("") != 0) {
                std::cout << "{" << currentState << "} --" << statesArray[i] << "--> {" << moveState << "}" << std::endl;

                // Get new E Closure of the moveState
                std::string moveEClosure = findEClosure(nfaArray, moveState, numStates);
                std::cout << "E-closure{" << moveState << "} = {" << moveEClosure << "}";

                // Add E Closure to dStates
                if (!inList(moveEClosure, dStates)) {
                    numEndingStates++;
                    EClosureQueue.push(moveEClosure);
                    addState(dStates, moveEClosure);
                }
                ss.str("");
                ss << numEndingStates;
                mappings += markedState + "," + statesArray[i] + "," + ss.str() + "|";
                std::cout << " = " << numEndingStates << std::endl;
            }
        }

        std::cout << std::endl;
    }

    std::cout << "Initial State: {1}" << std::endl;
    std::cout << "Final States: {" << getFinalStates(dStates, finalState) << "}" << std::endl;

    std::cout << "State\t";
    for (int i = 0; i < stateCount - 1; i++) {
        std::cout << statesArray[i] << "\t";
    }
    std::cout << std::endl;

    int currentState = 0;
    std::size_t breakPos = mappings.find('|');
    std::string currentSubstring = mappings.substr(0, breakPos);
    mappings = mappings.substr(breakPos+1);

    for (int i = 0; i < ((stateCount - 1)*getNumStates(dStates)); i++) {
        if (i % (stateCount-1) == 0) {
            ss.str("");
            ss << ++currentState;
            std::cout << ss.str() << "\t";
        }

        std::string currentCheckState = statesArray[i % (stateCount-1)];

        if (atoi(currentSubstring.substr(0,1).c_str()) == currentState) {
            if (currentSubstring.find(currentCheckState) != std::string::npos) {
                currentSubstring = currentSubstring.substr(currentSubstring.find(',')+1);
                currentSubstring = currentSubstring.substr(currentSubstring.find(',')+1);
                std::cout << "{" << currentSubstring << "}\t";
                if ((i+1) % (stateCount-1) == 0) {
                    std::cout << std::endl;
                }
                if (mappings.compare("") == 0) {
                    continue;
                }
                currentSubstring = mappings.substr(0, mappings.find('|'));
                mappings = mappings.substr(breakPos+1);
                continue;
            }
        }
        std::cout << "{}\t";
        if ((i+1) % (stateCount-1) == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << mappings << std::endl;

    return 0;
}

