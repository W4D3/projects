#include <stdio.h>
#include <stdlib.h>

/* data_uncompress.c
   Mitchell Wade
   January 28th, 2015
   
   This program reads from stdin and converts the input
   into uncompressed data that is readable for the user.
 */

int main () {
    char c, prev;
    int n, i, j, length;
    int *ibuf;
    double *dbuf;
    char *cbuf;

    c = getchar();
    prev = 'n';

    while (c != EOF) {

        // Check if the input is an int
        if (c == 'i') {
            n = getchar();

            // Check for proper size
            if (n == EOF) {
                fprintf(stderr, "Input error: no size\n");
                exit(0);
            }

            // Allocate memory
            ibuf = malloc(sizeof(int)*(n+1));
            
            // Store the input
            fread(ibuf, sizeof(int), n+1, stdin);

            // Check the number of ints
            if (feof(stdin)) {
                fprintf(stderr, "Input error: not enough ints\n");
                exit(0);
            }

            // Prints spaces
            if (prev != 'n' && c != 'n') printf(" ");

            // Prints the integers
            for (i = 0; i <= n; i++) {

                printf("%d", ibuf[i]);
                if (i < n) printf(" ");
            }

            // Deallocates memory
            free(ibuf);
        }

        // Check if the input is a double
        else if (c == 'd') {
            n = getchar();

            // Check for proper size
            if (n == EOF) {
                fprintf(stderr, "Input error: no size\n");
                exit(0);
            }

            // Allocate memory
            dbuf = malloc(sizeof(double)*(n+1));

            // Store the input
            fread(dbuf, sizeof(double), n+1, stdin);

            // Check the number of doubles
            if (feof(stdin)) {
                fprintf(stderr, "Input error: not enough doubles\n");
                exit(0);
            }

            // Print spaces
            if (prev != 'n' && c != 'n') printf(" ");

            // Print whitespaces
            for (i = 0; i <= n; i++) {

                printf("%.10lg", dbuf[i]);
                if (i < n) printf(" ");
            }

            // Deallocate memory
            free(dbuf);
        }

        // Check if the input is a char
        else if (c == 's') {
            n = getchar();

            // Check for proper size
            if (n == EOF) {
                fprintf(stderr, "Input error: no size\n");
                exit(0);
            }

            // Check for proper size and print strings
            for (i = 0; i <= n; i++) {

                length = getchar();
                
                // Check for proper size
                if (length == EOF) {
                    fprintf(stderr, "Input error: no string size\n");
                    exit(0);
                }

                // Allocate memory
                cbuf = malloc(sizeof(char)*(length+1));

                // Store the input
                fread(cbuf, sizeof(char), length+1, stdin);

                // Check for proper number of chars
                if(feof(stdin)) {
                    fprintf(stderr, "Input error: not enough chars\n");
                    exit(0);
                }

                // Print spaces
                if (i == 0 && prev != 'n' && c != 'n') printf(" ");

                // Print the string
                for (j = 0; j < length+1; j++) {
                    printf("%c", cbuf[j]);
                }

                // Print whitespace
                if (i < n ) printf(" ");

                // Deallocate memory
                free(cbuf);
            }

        // Check if the input is a newline
        } else if (c == 'n') {

            // Print newline
            printf("\n");
        
        // Check for proper input types
        } else if (c != 'n' && c != 's' && c != 'i' && c!= 'd'){
            fprintf(stderr, "Input error: bad type\n");
            exit(0);
        }

        // Manages spaces
        prev = c;
        c = getchar();
    }

    exit(0);
}
