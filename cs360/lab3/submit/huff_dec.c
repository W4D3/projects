// huff_dec.c
// Mitchell Wade
// Feb. 11, 2015
// This program reads in two files from the cmd line and
// the first file represents the code defintion and the
// second file is the data that needs to be decoded. Using
// a jrb tree we are able to store the code definition and
// then reference it while decoding the data in the second
// file.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "jrb.h"

int main(int argc, char** argv){

    int i = 0, j = 0, c = 0, count = 0, currentBit = 0, size = 0;
    char *buf = malloc(sizeof(char));
    JRB t, tmp;
    FILE *f1, *f2;
    unsigned int *n = malloc(sizeof(unsigned int));
    t = make_jrb();

    // Open the code definition file
    f1 = fopen(argv[1], "r");
    if (f1 < 0) {
        perror(argv[1]);
        exit(1);
    }

    // Read in the value and key
    while(!feof(f1)){
        
        char* value = malloc(sizeof(char)*256);
        char* key = malloc(sizeof(char)*256);

        // VALUE
        fread(buf, sizeof(char), 1, f1);
        while(buf[0] != '\0') {
            if (i != 0) fread(buf, sizeof(char), 1, f1);
            c = buf[0];
            value[i] = c;
            i++;
        }
        i = 0;

        // KEY
        fread(buf, sizeof(char), 1, f1);
        while(buf[0] != '\0') {
            if (i != 0) fread(buf, sizeof(char), 1, f1);
            c = buf[0];
            key[i] = c;
            i++;
        } while(buf[0] != '\0');
        i = 0;


        // Creates the jrb tree
        if(!feof(f1)){
            jrb_insert_str(t, key, new_jval_s(value));
        }
    }
    fclose(f1);

    // Open the input file
    f2 = fopen(argv[2], "r");
    if (f2 < 0) {
        perror(argv[2]);
        exit(1);
    }

    // Grabs the last four bytes
    fseek(f2, -4, SEEK_END);
    fread(n, sizeof(unsigned int), 1, f2);

    // Determine the size of the input file
    fseek(f2, 0, SEEK_END);
    size = ftell(f2);

    // Go back to the beginning of the file
    fseek(f2, 0, SEEK_SET);

    // Determines if the file is the correct size
    if (size != (ceil(*n/8.0)+4)) {
        if(size < 4) {
            fprintf(stderr, "Error: file is not the correct size.\n");
        } else {
            fprintf(stderr, "Error: Total bits = %u, but file's size is %i\n",(*n), size);
        }
        exit(0);
    }

    buf = realloc(buf, sizeof(char)*(*n));
    char stream[(*n)];

    // DECODE
    fread(buf, 1, *n, f2);
    for(i = 0; i < (*n)/8.0; i++) {
        for(j = 0; j < 8; j++) {

           currentBit++;

            // Reverses the bytes
            if(buf[i] & 1){
                stream[count] = '1';
            } else{
                stream[count] = '0';
            }
            count++;
            buf[i] >>= 1;
            stream[count] = '\0';

            // Lookup the key in the tree and print value
            tmp = jrb_find_str(t, stream);
            if(tmp != NULL){
                printf("%s",tmp->val.s);
                stream[0] = '\0';
                count = 0;
            }

            // Prevents extra output
            if(currentBit >= *n){
                fclose(f2);
                return 0;
            }
        }
    }
    fclose(f2);
    return 0;
}
