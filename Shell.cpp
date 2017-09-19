//
//  Shell.cpp
//
//  Created by Jacky on 2017-09-11.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "Shell.h"

/**
 Function Name: Shell
 Purpose:
    Default constructor. Create a shell whose name is "toyshell" and terminator is "->'.
 **/
Shell::Shell(){
    name = "toyshell";
    terminator = "->";
    commandsCounter = 0;
}

/**
 Function Name: SetName
 Purpose:
    Change the shell name to [newName].
    But doesn't save [newName] to config file.
 Parameter:
    newName: new shell name
 **/
void Shell::SetName(string newName){
    name = newName;
}

/**
 Function Name: GetName
 Purpose:
    Return the shell name.
 **/
string Shell::GetName(){
    return name;
}

/**
 Function Name: SetTerminator
 Purpose:
     Change the terminator to [newTerminator].
     But doesn't save [newTerminator] to config file.
 **/
void Shell::SetTerminator(string newTerminator){
    terminator = newTerminator;
}

/**
 Function Name: GetTerminator
 Purpose:
    Return the terminator.
 **/
string Shell::GetTerminator(){
    return terminator;
}

/**
 Function Name: IncrementCommandsCounter
 Purpose:
    Increment commandsCounter by 1
 **/
void Shell::IncrementCommandsCounter(){
    commandsCounter++;
}

/**
 Function Name: GetTerminator
 Purpose:
 Return the terminator.
 **/
int Shell::GetCommandsCounter(){
    return commandsCounter;
}

/**
 Function Name: InsertHistory
 
 Purpose:
    Insert a command line to history queue.
    If the command line contains alias, save the command of alias instead of saving alias derectly.
 **/
void Shell::InsertHistory(string commandLine){
    history.Enqueue(commandLine);
}

/**
 Function Name: AllHistory
 Purpose:
    Print all latest history commands in queue (up to QUEUESIZE).
 **/
void Shell::AllHistory(){
    history.Print();
}

/**
 Function Name: GetHistory
 Purpose:
    Return the n-th command in history.
 
 Precondition: n_th is a number between 1 and 10 (inclusive)
 **/
string Shell::GetHistory(int n_th){
    if(n_th < history.GetLength()){
        return history.GetElement(n_th-1);
    }
    else{
        throw "History does not exist.\n";
    }
}

/**
 Function Name: Print
 Purpose:
    Print the basic information of shell
 **/
void Shell::Print(){
    cout<< "Name: "<< name<< endl;
    cout<< "Terminator: "<< terminator<< endl;
    cout<< "Total commands number: "<< commandsCounter<< endl;
    cout<< "Latest history commands:"<< endl;
    AllHistory();
}

/**
 Function Name: DisplayCommandPrompt
 Purpose:
    Display command prompt (i.e. toyshell[1]%)
 **/
void Shell::DisplayCommandPrompt(){
    cout<< name<< "["<< commandsCounter+1<< "]"<< terminator<< " ";
}

/**
 Function Name: ReadCommand
 Purpose:
    Read in one command line.
    Increment [commandsCounter].
    Insert the command to command history.
    Return the command read from user.
 **/
string Shell::ReadCommand(){
    string commandLine;
    
    getline(cin, commandLine);
    commandsCounter++;
    
    history.Enqueue(commandLine);
    
    return commandLine;
}
