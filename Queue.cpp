//
//  Queue.cpp
//
//  Created by Jacky on 2017-09-10.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "Queue.h"

/**
 Function Name: Queue
 Purpose:
    Default constructor. Set all commands to "EMPTY"
 **/
Queue::Queue(){
    for(int i=0; i<QUEUESIZE; i++){
        commands[i] = "EMPTY";
    }
    length = 0;
}

/**
 Function Name: Push
 Purpose:
    Add a new element in [commands] array.
    When the array is full, pop the queue and then push the new element.
 Parameter:
    newCommand
 **/
void Queue::Enqueue(string newCommand){
    if(length<QUEUESIZE){
        commands[length] = newCommand;
        length++;
    } else{
        Dequeue();
        Enqueue(newCommand);
    }
}

/**
 Function Name: Pop
 Purpose:
    Shift elements from index1 to index9 up one position.
 **/
void Queue::Dequeue(){
    for(int i=1; i<QUEUESIZE; i++){
        commands[i-1] = commands[i];
    }
    commands[QUEUESIZE-1] = "EMPTY";
    length--;
}

/**
 Function Name: GetElement
 Purpose:
    Return the [position]th element in [commands] array.
 Parameter:
    position: should be less or equal to [numOfCommands]
 **/
string Queue::GetElement(int position){
    return commands[position];
}

/**
 Function Name: GetElement
 Purpose:
    Return the size of the array.
 **/
int Queue::GetLength(){
    return length;
}

/**
 Function Name: Print
 Purpose:
    Display all non-empty elements in the array
 **/
void Queue::Print(){
    if(length == 0)
        cout<< "There is no history command"<< endl;
    
    for(int i=0; i<length; i++){
        cout<< "("<< setw(2) << i+1 << ") "<< commands[i]<< endl;
    }
}
