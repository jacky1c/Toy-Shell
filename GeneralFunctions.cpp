//
//  GeneralFunctions.cpp
//
//  Created by Jacky on 2017-09-09.
//  Copyright © 2017 Jacky. All rights reserved.
//

#include "GeneralFunctions.h"

/**
 Function Name: TokenizeCommandLine
 
 Purpose:
    Tokenize the command line
 
 Parameters:
    commandLine: the command line got from user
    tokens[]: an empty array of char pointers (return value)
    numOfTokens: number of tokens in [tokens] array (return value)
 **/
void TokenizeCommandLine (string commandLine, char* tokens[], int& numOfTokens){
    numOfTokens = 0;
    tokens[numOfTokens] = strtok(strdup(commandLine.c_str()), &DELIMITER);
    while (tokens[numOfTokens] != NULL){
        numOfTokens++;
        tokens[numOfTokens] = strtok(NULL, &DELIMITER);
    }
    // TEST, display all the tokens
//    cout<< "numOfTokens = "<< numOfTokens<< endl;
//    cout<< "Parsed tokens are:"<< endl;
//    for(int i=0; i<numOfTokens; i++)
//        cout<< tokens[i]<< ", ";
//    cout<< endl;
}

/**
 Function Name: ExecutionFunction
 
 Purpose:
     Call the function corresponding to the command.
     Return [STOP] if command is "stop".
     Return [SUCCESS] if command(other than "stop") is executed successfully.
     Return [UNDEFINED] if command is neither a defined command nor a UNIX/LINUX command
 
 Parameters:
     tokens: an array of tokens parsed from command line. tokens[0] is command and the rest of the tokens are parameter(s).
     numOfTokens: the number of tokens in [tokens] array
 **/
int ExecutionFunction (char* tokens[], int numOfTokens, char* oldTokens[], int oldNumOfTokens, Shell& shell, LinkedList& aliasList){
    int status = UNDEFINED;
    
    if(numOfTokens == 0){
        
    }
    else{
        char* command = tokens[0];
        
        /* Terminate execution of the current shell session. */
        if(strcmp(command, "stop") == 0){
            status = STOP;
        }
        
        /* Change shell name and save new name to config file. */
        else if(strcmp(command, "setshellname") == 0){
            // If there is no argument, throw an exception
            if(numOfTokens == 1){
                throw "Lack of argument.\n";
            }
            // Otherwise, change shell name
            else{
                string newName = tokens[1];
                try{
                    SetName(shell, newName, CONFIGFILE);
                }
                catch(char const* msg){
                    throw msg;
                }
            }
        }
        
        /* Change shell terminator and save new terminator to config file. */
        else if(strcmp(command, "setterminator") == 0){
            // If there is no argument, throw an exception
            if(numOfTokens == 1){
                throw "Lack of argument.\n";
            }
            // Otherwise, change shell terminator
            else{
                string newTerminator = tokens[1];
                try{
                    SetTerminator(shell, newTerminator, CONFIGFILE);
                }
                catch(char const* msg){
                    throw msg;
                }
            }
        }
        
        
        /* Lists the commands that have been entered in the current session. */
        else if(strcmp(command, "history") == 0){
            shell.AllHistory();
        }
        
        
        /* Re-executes a command that has been previously executed in the current session. */
        else if(strcmp(command, "!") == 0){
            // If there is no argument, throw an exception
            if(numOfTokens == 1){
                throw "Lack of argument.\n";
            }
            // Otherwise, parameter should be a number between 1 to 10 (inclusive)
            else{
                string para = tokens[1];
                string commandLine; // A string to store the command get from the user
                char* tokens[30]; // An array to store tokens parsed from [commandLine]
                int numOfTokens; // Number of tokens in [tokens] array
                
                int n_th;
                
                // Convert string type parameter [para] to int type [n_th]
                if(para.length() > 2){ // if [para] is longer than 2 chars, it's invalid
                    throw "Invalid argument.\n";
                }
                else if(para.length() == 2){ // if [para] is 2-char long, it must be 10
                    if(para[0] != '1'){
                        throw "Invalid argument.\n";
                    }
                    else if(para[1] != '0'){
                        throw "Invalid argument.\n";
                    }
                    else{
                        n_th = 10;
                        // Get the 10th history
                        try{
                            commandLine = shell.GetHistory(n_th);
                            TokenizeCommandLine(commandLine, tokens, numOfTokens);
                            try{
                                status = ExecutionFunction(tokens, numOfTokens, oldTokens, oldNumOfTokens, shell, aliasList);
                                return status;
                            }
                            catch(string msg){
                                throw msg;
                            }
                            catch(char const* msg){
                                throw msg;
                            }
                        }
                        catch(char const * msg){
                            throw msg;
                        }
                    }
                }
                else{ // if [para] is 1-char long, it must be 1 - 9
                    if(para[0] >= '1' && para[0] <= '9'){
                        n_th = para[0] - 48;
                        // Get the n-th history
                        try{
                            commandLine = shell.GetHistory(n_th);
                            TokenizeCommandLine(commandLine, tokens, numOfTokens);
                            try{
                                status = ExecutionFunction(tokens, numOfTokens, oldTokens, oldNumOfTokens, shell, aliasList);
                                return status;
                            }
                            catch(string msg){
                                throw msg;
                            }
                            catch(char const* msg){
                                throw msg;
                            }
                        }
                        catch(char const * msg){
                            throw msg;
                        }
                    }
                    else{
                        throw "Invalid argument.\n";
                    }
                }
            }
        }
        
        
        /*  If there is only one parameter, it deletes the alias.
            Otherwise, it defines a new pair of alias and command.
         */
        else if(strcmp(command, "newname") == 0){
            // If there is no argument, throw an exception
            if(oldNumOfTokens == 1){
                throw "Lack of argument.\n";
            }
            
            // If there is only one argument, it deletes the alias.
            else if(oldNumOfTokens == 2){
                string aliasToDelete = oldTokens[1];
                
                try{
                    aliasList.Delete(aliasToDelete);
                }
                catch(string msg){
                    throw msg;
                }
            }
            
            // If there are at least two arguments, it defines a new pair of alias and command.
            // However we don't allow to define an alias is a part of its substitution.
            // For example, we don't allow "newname history history" or "newname ls ls -l".
            // We do allow "newname h history".
            else{
                // construct alias string from tokens
                string aliasToAdd = oldTokens[1];
                
                // construct command string from tokens
                string commandToAdd = "";
                commandToAdd += oldTokens[2];
                for(int i=3; i<oldNumOfTokens; i++){
                    commandToAdd = commandToAdd + " " + oldTokens[i];
                }
                
                // try to add alias and command to aliasList
                try{
                    aliasList.Insert(aliasToAdd, commandToAdd);
                }
                catch(string msg){
                    throw msg;
                }
            }
        }
        
        /* Output all the aliases that have been defined. */
        else if(strcmp(command, "newnames") == 0){
            aliasList.Print();
        }
        
        /* Stores all currently defined aliases in the file */
        else if(strcmp(command, "savenewnames") == 0){
            string fileName;
            if(numOfTokens == 1){
                throw "Lack of arguments.\n";
            }
            else{
                fileName = tokens[1];
                try{
                    SaveToAliasFile(aliasList, fileName);
                }
                catch(string msg){
                    throw msg;
                }
            }
        }
        
        /* Reads all aliases in the file and adds them to the aliases defined in the current session */
        else if(strcmp(command, "readnewnames") == 0){
            string fileName;
            if(numOfTokens == 1){
                throw "Lack of arguments.\n";
            }
            else{
                fileName = tokens[1];
                try{
                    LoadFromAliasFile(aliasList, fileName);
                }
                catch(string msg){
                    throw msg;
                }
            }
        }
        
        /* Command is either a UNIX/LINUX command or garbage */
        else{
            int status;
            // Try to execute the command as a UNIX/LINUX command
            // Construct command from tokens
            string unixCommand = "";
            
            
            for(int i=0; i<numOfTokens; i++){
                unixCommand = unixCommand + tokens[i] + " ";
            }
            
            status = system(unixCommand.c_str());
            
            //if(status == 0){ // a UNIX/LINUX command
                
            //}
            //else{ // garbage
                //throw "Invalid command.\n";
            //}
        }
        
    } // end of "else{}" which belongs to "if(numOfTokens == 0){}"
    
    return status;
}

void SetName(Shell& shell, const string newName, const string fileName){
    string oldName, oldTerminator;
    // Update name in config file
    // Read old name and old terminator from file
    ifstream inFile;
    inFile.open(fileName.c_str());
    if(inFile.is_open()){
        getline(inFile, oldName);
        getline(inFile, oldTerminator);
    }
    else{
        throw fileName + " cannot be found.\n" +
        "Cannot read from configuration file.\n";
    }
    inFile.close();
    // Then write new name and old terminator into file
    ofstream outFile;
    outFile.open(fileName.c_str());
    if(outFile.is_open()){
        outFile<< newName << '\n';
        outFile<< oldTerminator;
    }
    else{
        throw fileName + " cannot be found.\n" +
        "Shell name is not saved in configuration file.\n";
    }
    outFile.close();
    
    // Change [shell] name.
    shell.SetName(newName);
}


void SetTerminator(Shell& shell, const string newTerminator, const string fileName){
    string oldName, oldTerminator;
    
    // Update name in config file
    // Read old name and old terminator from file
    ifstream inFile;
    inFile.open(fileName.c_str());
    if(inFile.is_open()){
        getline(inFile, oldName);
        getline(inFile, oldTerminator);
    }
    else{
        throw fileName + " cannot be found.\n" +
        "Cannot read from configuration file.\n";
    }
    inFile.close();
    // Then write old name and new terminator into file
    ofstream outFile;
    outFile.open(fileName.c_str());
    if(outFile.is_open()){
        outFile<< oldName << '\n';
        outFile<< newTerminator;
    }
    else{
        throw fileName + " cannot be found.\n" +
        "Shell terminator is not saved in configuration file.\n";
    }
    outFile.close();
    
    // Change [shell] terminator.
    shell.SetTerminator(newTerminator);
}




/**
 Function Name: NewName
 
 Purpose:
 Insert a new pair of alias and command into [aliasList]
 Throw exception when alias already exists in [aliasList]
 
 Parameters:
 aliasList: alias list
 **/
//void NewName(LinkedList& aliasList){
//    string alias, command;
//    
//    cout<< "create a new pair of alias and command"<< endl;
//    cout<< "alias: ";
//    cin>>alias;
//    cout<< "command: ";
//    getline(cin, command); // consume the '\n' left from entering alias
//    getline(cin, command);
//    try {
//        aliasList.Insert(alias, command);
//    }
//    catch (string msg){
//        throw msg;
//    }
//}

/**
 Function Name: DeleteAlias
 
 Purpose:
 Delete a pair of alias and command from [aliasList]
 Throw exception when command does not exist in [aliasList]
 
 Parameters:
 aliasList: alias list
 **/
//void DeleteAlias(LinkedList& aliasList){
//    string command;
//    // delete a pair of alias and command
//    cout<< "delete a pair of alias and command"<< endl;
//    cout<< "command: ";
//    getline(cin, command);
//    try{
//        aliasList.Delete(command);
//    }
//    catch(string msg){
//        throw msg;
//    }
//}

/**
 Function Name: LoadAliasFile
 
 Purpose:
 Insert alias and command pairs from [fileName] to [aliasList]
 
 Note: 
 The format in alias file should be "<alias>empty_space<command>"
 
 Parameters:
 aliasList: alias list
 fileName: the source file storing alias and command pairs
 **/
void LoadFromAliasFile(LinkedList& aliasList, string fileName){
    string alias;
    string command;
    string aliasCommandPair;
    ifstream inFile;
    inFile.open(fileName.c_str());
    
    if(inFile.is_open()){
        // read alias and command pairs from file
        getline(inFile, aliasCommandPair);
        while(!inFile.eof()){
            // tokenize aliasCommandPair
            alias = strtok(strdup(aliasCommandPair.c_str()), &DELIMITER);
            //cout<< "alias = "<< alias<< endl; // TEST USE
            command = aliasCommandPair.substr(alias.length()+1);
            //cout<< "command = "<< command<< endl; // TEST USE
            // insert into alias list here...
            try{
                aliasList.Insert(alias, command);
            }
            catch(string msg){
                // if there is a duplicate alias, ignore it
            }
            // read next pair
            getline(inFile, aliasCommandPair);
        }
        inFile.close();
    }
    else{
        throw fileName + " does not exist.\n";
    }
}

/**
 Function Name: SaveAliasFile
 
 Purpose:
 Save [aliasList] to [fileName] and overwrite the file
 
 Note:
 The format in alias file is 
 <alias>empty_space<command>
 <alias>empty_space<command>
 <alias>empty_space<command>
 
 Parameters:
 aliasList: alias list
 fileName: the source file storing alias and command pairs
 **/

void SaveToAliasFile(LinkedList& aliasList, string fileName){
    ofstream outFile;
    outFile.open(fileName.c_str());
    Node* nodeTraverser;
    
    if(aliasList.GetLength() == 0){
        throw "Cannot store aliases in file.\nAliases list is empty.\n";
    }
    else{
        if(outFile.is_open()){
            aliasList.ResetCurrPos();
            for (int i=0; i<aliasList.GetLength(); i++) {
                nodeTraverser = aliasList.GetNextNode();
                outFile<< nodeTraverser->alias<< " "<< nodeTraverser->command<< endl;
            }
        }
        else{
            throw "Cannot store aliases in file.\n" + fileName + " does not exist.\n";
        }
        outFile.close();
    }
}

/*
 Function Name: SubstituteAlias
 
 Purpose:
 Convert tokens array to a string with no alias
 
 Parameter:
 tokens: tokens parsed from user input command line
 numOfTokens: the number of tokens in tokens array
 aliasList: a dictionary to fetch command for alias
 */
string SubstituteAlias (char* tokens[], int& numOfTokens, LinkedList aliasList){
    string newCommandLine = "";
    string originalCommand;
    Node* aliasCommandPair;
    char* newTokens[30]; // An array to store tokens parsed from [commandLine]
    int newNumOfTokens; // Number of tokens in [tokens] array
    
    /* Traverse each token in tokens[], if it's an alias, convert it into command.
     If token is not an alias, don't change the it.
     Append the command to newCommandLine
     */
    
    aliasCommandPair = aliasList.FindAlias(tokens[0]);
    if(aliasCommandPair == NULL){ // if tokens[i] is not an alias
        newCommandLine = newCommandLine + tokens[0]; // append it to newCommandLine
    }
    else{ // if tokens[i] is an alias
        // get the original command
        originalCommand = aliasCommandPair->command;
        newCommandLine = newCommandLine + originalCommand; // append it to newCommandLine
        
        // To make sure the command for an alias is not another alias, keep translating until there is no alias in the string
        TokenizeCommandLine(newCommandLine, newTokens, newNumOfTokens);
        newCommandLine = SubstituteAlias(newTokens, newNumOfTokens, aliasList);
    }
    
    for(int i=1; i<numOfTokens; i++){
        aliasCommandPair = aliasList.FindAlias(tokens[i]);
        if(aliasCommandPair == NULL){ // if tokens[i] is not an alias
            newCommandLine = newCommandLine + DELIMITER + tokens[i]; // append it to newCommandLine
        }
        else{ // if tokens[i] is an alias
            // get the original command
            originalCommand = aliasCommandPair->command;
            newCommandLine = newCommandLine + DELIMITER + originalCommand; // append it to newCommandLine
            
            // To make sure the command for an alias is not another alias, keep translating until there is no alias in the string
            TokenizeCommandLine(newCommandLine, newTokens, newNumOfTokens);
            newCommandLine = SubstituteAlias(newTokens, newNumOfTokens, aliasList);
            
        }
    }
    
    return newCommandLine;
}
