// jsh3.c
// Mitchell Wade
// April 10, 2015
// This program is the code for a C interpreter with
// file indirection and pipes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "fields.h"
#include "jrb.h"

int main(int argc, char** argv) {

    int i, j, count, fin, fout, nwait;
    int id, pid, status, exists, pipeFD[2];
    char* prompt;
    char** newargv;
    IS is = new_inputstruct(NULL);
    JRB t, tmp;

    // Use jsh3: for the prompt since nothing was entered
    if(argc < 2) {
        prompt = malloc(sizeof(char*)*5);
        strcat(prompt, "jsh3:");
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

    while(get_line(is) != EOF && (strcmp(is->fields[0], "exit") != 0)) {
        count = 0;
        nwait = 1;
        fin = -2;
        fout = -2;
        t = make_jrb();
        newargv = (char **) malloc(sizeof(char*)*(is->NF+1));

        // Read in cmd line
        for(i = 0; i < is->NF; i++) { 
            if(strcmp(is->fields[i], "<") == 0){

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
            }
            else if(strcmp(is->fields[i], "|") == 0) {
                newargv[count] = NULL;
                count = 0;

                // Pipe
                if(pipe(pipeFD) < 0) {
                    perror("pipe(pipeFD)");
                    exit(1);
                }

                id = fork();
                jrb_insert_int(t, id, JNULL);

                if(id == 0) {		

                    // Redirect input to specified file/cmd
                    if(fin != -2) {
                        if(dup2(fin, 0) != 0) {
                            perror("dup2(fin, 0)");
                            exit(1);
                        }
                        close(fin);
                        fin = -2;
                    } 

                    // Redirect output to pipe
                    if(dup2(pipeFD[1], 1) != 1) {
                        perror("dup2(pipeFD[1])");
                        exit(1);
                    }

                    close(pipeFD[0]);
                    close(pipeFD[1]);

                    // EXEC
                    execvp(newargv[0], newargv);
                    perror(newargv[0]);
                    exit(1);

                } else {
                    if(fin != -2) close(fin);
                    fin = pipeFD[0]; 

                    close(pipeFD[1]);
                }
            } else { 
                newargv[count] = is->fields[i];
                count++;
            }
        }
        newargv[count] = NULL;

        // Wait if a process is in the background
        if(strcmp(is->fields[is->NF-1], "&") == 0) { 
            newargv[count-1] = NULL;
            nwait = 0;
        }

        id = fork();
        jrb_insert_int(t, id, JNULL);

        if(id == 0) {

            // Redirect input to specified file/cmd
            if(fin != -2) {
                if(dup2(fin, 0) != 0) {
                    perror("dup2(fin, 0)");
                    exit(1);
                }
                close(fin);
            }

            // Redirect output to specified file/cmd
            if(fout != -2) {
                if(dup2(fout, 1) != 1) {
                    perror("dup2(fout, 1)");
                    exit(1);
                }
                close(fout);
            }

            // EXEC
            execvp(newargv[0], newargv);
            perror(newargv[0]);
            exit(1);
        }  
        else {

            // Wait if a process is in the background
            if(nwait) { 
                pid = wait(&status);
                tmp = jrb_find_int(t, pid);
                if(tmp != NULL) jrb_delete_node(tmp);

                while(1) {
                    if(jrb_empty(t)) break;
                    pid = wait(&status);
                    tmp = jrb_find_int(t, pid);
                    if(tmp != NULL) jrb_delete_node(tmp);
                }
            }

            fprintf(stdout, "%s", prompt);

            close(fin);
            close(fout);
        }

        free(newargv);
        jrb_free_tree(t);
    }

    jettison_inputstruct(is);
    return 0;
}
