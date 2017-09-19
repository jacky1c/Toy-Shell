//
//  Queue.h
//
//  Created by Jacky on 2017-09-10.
//  Copyright © 2017 Jacky. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <iostream>
#include <stdlib.h> // system function is used
#include <string.h> // strtok function is used
#include <iomanip> // setw function is used
using namespace std;

const int QUEUESIZE = 10;

// A queue of commands. Maximum size is MAXHISTORY.
class Queue{
private:
    string commands[QUEUESIZE];
    int length; // size of the array
public:
    Queue(); // default constructor
    void Enqueue(string newCommand);
    void Dequeue();
    string GetElement(int position); // get the [position]th element in [commands] array. [position] should be checked before function call
    int GetLength(); // get the size of the array
    void Print();
};

#endif /* Queue_h */
