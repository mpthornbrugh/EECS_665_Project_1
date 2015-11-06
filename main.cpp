//
//  main.cpp
//  Project_1
//  EECS_665
//
//  Created by Michael Thornbrugh on 9/17/15.
//  Copyright (c) 2015 Michael Thornbrugh. All rights reserved.
//

#include <iostream> // Used for output
#include <string>   // Used for all of the strings used throughout
#include <queue>    // Used for running the scheduling for the conversion
#include <stack>    // Used for the move and find E-closure functions
#include <sstream>  // Used for integer to string conversions
#include <stdio.h>  // Used for string to integer conversion
#include <stdlib.h> // Used for string to integer conversions
#include "Node.cpp" // Code file of the Node class used to make a linked list
#include "Node.h"   // Header file for the Node class

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
    bool statesAlreadyVisited[numStates];
    for (int i = 0; i < numStates; i++) {
        statesAlreadyVisited[i] = false;
    }

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
                if (statesAlreadyVisited[newNum-1]) {
                    continue;
                }
                //stack.push(statesArray[newNum - 1]); Removed the recursion
                visitedArr[newNum - 1] = true;
                statesAlreadyVisited[newNum-1] = true;
            }
        }
    }

    // Loop through the visited array in order to determine which nodes have been reached.
    // This also handles removing duplicates.
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
    bool statesAlreadyVisited[numStates];
    for (int i = 0; i < numStates; i++) {
        statesAlreadyVisited[i] = false;
    }

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
                if (statesAlreadyVisited[newNum-1]) {
                    continue;
                }
                stack.push(statesArray[newNum - 1]);
                numStack.push(newNum);
                statesAlreadyVisited[newNum-1] = true;
            }
        }
    }

    // Loop through the visited array in order to determine which nodes have been reached.
    // This also handles removing duplicates.
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
    /*########################################################################################################################
    *               Start | Receiving Inputs
    ########################################################################################################################*/
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
        // Need this outside of the next loop because it is the root node
        if (x.compare("") == 0) {
            cur->setValue("");
        }
        else {
            cur->setValue(x);
        }
        // Loop through each remaining state and add another node to the list of that state
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

    /*########################################################################################################################
    *               End | Receiving Inputs
    ########################################################################################################################*/

    /*########################################################################################################################
    *               Start | Calculating DFA
    ########################################################################################################################*/

    std::string eClosures[numStates];
    for (int i = 0; i < numStates; i++) {
        eClosures[i] = "";
    }
    int highestEClosure = 0;

    // Initializing some variables
    int numEndingStates = 0;
    std::stringstream ss;
    ss << initialState;

    // Calculate initial E-closure
    std::string initialEClosure = findEClosure(nfaArray, ss.str(), numStates);
    eClosures[highestEClosure] = initialEClosure;
    highestEClosure++;
    numEndingStates++;

    // Display the E-closure formatted nicely
    std::cout << "E-closure(I0) = {" << initialEClosure << "} = " << highestEClosure << std::endl << std::endl;

    // Create the E-closure queue which will control what states to mark and check
    std::queue<std::string> EClosureQueue;
    EClosureQueue.push(initialEClosure);

    // Create and add the initial E-closure to the dStates variable.
    Node* dStates = new Node();
    dStates->setValue(initialEClosure);

    // This variable will be used to create the linking between the states in the DFA
    std::string mappings = "";

    int markNum = 1; // Used for output and mapping

    // Loop through every possible linking.
    while (!EClosureQueue.empty()) {
        // Get the next state to check
        std::string currentState = EClosureQueue.front();
        EClosureQueue.pop();

        std::cout << "Mark " << markNum << std::endl;

        // Keep track of the current marked state for use in mapping
        ss.str("");
        ss << markNum;
        std::string markedState = ss.str();

        markNum++;

        // Loop through all of the states excluding the E path
        for (int i = 0; i < stateCount-1; i++) {
            // Move the                  current State along     a,b,c,d, etc...
            std::string moveState = move(currentState, nfaArray, statesArray[i] , i, numStates);

            // Check if any states can be moved to from the current state along statesArray[i]
            if (moveState.compare("") != 0) {
                std::cout << "{" << currentState << "} --" << statesArray[i] << "--> {" << moveState << "}" << std::endl;
std::cout << "Hey1" << std::endl;
                // Get new E Closure of the moveState
                std::string moveEClosure = findEClosure(nfaArray, moveState, numStates);
std::cout << "Hey2" << std::endl;                
                std::cout << "E-closure{" << moveState << "} = {" << moveEClosure << "}";

                int location = -1;
                //Loop through all EClosures to find the eclosure equal to the current one or create a new EClosure.
                for (int j = 0; j < highestEClosure; j++) {
                    if (eClosures[j].compare(moveEClosure) == 0) {
                        location = j+1;
                    }
                }
                if (location == -1) {
                    //Need to create a new E Closure
                    eClosures[highestEClosure] = moveEClosure;
                    highestEClosure++;
                    location = highestEClosure;
                }

                // Add E Closure to dStates
                if (!inList(moveEClosure, dStates)) {
                    numEndingStates++;
                    EClosureQueue.push(moveEClosure);
                    addState(dStates, moveEClosure);
                }
                // Create the mapping between the currently marked state and the recently added state.
                ss.str("");
                ss << location;
                mappings += markedState + "," + statesArray[i] + "," + ss.str() + "|";
                std::cout << " = " << location << std::endl;
            }
        }

        std::cout << std::endl;
    }

    // Output formatted
    std::cout << "Initial State: {1}" << std::endl;
    std::cout << "Final States: {" << getFinalStates(dStates, finalState) << "}" << std::endl;

    std::cout << "State\t";
    for (int i = 0; i < stateCount - 1; i++) {
        std::cout << statesArray[i] << "\t";
    }
    std::cout << std::endl;

    // Initialize variables for mapping calculations
    int currentState = 0;
    std::size_t breakPos = mappings.find('|');
    std::string currentSubstring = mappings.substr(0, breakPos);
    mappings = mappings.substr(breakPos+1);

    // Loop through each ending mapping
    for (int i = 0; i < ((stateCount - 1)*getNumStates(dStates)); i++) {
        // If we are in a new state print out the state number
        if (i % (stateCount-1) == 0) {
            ss.str("");
            ss << ++currentState;
            std::cout << ss.str() << "\t";
        }

        // This will flip between the available states a then b then a or a then b then c then a
        std::string currentCheckState = statesArray[i % (stateCount-1)];

        // If the current substring from the mapping corresponds to our current state
        if (atoi(currentSubstring.substr(0,1).c_str()) == currentState) {
            // If the current substring from the mapping corresponds to our current state we are checking.
            if (currentSubstring.find(currentCheckState) != std::string::npos) {
                // Move over the two ,'s. We already checked for those.
                currentSubstring = currentSubstring.substr(currentSubstring.find(',')+1);
                currentSubstring = currentSubstring.substr(currentSubstring.find(',')+1);
                std::cout << "{" << currentSubstring << "}\t";
                // Need to do this logic in the loop as well so that we don't miss a new line because we hit the correct cases
                if ((i+1) % (stateCount-1) == 0) {
                    std::cout << std::endl;
                }
                // Used so that we don't try to call a substring on an empty string
                if (mappings.compare("") == 0) {
                    currentSubstring = "";
                    continue;
                }
                // Create the new substring now that we have used up the last one.
                currentSubstring = mappings.substr(0, mappings.find('|'));
                mappings = mappings.substr(breakPos+1);
                continue;
            }
        }
        // Display that there is no mapping for this location.
        std::cout << "{}\t";
        // Display a new line if we are finished with a state.
        if ((i+1) % (stateCount-1) == 0) {
            std::cout << std::endl;
        }
    }

    /*########################################################################################################################
    *               End | Calculating DFA
    ########################################################################################################################*/

    return 0;
}

