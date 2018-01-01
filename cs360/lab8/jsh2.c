// jsh2.c
// Mitchell Wade
// April 10, 2015
// This program is the code for a C interpreter with
// file indirection.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "fields.h"

int main(int argc, char** argv) {

    int i, fin, fout, count, nwait;
    int id, pid, status, exists;
    char* prompt;
    char** newargv;
    IS is = new_inputstruct(NULL);

    // Use jsh2: for the prompt since nothing was entered
    if(argc < 2) {
        prompt = malloc(sizeof(char*)*5);
        strcat(prompt, "jsh2:");
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
    while(get_line(is) != EOF && (strcmp(is->fields[0], "exit") != 0)) {
        count = 0;
        nwait = 1;
        fin = -2;
        fout = -2;
        newargv = (char **) malloc(sizeof(char*)*(is->NF+1));

        // Read in the cmds
        for(i = 0; i < is->NF; i++) { 
            if(strcmp(is->fields[i], "<") == 0) {

                // Redirect input to specified file/cmd
                fin = open(is->fields[i+1], O_RDONLY);

                if(fin < 0) {
                    perror(is->fields[i+1]);
                    exit(1);
                }
                i++;
            }
            else if(strcmp(is->fields[i], ">") == 0) {

                // Redirect output to specified file/cmd
                fout = open(is->fields[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
                if(fout < 0) {
                    perror(is->fields[i+1]);
                    exit(1);
                }
                i++;
            }
            else if(strcmp(is->fields[i], ">>") == 0) {

                // Append to specified file/cmd
                fout = open(is->fields[i+1], O_WRONLY | O_APPEND | O_CREAT, 0644);
                if(fout < 0) {
                    perror(is->fields[i+1]);
                    exit(1);
                }
                i++;

            } else { 
                newargv[count] = is->fields[i];
                count++;
            }
        }
        newargv[count] = NULL;

        // Put into background
        if(strcmp(is->fields[is->NF-1], "&") == 0) { 
            newargv[count-1] = NULL;
            nwait = 0;
        }

        id = fork();
        if(id == 0) {

            // Redirect the input 
            if(fin != -2) {
                if(dup2(fin, 0) != 0) {
                    perror("dup2(fin, 0)");
                    exit(1);
                }
                close(fin);
            }

            // Redirect the output 
            if(fout != -2) {
                if(dup2(fout, 1) != 1) {
                    perror("dup2(fout, 1)");
                    exit(1);
                }
                close(fout);
            }

            // EXEC
            execvp(is->fields[0], newargv);
            perror(is->fields[0]);
            exit(1);
        }  
        else {

            // Wait for background process
            if(nwait) { 
                pid = wait(&status);
                while(1) {
                    if(pid == id) break;
                    pid = wait(&status);
                }
            }
            close(fin);
            close(fout);

        }
        fprintf(stdout, "%s", prompt);
        free(newargv);

    }

    jettison_inputstruct(is);
    return 0;
}
