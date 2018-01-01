#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "dllist.h"
#include "jval.h"

// famtree.c
// Mitchell Wade
// Feb. 4, 2015
// This program reads in a file from standard input that
// represents a list of people. The program will then
// create a family tree using a JRB tree for the family
// tree and a Dllist for keeping a list of children. It
// prints out the family tree, names, and genders.

typedef struct person 
{
    int visited, printed;
    char *name, sex;
    struct person *father, *mother;
    Dllist children;
    // depth and breadth first search traversal variables
} Person;

// Creates a new person struct and returns a pointer to it
Person* createPerson(char* n, IS is, JRB t) {

    Person *p;

    p = malloc(sizeof(Person));
    p->name = strdup(n);
    p->father = malloc(sizeof(Person));
    p->mother = malloc(sizeof(Person));
    p->sex = 'u';
    p->father->name = "Unknown";
    p->mother->name = "Unknown";
    p->children = new_dllist();
    p->visited = 0;
    p->printed = 0;

    return p;
}

void addChild(Person *child, Person *p) {

    int flag = 0;
    Dllist tmp;
    Person *p2;

    // Check if the child is already on the list
    dll_traverse(tmp, p->children) {
        p2 = (Person *) tmp->val.v;
        if (strcmp(p2->name, child->name) == 0) {    
            flag++;
        }
    }

    if (flag == 0) {
        dll_append(p->children, new_jval_v((void *) child));
    }
}

int is_descendant(Person *p)
{
    Person *child;
    Dllist tmp;
    
    //printf("%s\n", p->name);

    if (p->visited == 1) return 0;
    if (p->visited == 2) return 1;

    p->visited = 2;
    
    dll_traverse(tmp, p->children) {
        child = (Person *) tmp->val.v;
        if (is_descendant(child)) return 1;
    }

    p->visited = 1;

    return 0;
}

char* createName(char* n, IS is) {

    int i = 0, nsize = 0;

    // Grab the length of the persons name
    nsize = strlen(is->fields[1])+1;

    // Concatinate all names together and add one for a space between words
    for (i = 2; i < is->NF; i++) {
        //if (i != is->NF) {
            nsize += strlen(is->fields[i])+1;
        //} else nsize += strlen(is->fields[i]);
    }

    // Allocate space for the persons name
    n = (char *) malloc(sizeof(char)*nsize);
    strcpy(n, is->fields[1]);
    // Store the persons name
    for (i = 2; i < is->NF; i++) {
        strcat(n, " ");
        strcat(n, is->fields[i]);
    }


    return n;
}

int main(int argc, char **argv) {

    char *n;
    IS is;
    int i = 0, nsize = 0;
    JRB t, tmp;
    Dllist l, tmp2, print, top;
    Person *p, *father, *mother, *child;
    is = new_inputstruct(NULL);
    t = make_jrb();
    print = new_dllist();

    while(get_line(is) >= 0) {

        // Skips blank lines
        if (is->NF == 0 ) continue;

        // PERSON
        if (strcmp(is->fields[0], "PERSON") == 0) {
            n = createName(n, is);
            tmp = jrb_find_str(t, n);

            if (tmp != NULL) {
                p = (Person *) tmp->val.v;
            } else {
                p = createPerson(n, is, t);
                jrb_insert_str(t, p->name, new_jval_v((void *) p));
            }

            // SEX
        } else if (strcmp(is->fields[0], "SEX") == 0) {

            if(strcmp(is->fields[1], "M") == 0) p->sex = 'M';
            else { p->sex = 'F'; }

            // FATHER_OF
        } else if (strcmp(is->fields[0], "FATHER_OF") == 0) {

            if (p->sex == 'u') {
                p->sex = 'M';
            }

            n = createName(n, is);
            
            // Cannot be own parent
            if (strcmp(n, p->name) == 0) {
                fprintf(stderr, "%s can't be their own parent!\n", p->name);
                exit(0);
            }

            tmp = jrb_find_str(t, n);

            if (tmp != NULL) {
                child = malloc(sizeof(Person));
                child = (Person *) tmp->val.v;
                /*
                //printf("%s\n", p->name);
                //printf("  FATHER OFSex: %c\n", p->sex);
                // Check for improper sex
                if (child->sex == 'F') {
                    fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
                    exit(0);
                }
                */

                // Checks for two fathers
                if ((strcmp(child->father->name, "Unknown") != 0) && (strcmp(n, child->father->name) != 0 )) { 
                    fprintf(stderr, "Bad input - child with two mothers on line %d\n", is->line);
                    exit(0);
                }

                addChild(child, p);
                child->father = p;
            } else {
                child = malloc(sizeof(Person));
                child = createPerson(n, is, t);
                jrb_insert_str(t, child->name, new_jval_v((void *) child));
                addChild(child, p);
                child->father = p;
            }

            // MOTHER_OF
        } else if (strcmp(is->fields[0], "MOTHER_OF") == 0) {

            if (p->sex == 'u') {
                p->sex = 'F';
            }

            n = createName(n, is);

            // Cannot be own parent
            if (strcmp(n, p->name) == 0) {
                fprintf(stderr, "%s can't be their own parent!\n", p->name);
                exit(0);
            }

            tmp = jrb_find_str(t, n);

            if (tmp != NULL) {
                child = malloc(sizeof(Person));
                child = (Person *) tmp->val.v;
                
                /*
                //printf("%s\n", child->name);
                //printf("  MOTHER OFSex: %c\n", child->sex);
                if (child->sex == 'M') {
                    fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
                    exit(0);
                }
                */


                // Checks for two mothers
                if ((strcmp(child->mother->name, "Unknown") != 0) && (strcmp(n, child->mother->name) != 0 )) { 
                    fprintf(stderr, "Bad input - child with two mothers on line %d\n", is->line);
                    exit(0);
                }

                addChild(child, p);
                child->mother = p;
            } else {
                child = malloc(sizeof(Person));
                child = createPerson(n, is, t);
                jrb_insert_str(t, child->name, new_jval_v((void *) child));
                addChild(child, p);
                child->mother = p;
            }

            // MOTHER
        } else if (strcmp(is->fields[0], "MOTHER") == 0) {

            n = createName(n, is);

            // Checks for two mothers
            if ((strcmp(p->mother->name, "Unknown") != 0) && (strcmp(n, p->mother->name) != 0 )) { 
                fprintf(stderr, "Bad input - child with two mothers on line %d\n", is->line);
                exit(0);
            }

            // Cannot be own parent
            if (strcmp(n, p->name) == 0) {
                fprintf(stderr, "%s can't be their own parent!\n", p->name);
                exit(0);
            }

            tmp = jrb_find_str(t, n);

            if (tmp != NULL) {
                mother = (Person *) tmp->val.v;

                //printf("%s\n", p->name);
                //printf("  MOTHERSex: %c\n", p->sex);
                // Check for improper sex
                if (mother->sex == 'M') {
                    fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
                    exit(0);
                }

                addChild(child, p);
                p->mother = mother;
            } else {
                mother = createPerson(n, is, t);
                jrb_insert_str(t, mother->name, new_jval_v((void *) mother));
                addChild(child, p);
                p->mother = mother;
            }

            // FATHER
        } else if (strcmp(is->fields[0], "FATHER") == 0) {

            n = createName(n, is);

            // Checks for two fathers
            if ((strcmp(p->father->name, "Unknown") != 0) && (strcmp(n, p->father->name) != 0 )) { 
                fprintf(stderr, "Bad input - child with two fathers on line %d\n", is->line);
                exit(0);
            }

            // Cannot be own parent
            if (strcmp(n, p->name) == 0) {
                fprintf(stderr, "%s can't be their own parent!\n", p->name);
                exit(0);
            }

            tmp = jrb_find_str(t, n);

            if (tmp != NULL) {
                father = (Person *) tmp->val.v;
                
                //printf("%s\n", p->name);
                //printf("  FATHERSex: %c\n", p->sex);
                // Check for improper sex
                if (father->sex == 'F') {
                    fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
                    exit(0);
                }
                addChild(child, p);
                p->father = father;
            } else {
                father = createPerson(n, is, t);
                jrb_insert_str(t, father->name, new_jval_v((void *) father));
                addChild(child, p);
                p->father = father;
            }
        }
    }  

    // Check if visited
    jrb_traverse(tmp, t) {
        p = (Person *) tmp->val.v;

        if (is_descendant(p)) {
            fprintf(stderr, "Bad input -- cycle in specification\n");
        }

        if (is_descendant(p) == 0) {
            dll_traverse(tmp2, p->children) {
                child = (Person *) tmp2->val.v;
                is_descendant(child);
            }
        }
        dll_append(print, new_jval_v((void *) p));
    }

    // Print out the family tree
    while (!dll_empty(print)) {
        top = dll_first(print);

        p = (Person *) top->val.v;

        dll_delete_node(top);

        //if not printed and both parents printed or doesn't exist
        // Print out each person
        if ((p->printed == 0 && p->father->printed == 1 && p->mother->printed == 1) ||
                (p->printed == 0 && p->father->name == "Unknown" && p->mother->printed == 1) ||
                (p->printed == 0 && p->father->printed == 1 && p->mother->name == "Unknown") ||
                (p->father->name == "Unknown" && p->mother->name == "Unknown")) {

            printf("%s\n", p->name);
            if (p->sex == 'u') {
                printf("  Sex: Unknown\n");
            } else if (p->sex == 'M') {
                printf("  Sex: Male\n");
            } else if (p->sex == 'F') {
                printf("  Sex: Female\n");
            }
            printf("  Father: %s\n", p->father->name);
            printf("  Mother: %s\n", p->mother->name);
            if (dll_empty(p->children)) { 
                printf("  Children: None\n");
            } else {
                printf("  Children:\n");
                dll_traverse(tmp2, p->children) {
                    child = (Person *) tmp2->val.v;
                    printf("    %s\n", child->name);
                }
            }
            printf("\n");
            //set printed 
            p->printed = 1;
        } else dll_append(print, new_jval_v((void *) p));
    }

    // Deallocate memory and exit program
    jettison_inputstruct(is);
    exit(0);
}
