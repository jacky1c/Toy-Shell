//
//  Shell.hpp
//
//  Created by Jacky on 2017-09-11.
//  Copyright © 2017 Jacky. All rights reserved.
//

#ifndef Shell_h
#define Shell_h

#include <string.h> // strtok is used to tokenize command line
#include "Queue.h"
using namespace std;


class Shell{
private:
    string name;
    string terminator;
    Queue history; // history of commands
    int commandsCounter; // number of commands that have been entered in the current session
public:
    Shell();
    void SetName(string newName);
    string GetName();
    void SetTerminator(string newTerminator);
    string GetTerminator();
    void IncrementCommandsCounter();
    int GetCommandsCounter();
    void InsertHistory(string commandLine);
    void AllHistory(); // Print all latest history commands in queue (up to QUEUESIZE).
    string GetHistory(int n_th); // return the n-th command in history
    void Print(); // display the basic information of shell
    
    void DisplayCommandPrompt();
    string ReadCommand();
};


#endif /* Shell_h */
