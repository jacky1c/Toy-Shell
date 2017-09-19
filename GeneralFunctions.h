//
//  CommandFunctions.h
//
//  Created by Jacky on 2017-09-09.
//  Copyright © 2017 Jacky. All rights reserved.
//

#ifndef GeneralFunctions_h
#define GeneralFunctions_h

#include <iostream>
#include <stdlib.h> // system function is used
#include <string.h> // strtok function is used
#include <fstream> 
#include "LinkedList.h"
#include "Shell.h"


using namespace std;


const string ALIASESFILE = "aliases.txt";
const string CONFIGFILE = "config.txt";

/** Define status code for ExecutionFunction. **/
const int SUCCESS = 0;
const int STOP = -1;
const int UNDEFINED = 999;
/**************************************************/


void TokenizeCommandLine (string commandLine, char* tokens[], int& numOfTokens); // Tokenize the command line
int ExecutionFunction (char* tokens[], int numOfTokens, char* oldTokens[], int oldNumOfTokens, Shell& shell, LinkedList& aliasList); // Call the function corresponding to the command. Exception could be throwed
string SubstituteAlias (char* tokens[], int& numOfTokens, LinkedList aliasList); // convert tokens array to a string with no alias

void SetName(Shell& shell, const string newName, const string fileName);
void SetTerminator(Shell& shell, const string newTerminator, const string fileName);
void NewName(LinkedList& aliasList); // defines alias for command
void DeleteAlias(LinkedList& aliasList);
void LoadFromAliasFile(LinkedList& aliasList, string fileName);
void SaveToAliasFile(LinkedList& aliasList, string fileName);

#endif /* CommandFunctions_h */
