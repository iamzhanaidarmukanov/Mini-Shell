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
void foreground() {}
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
        else if (strcmp(cmd, "fg") == 0) {}

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