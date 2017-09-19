//
//  LinkedList.cpp
//
//  Created by Jacky on 2017-09-10.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "LinkedList.h"

/**
 Function Name: LinkedList
 Purpose:
    Default constructor. Set [rootNode] pointing to NULL.
 **/
LinkedList::LinkedList(){
    rootNode = NULL;
    length = 0;
}

/**
 Function Name: Insert
 Purpose:
 Insert a pair of alias and command if alias doesn't exist.
 Otherwise, throw an exception.
 **/
void LinkedList::Insert(string alias, string command){
    bool duplicate = false;
    Node* newNode = new Node;
    char* token;
    
    newNode->alias = alias;
    newNode->command = command;
    
    // use a loop to check whether the second argument contains the first argument
    token = strtok(strdup(command.c_str()), &DELIMITER);
    while (token != NULL){
        if(alias == token){
            duplicate = true;
        }
        token = strtok(NULL, &DELIMITER);
    }
    
    // if the second argument contains the first argument, we throw an exception
    if(duplicate){
        throw "Alias cannot be defined.\nAlias is a part of command.\n";
    }
    
    // if the length of alias list is at MAXLENGTH, we throw and exception
    else if(length >= MAXLENGTH){
        throw "Alias cannot be defined.\nThe maximum number of aliases is reached.\n";
    }
    
    // otherwise, we define a new pair of alias and command
    else{
        if(FindAlias(alias) != NULL){ // if alias exists in the list, new command replaces old commmand
            FindAlias(alias)->command = command;
        }
        else if(FindCommand(command) != NULL){ // if command exists in the list, new alias replaces the old alias
            FindCommand(command)->alias = alias;
        }
        else{
            // if the list is empty, make rootNode point to the new node.
            if(rootNode == NULL){
                rootNode = newNode;
                newNode->nextNode = NULL;
            }
            // otherwise, insert new node at the beginning of the list.
            else{
                newNode->nextNode = rootNode;
                rootNode = newNode;
            }
            length++;
        }
    }
    
    return;
}

/**
 Function Name: FindAlias
 Purpose:
    Return a pointer pointing to the node which contains [alias].
    Return NULL if [alias] cannot be found in linked list.
 Parameter:
    alias: an alias that we want to search in linked list
 **/
Node* LinkedList::FindAlias(string alias){
    Node* scanner;
    scanner = rootNode;
    
    while(scanner != NULL){
        if(scanner->alias == alias){
            return scanner;
        }
        else{
            scanner = scanner->nextNode;
        }
    }
    
    return NULL; // can't find alias
}

/**
 Function Name: FindAlias
 Purpose:
 Return a pointer pointing to the node which contains [alias].
 Return NULL if [alias] cannot be found in linked list.
 Parameter:
 alias: an alias that we want to search in linked list
 **/
Node* LinkedList::FindCommand(string command){
    Node* scanner;
    scanner = rootNode;
    
    while(scanner != NULL){
        if(scanner->command == command){
            return scanner;
        }
        else{
            scanner = scanner->nextNode;
        }
    }
    
    return NULL; // can't find command
}

/**
 Function Name: Delete
 
 Purpose:
    Delete the pair of alias and command that contains [command].
    Throws exception if [command] cannot be found.
 
 Parameter:
    alias: the alias which we want to delete.
 **/
void LinkedList::Delete(string alias){
    
    Node *scanner, *detector;
    scanner = rootNode; // [detector] always point to the next node of [scanner]
    detector = NULL; // use detector to find the node containing [command]
    
    if(scanner == NULL){ // empty list
        throw "Alias cannot be deleted.\nEmpty alias list.\n";
    }
    else{
        if(scanner->alias == alias){ // if alias exists at the first position, delete the node
            rootNode = scanner->nextNode;
            delete scanner;
            length --;
            return;
        }
        else{ // if alias is not found at the first position, we use detector to find alias
            detector = scanner->nextNode;
            while(detector != NULL){
                if(detector->alias == alias){ // alias exists in the list, delete the node
                    scanner->nextNode = detector->nextNode;
                    delete detector; // PROBLEM HERE
                    length --;
                    return;
                }
                else{ // move [detector] and [scanner] down one node
                    detector = detector->nextNode;
                    scanner = scanner->nextNode;
                }
            }
            throw "Alias cannot be deleted.\n" + alias + " does not exist.\n"; // alias doesn't exist in the list
        }
    }
}

void LinkedList::Print(){
    Node* scanner = rootNode;
    if(length == 0){
        cout<< "Empty alias list."<< endl;
    }
    else{
        cout<< setw(10) << left << "Alias"<< ": Command" << endl;
        while(scanner != NULL){
            cout<< setw(10) << left << scanner->alias << ": "<< scanner->command << endl;
            scanner = scanner->nextNode;
        }
    }
}

int LinkedList::GetLength(){
    return length;
}

void LinkedList::ResetCurrPos(){
    currentPosition = NULL;
}

Node* LinkedList::GetNextNode(){
    Node* result;
    
    if (currentPosition == NULL)
        currentPosition = rootNode;
    result = currentPosition;
    currentPosition = currentPosition->nextNode;
    return result;
}
