//
//  LinkedList.hpp
//
//  Created by Jacky on 2017-09-10.
//  Copyright © 2017 Jacky. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdlib.h> // system function is used
#include <string.h> // strtok function is used
#include <iomanip> // setw function is used
using namespace std;

const char DELIMITER = ' '; // Set the default delimiter in the command line to one empty space
const int MAXLENGTH = 10; // Set the default length of alias list to 10

struct Node{
    string alias;
    string command;
    Node* nextNode;
};

class LinkedList{
private:
    Node* rootNode;
    Node* currentPosition;
    int length;
public:
    LinkedList();
    void Insert(string alias, string command); // Insert a pair of alias and command
    Node* FindAlias(string alias); // Return a pair of alias and command that containing alias
    Node* FindCommand(string command); // Return a pair of alias and command that containing command
    void Delete(string command); // Delete the node containing command. Throw an error msg if command cannot be found
    void Print(); // Print all pairs of alias and command
    int GetLength(); // Return the number of pairs of alias and command
    Node* GetNextNode();
    void ResetCurrPos();
};

#endif /* LinkedList_h */
