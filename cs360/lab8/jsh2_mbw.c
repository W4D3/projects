// jsh2.c
// Mitchell Wade
// April 9, 2015
// This program is the code for a basic C interpreter.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fields.h"
#include <fcntl.h>

int main(int argc, char** argv){

    char* prompt;
    IS is = new_inputstruct(NULL);

    // Use "jsh1:" for the prompt if nothing was specified
    if(argc < 2) {
        prompt = malloc(sizeof(char*)*5);
        strcat(prompt, "jsh1:");
    }
    
    // Default because "-" was specified
    if(strcmp(argv[1], "-") == 0) {
        prompt = "";
    
    // Use the specified prompt
    } else {
        prompt = malloc(sizeof(char*)*strlen(argv[1]));
        prompt = strdup(argv[1]);
    }
    fprintf(stdout, "%s", prompt);

    // Read file
    // Exit if user enters "exit"
    while(get_line(is) != EOF && strcmp(is->fields[0], "exit")) {

        int i, tmp, fdin, fdout, status, pid;
        int NF = is->NF;
        int background = 0; 
        char* newargv[NF+1];

        // Read in the cmds for the interpreter
        for(i = 0; i < NF; i++) {
            newargv[i] = is->fields[i];
        }
        tmp = i;
        fdin = 0;
        fdout = 0;

        if(i < NF) {
            // If the next cmd is a <, open the next field as read-only
            if(strcmp(is->fields[i], "<") == 0) {
                fdin = open(is->fields[i+1], O_RDONLY);
            }
        }

        if(i < NF) {
            // If the next cmd is a >, open the next field as write-only with truncate
            if(strcmp(is->fields[i], ">") == 0) {
                fdout = open(is->fields[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
            }
            // If the next cmd is a >>, open the next field as write-only with append
            
            if(strcmp(is->fields[i], ">>") == 0) {
                fdout = open(is->fields[i+1], O_WRONLY | O_APPEND | O_CREAT, 0666);
            }
        }

        // If the last cmd on the line is &, the command will be run in the background
        if(strcmp(is->fields[NF-1], "&") == 0) {
            newargv[tmp-1] = NULL;
            background = 1;
        } else {
            newargv[tmp] = NULL;
        }

        pid = fork();
        if(pid == 0) {

            // Child Process
            if(fdin){

                // Connect stdin to fdin
                if (dup2(fdin, 0) != 0) {
                    perror("dup2(fdin, 0)");
                    exit(1);
                }
                close(fdin);
            }

            if(fdout){
                // Connect stdout to fdout
                if (dup2(fdout, 1) != 1) {
                    perror("dup2(fdout, 1)");
                    exit(1);
                }
                close(fdout);
            }

            // EXEC
            execvp(newargv[0], newargv);
            perror(newargv[0]);
            exit(1);
        } else {
            
            // Parent Process
            if(fdin) close(fdin);
            if(fdout) close(fdout);
            
            // If background = 1 then the process should not be waited
            // on, but if background = 0 then halt progress until the
            // cmd finishes
            if(!background) {
                while(pid != wait(&status));
            }
        }

        fprintf(stdout, "%s", prompt);
    }

    return 0;
}
