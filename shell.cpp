#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
using namespace std;

// Placeholder for user input
char *input = NULL;

// Placeholder for command
char *cmd = NULL;

// Array for arguments
char *args[20];

// Flag of Foreground process
// if it is 0, then foreground process is not running
// if it is 1, then foreground process is running
int runningForeground = 0;


//
// Structure of the process
// 
struct PROCESS
{
    int id;
    char status[20];
    char *argsOfProcess[20];
    PROCESS *next = NULL;
};

PROCESS *head = NULL; // Head is NULL for now

// Creating pid
pid_t pid = getpid();

// Create status of the process
int status;


// 
// Scenario Functions
// 

// Foreground Process
void foreground() {

    //  Create a child process
    pid = fork();

    // Child Process
    if (pid == 0) {

        //  Executing path program
        if (execvp(args[0], args) < 0) {
            printf("execvp is failed for process. \n");
            exit(EXIT_FAILURE);
        }

    }

    // Parent Process
    else if (pid > 0) {

        //  Creating new Process
        PROCESS *newProcess = (PROCESS *)malloc(sizeof(PROCESS));

        //  Filling its attributes
        newProcess -> id = pid;
        strcpy(newProcess->status, "running");
        int i = 0;
        while (args[i] != NULL) {
            newProcess -> argsOfProcess[i] = (char *)malloc(strlen(args[i]) + 1);
            if (newProcess->argsOfProcess[i] != NULL) {
                strcpy(newProcess->argsOfProcess[i], args[i]);
            }
            i++;
        }
        newProcess->argsOfProcess[i] = NULL; // Last index of the array should be terminating NULL
        newProcess->next = NULL;

        //  Including this process in the processes list
        //  Simple algorithm to put it last in the list
        if (head == NULL) {
            head = newProcess;
        } else {
            PROCESS *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newProcess;
        }

    }

    // Fork Failed
    else {
        printf("Fork Failed\n");
        exit(EXIT_FAILURE);
    }

    //  Since we run foreground process, runningForeground should become 1
    runningForeground = 1;
}





void background() {}
void list() {}
void exit() {}



// 
// Start of the main Function
// 
int main(int argc, char **argv) {


    //  Start of the Busy Loop
    //  Always prompting for user input
    while (true) {

        //  Prompting for user input
        input = readline("sh >");

        //  cmd gets the first argument
        // arguments are separated by space or tab
        cmd = strtok(input, " \t");

        //  Inserting other arguments into args array
        args[0] = strtok(NULL, " \t");
        char *temp;
        int i = 1;
        while (temp = strtok(NULL, " \t")) {
            args[i] = temp;
            i++;
        }
        args[i] = NULL;


        // 
        //  Start of the scenarios
        // 

        // Empty Command
        if (cmd == NULL) {
            continue; // If empty command, do nothing
        }

        // Foreground Process
        else if (strcmp(cmd, "fg") == 0) {
            foreground();
        }

        // Background Process
        else if (strcmp(cmd, "bg") == 0) {}

        // List Function
        // Listing all the processes that are not terminated
        else if (strcmp(cmd, "list") == 0) {}

        // Exit the Shell
        else if (strcmp(cmd, "exit") == 0) {}
        
        // Invalid Command
        else {
            printf("Unrecognized command.\n");
        }
    }
    return 0;
}