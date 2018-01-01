// jtar.c
// Mitchell Wade
// Mar. 10, 2015

#include "jtar.h"
#include "fields.h"
#include <utime.h>

void processFile(char* filename, JRB t){

    struct stat s;

    if (lstat(filename, &s) == -1) {
        fprintf(stderr, "%s\t", filename);
        fprintf(stderr, "lstat failed\n");
        exit(1);
    }

    // Add the current file to t
    if (jrb_find_str(t, filename) == NULL && !S_ISLNK(s.st_mode))
        jrb_insert_str(t, filename, JNULL);

    // Check if its a directory
    if (S_ISDIR(s.st_mode)){
        
        struct dirent* namelist;
        DIR* d = opendir(filename);
        Dllist temp = new_dllist();
        
        // Read the contents of the directory
        for (namelist = readdir(d); namelist != NULL; namelist = readdir(d)){
            
            if (strcmp(namelist->d_name, ".") && strcmp(namelist->d_name, "..")){
                
                // Get the path name
                char* newfilename = malloc(sizeof(char)*(strlen(filename)+256));
                strcpy(newfilename, filename);
                strcat(newfilename, "/");
                strcat(newfilename, namelist->d_name);

                //Add it to a Dllist
                dll_append(temp, new_jval_s(newfilename));
            }
        }

        closedir(d);
        Dllist running;
        
        // Process the files on the Dllist
        dll_traverse(running, temp){
            processFile(running->val.s, t);
        }

        free_dllist(running);
    }
}

void writeData(JRB t){

    JRB inodes = make_jrb();
    JRB running;
    jrb_traverse(running, t){

        // Write the filename to stdout
        fwrite(running->key.s, sizeof(char), strlen(running->key.s), stdout);
        fputc('\0', stdout);

        struct stat s;
        lstat(running->key.s, &s);

        // Write the stat struct to stdout
        fwrite(&s, sizeof(struct stat), 1, stdout);

        // If it's not a directory + if it's not already in the JRB tree
        // Then add it to the tree and put the contents in
        // Else its a hard link
        if (S_ISREG(s.st_mode) && jrb_find_int(inodes, s.st_ino) == NULL){
            
            FILE* file = fopen(strdup(running->key.s), "r");
            char* contents = malloc(s.st_size);
            
            fread(contents, s.st_size, 1, file);
            fwrite(contents, s.st_size, 1, stdout);
            fclose(file);
            jrb_insert_int(inodes, s.st_ino, JNULL);
        }
    }
}

void readData(){

    int x;
    JRB inodes = make_jrb();
    JRB dirs = make_jrb();
    JRB atimes = make_jrb();
    JRB mtimes = make_jrb();

    char c = fgetc(stdin);
    while(c != EOF){
        
        char* filename = malloc(sizeof(char) * MAXLEN);
        int i;
        
        // Creates the filename
        for(i = 0; c != '\0'; i++){
            filename[i] = c;
            c = fgetc(stdin);
        }

        // Null terminate the string
        filename[i] = c;
        struct stat s;

        // Read in the stat struct
        fread(&s, sizeof(struct stat), 1, stdin);

        // Create the utimbuf from the stat struct
        struct utimbuf ubuf;
        ubuf.actime = s.st_atime;
        ubuf.modtime = s.st_mtime;

        if (S_ISDIR(s.st_mode)){
            mkdir(filename, 0777);

            // Add the filenames info to the JRB trees
            jrb_insert_str(dirs, filename, new_jval_i(s.st_mode));
            jrb_insert_str(atimes, filename, new_jval_i(s.st_atime));
            jrb_insert_str(mtimes, filename, new_jval_i(s.st_mtime));
        }

        // If it's a regular file that's not a hard link
        else if (S_ISREG(s.st_mode) && jrb_find_int(inodes, s.st_ino) == NULL){
            
            // Put it in the inodes tree
            jrb_insert_int(inodes, s.st_ino, new_jval_s(filename));

            char* contents = malloc(s.st_size);
            fread(contents, s.st_size, 1, stdin);
            FILE* file = fopen(filename, "w");
            if (file == NULL) {
                printf("Failed to open: %s\n", filename);
                exit(1);
            }
            fwrite(contents, s.st_size, 1, file);
            fclose(file);
            
            // Change mode
            chmod(filename, s.st_mode);

            // Change times
            utime(filename, &ubuf);
        }

        // If it's a hard link
        else if (S_ISREG(s.st_mode)){
            JRB temp = jrb_find_int(inodes, s.st_ino);
            link(temp->val.s, filename);
            utime(filename, &ubuf);
        }
        c = fgetc(stdin);
    }
    JRB temp;

    // Update time and mode to final time/mode
    jrb_traverse(temp, dirs){
        chmod(temp->key.s, temp->val.i);
        struct utimbuf ubuf;
        ubuf.actime = jrb_find_str(atimes, temp->key.s)->val.i;
        ubuf.modtime = jrb_find_str(mtimes, temp->key.s)->val.i;
        utime(temp->key.s, &ubuf);
    }

    jrb_free_tree(inodes);
    jrb_free_tree(dirs);
    jrb_free_tree(atimes);
    jrb_free_tree(mtimes);
}

int main(int argc, char** argv){

    char cx = argv[1][0];
    int i;
    JRB t;

    if (argc < 2) {
        fprintf(stderr, "usage: jtar cx files...\n");
        exit(1);
    }

    if (strcmp(argv[1], "c") && strcmp(argv[1], "x")) {
        fprintf(stderr, "usage: jtar cx files...\n");
        exit(1);
    }

    // Check for extraction or creation
    if (cx == 'c') {

        if (argc < 3) {
            fprintf(stderr, "usage: jtar cx files...\n");
            exit(1);
        }

        // Allocate memory
        t = make_jrb();

        // Process command line arguments
        for(i = 2; i < argc; i++) processFile(argv[i], t);

        // Write the tar file to stdout
        writeData(t);

        // Deallocate memory
        jrb_free_tree(t);

    } else if (cx == 'x') {

        // Read the tar file from stdin
        readData();
    }

    return 0;
}
