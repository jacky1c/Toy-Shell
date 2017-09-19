# Toyshell

### The commands that are supported in this shell program:
a. STOP: 
Terminates execution of the current toyshell session.
b. SETSHELLNAME <shell_name>: 
Sets the shell name in the toyshell command prompt to <shell_name>.
c. SETTERMINATOR <terminator>: 
Sets the terminator in the toyshell command prompt to <terminator>. If no terminator is defined, toyshell should use -> as the default terminator.
d. HISTORY: 
Lists the commands that have been entered in the current session (i.e., since the last time toyshell was run). The maximum number of commands in the history list should be set to 10 as the default.
e. ! <n>: 
Re-executes a command that has been previously executed in the current session. The command will execute the n-th command in the history list. For example, the command ! 6 will cause the 6-th command to be executed again.
f. NEWNAME <new_name> | <new_name> <old_name>: 
Manages the alias list. The first option deletes a previously defined alias. The second option defines an alias for another command. For example, the command NEWSMAN mymove deletes the command for mymove, and the command NEWNAME mycopy cp defines mycopy as the alias for the cp command. If an alias for a command already exists, then the new alias replaces the old alias. The maximum number of aliases in the alias list should be set to 10 as the default.
g. Alias Substitution: 
When an alias is detected in a command, the old name should be substituted into the command before the command is executed.
h. NEWNAMES: 
Outputs all the aliases that have been defined. Each pair of names should be shown on one line.
i. SAVENEWNAMES <file_name>: 
Stores all currently defined aliases in the file <file_name>.
j. READNEWNAMES <file_name>: 
Reads all aliases in the file <file_name> and adds them to the aliases defined in the current session. If a duplicate is found in the file <file_name>, it should be ignored.
k. <UNIX_command>: 
Executes the UNIX command <UNIX_command>, corresponding to any valid UNIX command. One approach to implementing this is to use the system function. If the first token on a command line is not a built-in command, assume that it is a UNIX command.



### Files structure:
toyshell.cpp calls GeneralFunctions.cpp(contains all command functions)
GeneralFunctions.cpp calls LinkedList.cpp(for alias list) and Shell.cpp
Shell.cpp calls Queue.cpp(for command history)

### Exceptions List:
• Shell configuration file cannot be found.
• Lack of argument
• Invalid argument
• Invalid command/ Command not found
• Cannot store aliases in file. Alias list is empty
• Cannot read from alias file. File does not exist
• History does not exist.
• Alias cannot be defined
  • Alias is part of command
  • The maximum number of aliases is reached
• Alias cannot be deleted
  • Empty alias list
  • Alias does not exist


Created by Jacky on 2017-09-08.
Copyright © 2017 Jacky. All rights reserved.
