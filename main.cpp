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

std::string removeBraces(std::string s) {
	s.erase(0, 1);
	s.erase(s.size() - 1);
	return s;
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

    Node<std::string> statesRoot;

    

    return 0;
}

