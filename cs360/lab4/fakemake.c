// fakemake.c
// Mitchell Wade
// Feb. 21, 2015
// This program simulates the processing of making a
// program. It reads in a file descriptor and processes
// the contents of that file or if the file is not given
// it will process the file "fmakefile".

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include <sys/stat.h>

int main(int argc, char **argv) {

    int i = 0, size = 0, max_st_mtime = 0, cTime = 0, eTime = 0;
    int numC = 0, numF = 0, numL = 0, sizeC = 0, sizeF = 0 , sizeL = 0;
    int lengthC = 0, lengthF = 0, lengthL = 0, lengthE = 0, count2 = 0;
    int lengthTotal = 0, e_error = 0, updated = 0;
    char *exe = NULL, *obj = NULL, *s1 = NULL, *s2 = NULL, *c = NULL, *s3 = NULL;
    char *s4 = NULL, *flag_string = NULL, *exe_string = NULL, *lib_string = NULL;
    struct stat buf;
    IS is;
    Dllist C, H, L, F, tmp;
    C = new_dllist();
    H = new_dllist();
    L = new_dllist();
    F = new_dllist();

    // Default file descriptor
    if (argc == 1) { 
        is = new_inputstruct("fmakefile");    
        // Specified file descriptor
    } else {
        is = new_inputstruct(argv[1]); 
    }

    // Bad file descriptor
    if (is == NULL) {
        fprintf(stderr, "Bad file descriptor...\n");
        exit(1);
    }


    while(get_line(is) >= 0) {

        // Skip blank lines
        if (is->NF == 0) continue;

        // ADD C FILES
        if (strcmp(is->fields[0], "C") == 0) {

            i = 1;
            while (i != is->NF) {

            dll_append(C, new_jval_s(strdup(is->fields[i])));

            i++;
            }

            // ADD H FILES
        } else if (strcmp(is->fields[0], "H") == 0) {

            i = 1;
            while (i != is->NF) {

            dll_append(H, new_jval_s(strdup(is->fields[i])));

            i++;
            }

            // ADD L FILES
        } else if (strcmp(is->fields[0], "L") == 0) {
            
            i = 1;
            while (i != is->NF) {

            dll_append(L, new_jval_s(strdup(is->fields[i])));

            i++;
            }

            // ADD EXECUTABLE NAME
        } else if (strcmp(is->fields[0], "E") == 0) {
            
            // Check to see if there is more than one E line
            if (e_error != 0) {
                fprintf(stderr, "fmakefile (%d) cannot have more than one E line\n", is->line);
                exit(1);
            }

            size = strlen(is->fields[1]);
            exe = malloc(sizeof(char)*size);
            exe = strdup(is->fields[1]);
            
            // Flag that there has been an E line
            e_error++;

            // ADD F FILES
        } else if (strcmp(is->fields[0], "F") == 0) {
            
            i = 1;
            while (i != is->NF) {

            dll_append(F, new_jval_s(strdup(is->fields[i])));

            i++;
            }

            // Check for unprocessed line errors
        } else {
            fprintf(stderr, "Unprocessed line\n");
            exit(1);
        }
    }

    // Count the size of all flags
    dll_traverse(tmp, F) {
        numF++;
        sizeF += strlen(tmp->val.s);
    }

    // Create the flag string
    flag_string = malloc(sizeof(char)*(numF+sizeF));
    dll_traverse(tmp, F) {
        flag_string = strcat(flag_string, tmp->val.s);
        count2++;
        if (count2 != numF) flag_string = strcat(flag_string, " ");
    }
    count2 = 0;

    // Count the size of all executables
    dll_traverse(tmp, C) {
        numC++;
        sizeC += strlen(tmp->val.s);
    }

    // Create the exe string
    exe_string = malloc(sizeof(char)*(numC+sizeC));
    dll_traverse(tmp, C) {
        size = strlen(tmp->val.s)-1;
        tmp->val.s[size] = 'o';
        exe_string = strcat(exe_string, tmp->val.s);
        count2++;
        if (count2 != numC) exe_string = strcat(exe_string, " ");
        tmp->val.s[size] = 'c';
    }
    count2 = 0;

    // Count the size of all libs
    dll_traverse(tmp, L) {
        numL++;
        sizeL += strlen(tmp->val.s);
    }

    // Create the lib string
    lib_string = malloc(sizeof(char)*(numL+sizeL));
    dll_traverse(tmp, L) {
        lib_string = strcat(lib_string, tmp->val.s);
        count2++;
        if (count2 != numL) lib_string = strcat(lib_string, " ");
    }
    count2 = 0;

    // Check to see if no executable was specified
    if (exe == NULL) {
        fprintf(stderr, "No executable specified\n");
        exit(1);
    }

    // Process the H FILES
    dll_traverse(tmp, H) {
        if (stat(tmp->val.s, &buf) == -1) {
            fprintf(stderr, "fmakefile: %s: No such file or directory\n", tmp->val.s);
            exit(1);
        }

        if (buf.st_mtime >= max_st_mtime) max_st_mtime = buf.st_mtime;
    }

    // Process the C FILES
    dll_traverse(tmp, C) {
        if (stat(tmp->val.s, &buf) == -1) {
            fprintf(stderr, "fmakefile: %s: No such file or directory\n", tmp->val.s);
            exit(1);
        }

        // Grab time of C FILE
        cTime = buf.st_mtime;

        // Create the object file
        size = strlen(tmp->val.s)-1;
        obj = strdup(tmp->val.s);
        c = strdup(tmp->val.s);         // Saves the executable name
        obj[size] = 'o';

        // Grab the object file
        i = stat(obj, &buf);

        // COMPILE THE .c FILES
        if ((buf.st_mtime < max_st_mtime) || (buf.st_mtime < cTime) || (i == -1)) { 
            // Create the compile statement
            s1 = malloc(sizeof(char)*(strlen(obj)+7+(sizeF+numF)));
            s2 = malloc(sizeof(char)*7);
            strcpy(s2, "gcc -c ");
            strcpy(s1, s2);
            s1 = strcat(s1, flag_string);
            if (numF != 0) s1 = strcat(s1, " ");
            s1 = strcat(s1,c);
            printf("%s\n", s1);
            i = system(s1);
            if (i != 0) {
                fprintf(stderr, "Command failed.  Exitting\n");
                exit(1);
            }

            // Increment the number of files remade
            updated++;
        }
    }

    // Check if the executable needs to be remade
    i = stat(exe, &buf);

    eTime = buf.st_mtime;
    
    // Add up the length of the executable statement
    lengthL = sizeL+numL;
    lengthF = sizeF+numF;
    lengthC = sizeC+numC;
    // Added 1 for a space
    lengthE = strlen(exe)+1;
    // Added 4 for " -o " and 7 for "gcc -o "
    lengthTotal = lengthL + lengthF + lengthC + lengthE + 4 + 7; 

    // RECOMPILE THE .o FILES
    if ((eTime < max_st_mtime) || (updated > 0) || (i == -1)) { 
        s3 = malloc(sizeof(char)*lengthTotal);
        s4 = malloc(sizeof(char)*7);
        strcpy(s4, "gcc -o ");
        strcpy (s3, s4);                //"gcc -o "
        if (numF > 0) {
            s3 = strcat(s3, exe);           // exec name
            s3 = strcat(s3, " ");
        }
        s3 = strcat(s3, flag_string);   // flags
        if (numF != 0) s3 = strcat(s3, " ");
        if (numF == 0) {
            s3 = strcat(s3, exe);           // exec name
            s3 = strcat(s3, " ");
        }
        s3 = strcat(s3, exe_string);    // o files
        if (numL != 0) s3 = strcat(s3, " ");
        if (numL != 0) s3 = strcat(s3, lib_string);    // libraries
        printf("%s\n", s3);
        i = system(s3);
        if (i != 0) {
            fprintf(stderr, "Command failed.  Fakemake exiting\n");
            exit(1);
        }
    } else {
        printf("%s up to date\n", exe);
        exit(1);
    }

    jettison_inputstruct(is);
    return 0;
}
