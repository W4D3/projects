// jsh1.c
// Mitchell Wade
// April 10, 2015
// This program is the code for a basic C interpreter.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fields.h"
#include <fcntl.h>

int main(int argc, char** argv) {

    int i, fdin, fdout, status, pid;
    int tmp; // Used to index the end of the cmd line
    int background = 0;
    char* prompt;
    IS is = new_inputstruct(NULL);

    // Use jsh1: for the prompt since nothing was entered
    if(argc < 2) {
        prompt = malloc(sizeof(char*)*5);
        strcat(prompt, "jsh1:");
    }
    
    // Default because "-" was specified
    if(strcmp(argv[1], "-") == 0) {
        prompt = "";
    
    // Use the specified prompt
    } else {
        prompt = malloc(sizeof(char*)*(strlen(argv[1])));
        prompt = strdup(argv[1]);
    }
    fprintf(stdout, "%s", prompt);

    // Read file
    // Exit if user enters "exit"
    while(get_line(is) != EOF && strcmp(is->fields[0], "exit")) {

        // Set each cmds initial process type to foreground processes
        background = 0;
        char* newargv[is->NF+1];

        // Read in the cmds
        for(i = 0; i < is->NF; i++) {
            if(strcmp(is->fields[i], ">>") == 0 || strcmp(is->fields[i], ">") == 0 || strcmp(is->fields[i], "<") == 0) {
                break;
            }
            newargv[i] = is->fields[i];
        }
        tmp = i;
        fdin = 0;
        fdout = 0;

        // If the last cmd on the line is &, the command will be run in the background
        if(strcmp(is->fields[is->NF-1], "&") == 0) {
            newargv[tmp-1] = NULL;
            background = 1;
        } else {
            newargv[tmp] = NULL;
        }

        pid = fork();
        if(pid == 0) {

            if(fdin) {

                // Connect stdin to fdin
                if (dup2(fdin, 0) != 0) {
                    perror("dup2(fdin, 0)");
                    exit(1);
                }
                close(fdin);
            }

            if(fdout) {
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

    jettison_inputstruct(is);
    return 0;
}
