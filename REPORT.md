# User Thread Library

## Summary

The goal of this project is to build a basic user-level thread library `libuthread.a` for Linux. This library provides a complete interface for applications to creat and run independent threads concurrently. It is able to create new threads, schedule the execution threads in a round-robin fashion, and provide a thread synchronization API, namely semaphores (ECS 150_Project #2 - User-level thread library).


## Implementation

The implementation of this program has three main parts:

1. Implementing a queue container for system programming
2. Implementing the thread management API `uthread.c` using internal context API `context.c` for applications to create, terminate, or manipulate threads
3. Implementing the semaphore API `sem.c` to control the access to common resources by multiple threads



### Parsing options

At the beginning of program execution, `sshell` runs function `arg_parser()` 
which parses the incoming command line (i.e., `cmd`) into command and arguments 
(i.e., `command` and `arg[i]`).
All command line information is stored in an object data structure called 
`struct cmdLine`. We can then access this information by passing the object 
into our functions.
On occasions when special commands are detected in arguement, function 
`command_handler()` is executed. `command_handler()` contains all function calls
to perform builtin commands: exit, cd, pwd, and directory stack interactions.
Otherwise, function `system_call()` is executed. `system_call()` contains all 
function calls to perform specific command executions using external executable 
files.
`execvp()` sereaches for the file path automatically for execution and take in 
char *ptr arguements.

### Redirection
Upon program excution `arg_parser()` identifies the `>` or `<` symbol. It stores
 the immediate arguemnt after the symbol into `file`. This will later be used as
  filename for file manipilation.

### Piping
The parsing for piping takes two steps. First, `arg_parser()` is called to parse
 the command line into processes. `arg_parser()` is called again in `piping()` 
 where each process is parsed into command and arguments.
Details...
use of for loop
1. Create pipes and file descriptors; the number of them are equal to the number
 of pipe signs in command.
2. Use of for loop to iterate each process.
3. For each iteration, fork once. 
4. In the child section, send fd[0] to STDIN, and if it is the last process that
need to be executed, send fd[1] to STDOUT. In this way, the previous process's 
output could be the current process's input. 
5. In the parent section, close the previous file descriptor for security.

### Directory Stack
Directory is stored in a stack, implemented using a singly linked list `struct 
ListNode`.  A singly linked list allows an arbitrary number of paths and fast 
access.
This singly linked list contains two pointers, one to store the current 
directory, the other points to the next object.
Directory stack `struct listNode *ds` serves as the head node. 
New node is created in `push_directory()`. It is appended after `ds`, with its 
next pointer pointing to the previous directory. This way the stack keeps track 
of a history of directory, from the most recent down to the first.

### Reference program and testing
Compile `sshell.c` using `makefile` to generate a executable `sshell`. And ran 
the provided test code `./tester.sh`.

## License

This work is distributed under the [GNU All-Permissive
License](https://spdx.org/licenses/FSFAP.html).

Copyright 2022, Betty and Aileen, ECS150
