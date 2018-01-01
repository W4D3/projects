#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "dllist.h"
#include "jval.h"

// famtree.c
// Mitchell Wade
// Feb. 7, 2015
// This program reads in a file from standard input that
// represents a list of people. The program will then
// create a family tree using a JRB tree for the family
// tree and a Dllist for keeping a list of children. It
// prints out the family tree, names, and genders.

typedef struct person {
    int visited, printed;
    char *name, *sex, *mother, *father;
    Dllist children;
} Person;

// Checks for cycles
int is_descendant(Person *p) {

    Dllist tmp;
    
    if(p->visited == 1) return 0;
    if(p->visited == 2) return 1;

    // Flags a cycle
    p->visited = 2;
    
    dll_traverse(tmp, p->children) {
        if (is_descendant((Person *) tmp->val.v)) return 1;
    }

    // Mark as visited
    p->visited = 1;
    
    return 0;
}

// Adds a child to a parents dllist
Dllist addChild(Person *parent, Person *child) {

    Person *p;
    Dllist tmp;
    
    dll_traverse(tmp, parent->children) {
        p = (Person *) tmp->val.v;

        // If the child is already on the list return
        if(!strcmp(p->name, child->name)) {
            return parent->children;
        }
    }

    // Add the child
    dll_append(parent->children, new_jval_v(child));
    
    return parent->children;
}

// FATHER
void setFather(Person *child, Person *father, IS is) {

    if(strcmp(child->father, "Unknown")) {
        fprintf(stderr, "Bad input -- child with two fathers on line %i\n", is->line);
        exit(0);
    }

    child->father = father->name;
}

// MOTHER
void setMother(Person *child, Person *mother, IS is) {
    
    if(strcmp(child->mother, "Unknown")) {
        fprintf(stderr, "Bad input -- child with two mothers on line %i\n", is->line);
        exit(0);
    }

    child->mother = mother->name;
}

// Deteremines the persons sex
void setSex(Person *p, char *sex, IS is) {

    // New person
    if(p->sex == NULL) {        
        p->sex = sex;
    
    // Unknown sex
    } else if(!strcmp(p->sex, "Unknown") && strcmp(sex, "Unknown")) {
        p->sex = sex;
    
    // Don't set the sex
    } else if(strcmp(p->sex, "Unknown") && !strcmp(sex, "Unknown")) {
        return;
    
    // Error
    } else if(strcmp(p->sex, sex)) {
        fprintf(stderr,"Bad input - sex mismatch on line %i\n", is->line);
        exit(0);
    }
}

// PERSON
void setPerson(JRB tree, Person** person, IS is) {
    
    Person *p;

    JRB t = jrb_find_str(tree, (*person)->name);

    // Insert the person if he/she is not already on the family tree
    if(!t) t = jrb_insert_str(tree, (*person)->name, new_jval_v(*person));

    p = (Person *) t->val.v;
    setSex(p, (*person)->sex, is);
    p->printed = 0;
    p->visited = 0;
    *person = p;
}


// PRINT PARENTS
int printParents(Person *p, JRB tree) {

    Person *father, *mother;

    // Prints father
    if(strcmp(p->father, "Unknown") != 0) {
        father = (Person *) jrb_val(jrb_find_str(tree, p->father)).v;

        if(father->printed == 0) return 0;
    }

    // Prints mother
    if(strcmp(p->mother, "Unknown") != 0) {
        mother = (Person*) jrb_val(jrb_find_str(tree, p->mother)).v;
        
        if(mother->printed == 0) return 0;
    }

    return 1;
}

// PRINT PERSON
void printPerson(Person** p) {

    Dllist temp_dll;
    
    printf("%s\n", (*p)->name);
    printf("Sex: %s\n", (*p)->sex);
    printf("Father: %s\n", (*p)->father);
    printf("Mother: %s\n", (*p)->mother);
    printf("Children: ");

    // If there are no children
    if(dll_empty((*p)->children)) {
        printf("None");
    } else {
        dll_traverse(temp_dll,(*p)->children) {
            printf("\n");
            printf("%s", ((Person*)temp_dll->val.v)->name);
        }
    }
    printf("\n\n");

    (*p)->printed = 1;
}

// Creates the persons name
char* createName(IS is) {
    
    int i;
    char* name = "";
    
    name = malloc(sizeof(char[MAXLEN]));
    
    for(i = 1; i < is->NF; i++) {
        name = strcat(name, is->fields[i]);
        name = strcat(name, " ");
    }

    return name;
}

// Creates a person struct
Person* createPerson(IS is, char* sex) {

    Person *p = (Person*) malloc(sizeof(Person));
    p->name = createName(is);
    setSex(p, sex, is);
    p->father = "Unknown";
    p->mother = "Unknown";
    p->visited = 0;
    
    if(p->children == NULL) {
        p->children = new_dllist();
    }

    return p;
}

int main(int argc, char* argv[]) {

    int i;
    Person *p, *tmp;
    IS is = new_inputstruct(NULL);
    JRB tree = make_jrb();
    JRB t;
    Dllist temp_dll, print;

    while(get_line(is) >= 0) {

        // PERSON
        if(!strcmp(is->fields[0], "PERSON")) {
            p = createPerson(is, "Unknown");
            setPerson(tree, &p, is);
        
        // SEX
        } else if(!strcmp(is->fields[0], "SEX")) {
            if(!strcmp(is->fields[1], "M")) {
                setSex(p, "Male", is);
            } else if(!strcmp(is->fields[1], "F")) {
                setSex(p, "Female", is);
            }
        
        // FATHER_OF
        } else if(!strcmp(is->fields[0], "FATHER_OF")) {
            setSex(p, "Male", is);
            tmp = createPerson(is, "Unknown");
            setPerson(tree, &tmp, is);
            setFather(tmp, p, is);
            p->children = addChild(p, tmp);
        
        // MOTHER_OF
        } else if(!strcmp(is->fields[0], "MOTHER_OF")) {
            setSex(p,"Female", is);
            tmp = createPerson(is, "Unknown");
            setPerson(tree, &tmp, is);
            setMother(tmp, p, is);
            p->children = addChild(p, tmp);
        
        // FATHER
        } else if(!strcmp(is->fields[0], "FATHER")) {
            tmp = createPerson(is, "Male");
            setPerson(tree, &tmp, is);
            setFather(p, tmp, is);
            tmp->children = addChild(tmp, p);
        
        // MOTHER
        } else if(!strcmp(is->fields[0], "MOTHER")) {
            tmp = createPerson(is, "Female");
            setPerson(tree, &tmp, is);
            setMother(p, tmp, is);
            tmp->children = addChild(tmp, p);
        }

        // Clear the input field
        is->fields[0] = "";
    }
    jettison_inputstruct(is);
    
    print = new_dllist();
    
    // Creates a Queue
    jrb_traverse(t, tree) {
        
        p = (Person *) jrb_val(t).v;

        if(is_descendant(p)) {
            fprintf(stderr, "Bad input -- cycle in specification\n");
            exit(0);
        }

        p->printed = 0;
        p->visited = 0;
        dll_append(print, new_jval_v(p));
    }


    // PRINT
    while(!dll_empty(print)) {
        
        // Grab the top
        p = (Person*) dll_val(dll_first(print)).v;

        // Pop off the top
        dll_delete_node(dll_first(print));
        
        // Check if printed
        if(p->printed == 0) {
            if(printParents(p, tree)) {
                
                // Print the person
                printPerson(&p);

                dll_traverse(temp_dll,p->children) {
                    tmp = (Person *) temp_dll->val.v;
                    dll_append(print, new_jval_v(tmp));
                }
            }
        }
    }
}
