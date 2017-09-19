//
//  toyshell.cpp
//
//  Created by Jacky on 2017-09-08.
//  Copyright © 2017 Jacky. All rights reserved.
//

/***** Program structure:
 int main(){
    Open the file to read the shell name.
    Open the file to read the terminator.
    Prime the loop (if necessary).
    Loop (condition){
        Print the command prompt. (i.e. toyshell[1]%)
        Read the command line.
        Call a function to tokenize the command line.
        Find what the command is if it's a history command.
        Check whether the command is an alias (function).
        Call a function to execute the command found.
        if(executable)
            continue;
        else
            Print error message. (i.e. Command is correct but the parameter is wrong)
    }
 
 ExecutionFunction(command, arguments parameters){
    if(stop){
 
    }
    else if (){}
    else{
        It's a UNIX/LINUX command,
        OR it could be a garbage.
    }
    return status;
 }
 ***************************************************************************/

#include "GeneralFunctions.h"


int main() {
    Shell shell;
    LinkedList aliasList;
    int status;
    
    string commandLine; // A string to store the command get from the user
    char* tokens[30]; // An array to store tokens parsed from [commandLine]
    int numOfTokens; // Number of tokens in [tokens] array
    
    string newCommandLine; // A string to store the command with no alias
    char* newTokens[30]; // An array to store tokens parsed from [commandLine]
    int newNumOfTokens; // Number of tokens in [tokens] array
    
    ifstream inFile(CONFIGFILE.c_str());
    string shellName;
    string shellTerminator;
    
    /* Open the file to read the shell name. Open the file to read the terminator. */
    if(inFile.is_open()){
        getline(inFile, shellName);
        getline(inFile, shellTerminator);
        shell.SetName(shellName);
        shell.SetTerminator(shellTerminator);
    }
    else{
        cerr<< "Shell configuration file " << CONFIGFILE << " cannot be found.\n"
        << "Using default shell configuration.\n";
    }
    inFile.close();
    
    /* Main loop body */
    do{
        /** Print the command prompt. (i.e. toyshell[1]%) **/
        shell.DisplayCommandPrompt();
        
        /** Read the command line. **/
        commandLine = shell.ReadCommand();
        
        /** Call a function to tokenize the command line. **/
        TokenizeCommandLine(commandLine, tokens, numOfTokens);
        
        if(numOfTokens == 0){
            continue;
        }
        else{
            /** Check whether the command is an alias (function). **/
            newCommandLine = SubstituteAlias(tokens, numOfTokens, aliasList);
            
            /** Call a function to tokenize the new command line without alias. **/
            TokenizeCommandLine(newCommandLine, newTokens, newNumOfTokens);

            /** Call a function to execute the command found. **/
            try{
                
// Test use: Display command
//                cout<< "command: ";
//                for(int i=0; i<newNumOfTokens; i++){
//                    cout<< newTokens[i]<< " ";
//                }
//                cout<< endl;
                
                status = ExecutionFunction(newTokens, newNumOfTokens, tokens, numOfTokens, shell, aliasList);
                if(status == STOP){
                    break; // exit the program
                }
            }
            catch(string msg){
                cerr<< msg;
            }
            catch(char const* msg){
                cerr<< msg;
            }
        }
        
    } while(true); // As long as user doesn't want to quit shell, print the command prompt again.
    
    // Quit shell
    return 0;
}


