# Mini-Shell

This project uses process management and system calls in Linux environment. To achieve this goal, C++ will be used to implement a mini shell that supports running programs not only in the foreground but also in the background: if a program is designated to run in the foreground, then shell should load and run the program, and wait for the program to terminate before available for the next command line; in contrast, the shell does not wait for the program to terminate before awaiting the next command line if the program runs in the background.

## Requirements

### 1. Prompt for User Input

Mini shell should display the prompt for user input. For example, if running mini shell in the Linux terminal,

    $./ shell

it should prompt

    sh >

indicating being ready for user input.

### 2. Foreground Execution of a Program

Mini shell should allow a program to run in the foreground, which has the following form:

    sh >fg [path of executable file] [a list of arguments]

For example, if want to run the test program mentioned in Section 4 in the foreground, type: 

    sh >fg ./test hello 2 5

where ./test is the path of the test program, and hello 2 5 are the arguments. When running a process in the foreground, the shell is unable to accept the next command from the user until the foreground process terminates. At any time, at most ONE process can run in the foreground.

### 3. Background Execution of Programs

The shell should also allow programs to run in the background:

    sh >bg [path of executable file] [a list of arguments]

Unlike the fg command, the shell is able to accept the next command immediately after executing the bg command. Below is an example:

    sh >bg ./test hello 2 5
    sh >

Also shell should allow **ANY** number of processes to exist in the background simultaneously.

### 4. Completion of Programs

When a foreground process or a background process completes and exits normally, shell should display a message. For example:

    sh >fg ./test hello 2 5
    hello
    hello
    hello
    hello
    hello
    Process 4096 completed 
    sh >

### 5. Ctrl-C and Ctrl-Z

When mini shell program is running in the Linux terminal, it will receive a SIGINT (SIGTSTP) signal if typing Ctrl-C (Ctrl-Z) on the keyboard. Shell program is expected to handle the signal and terminate (stop) the foreground process. If there is no foreground process running in the shell, then the signal should
have no effect.
For each process that is terminated (stopped) by Ctrl-C (Ctrl-Z), the shell should display the corresponding
message. For example, if a process with PID = 4096 is terminated by Ctrl-C, then the shell is expected to display the following message:

    sh >Process 4096 terminated

Similarly, if a process with PID = 4096 is stopped by Ctrl-Z, then the shell is expected to display the following information:

    sh >Process 4096 stopped

### 6. List All Processes

The **list** command should list the information of all processes that are running in the background as well as all the stopped processes. The information should include PID, state, path, and arguments. Terminated processes are **NOT** supposed to appear in the list. Therefore, need to reap the process if it completes and exits normally, or it is terminated by Ctrl-C. Otherwise, the **list** command may behave unexpectedly. Here is an example with correct behavior:

    sh >bg ./test test1 2 5
    sh >bg ./test test2 5 10
    sh >list
    4096: running ./test test1 2 5
    4097: running ./test test2 5 10
    sh >fg ./test test3 2 5
    Process 4098 terminated
    sh >fg ./test test4 5 10
    Process 4099 stopped
    sh >list
    4096: running ./test test1 2 5
    4097: running ./test test2 5 10
    4099: stopped ./test test4 5 10
    sh >

### 7. Exit the Shell

The **exit** command should cause the shell program to exit. But before that, make sure that all processes have been terminated and reaped. Here is an example where there are two processes in the background before executing exit:

    sh >exit
    Process 4096 terminated 
    Process 4097 terminated 
    $
    
### 8. Handling Unexpected Inputs

Need to handle unexpected inputs properly





## 2. How to run shell

User guides:

1. Compile and link the source program 55574846.cpp to produce an executable file 55574846 

        > g++ shell.cpp -lreadline -o shell

2. Run the executable file.

        > ./shell

Linux Shell
The shell continuously prompts for user command inputs.
Commands can't have more than 20 arguments
The shell can run commands in foreground and background
After "fg" command shell will run in foreground, and wait until the process finishes, or user can press Ctrl+C or Ctrl+Z to stop and terminate process.
After "bg" command shell will run in foreground, and will be able to run multiple processes at the same time.
In "bg", there is a list command that lists all not terminated processes that are running or stopped.
The shell prints, when some process finishes exetution.
Exit command terminates all the processes and quits the shell.

Possible outcomes are shown below.

1. fg command

        sh >fg [name of executable file] [a list of arguments] 

Action: shell runs the executable file with a list of arguments at the foreground, and therefore, no other commands are allowed (Except for ctrl+z and ctrl+c).

i) Simple run

    sh >fg ./test hello 3 4
    hello
    hello
    hello
    hello
    Process 73934 completed

ii) ctrl+c

    sh >fg ./test hello 3 4
    hello
    hello
    ^CProcess 74505 terminated

iii) ctrl+z

    sh >fg ./test hello 3 4
    hello
    hello
    ^ZProcess 74699 stopped

2. bg command

        sh >bg [name of executable file] [a list of arguments] 

Action: shell runs the executable file with a list of arguments at the background, therefor, user can add more processes anytime, and shell will keep prompting.

    sh >bg ./test hello 10 4
    sh >bg ./test world 10 3
    sh >hello
    world
    hello
    world
    hello
    world
    Process 76156 completed
    hello
    Process 75814 completed

3. list command

        sh >list

Action: shell outpust the list of mot terminated processes (stopped or running).

i) running process

    sh >bg ./test hello 10 5
    sh >list
    hello
    80025: running ./test hello 10 5

ii) running and stopped

    sh >fg ./test hello 5 10
    hello
    ^ZProcess 80941 stopped
    sh >bg ./test world 10 5
    sh >list
    80941: stopped ./test hello 5 10
    81299: running ./test world 10 5
    sh >world

4. exit command

        sh >exit 
    
Action: shell terminates all the processes and exits.

    sh >fg ./test hello 5 10
    hello
    ^ZProcess 80941 stopped
    sh >bg ./test world 10 5
    sh >list
    80941: stopped ./test hello 5 10
    81299: running ./test world 10 5
    sh >world
    world
    world
    world
    world
    Process 81299 completed
    list
    80941: stopped ./test hello 5 10
    sh >exit
    Process 80941 terminated

5. ctrl+c
Action: while foreground process is running, we can terminate it by ctrl+c command

        sh >fg ./test hello 2 5
        hello
        hello
        ^CProcess 83384 terminated

6. ctlr+z
Action: while foreground process is running, we can stop it by ctrl+z command

        sh >fg ./test hello 3 4
        hello
        hello
        ^ZProcess 74699 stopped

7. Reaping terminated processes
WUNTRACED is reaping terminated processes as it allows parent to be returned from waitpid() if child gets stopped as well as being exiting or being killed.
