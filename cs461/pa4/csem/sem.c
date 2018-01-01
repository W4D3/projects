// sem.c
// Mitchell Wade
// 11/18/15
// This program...

# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

extern char formaltypes[];
extern int formalnum;
extern char localtypes[];
extern int localnum;
int numLoops, numBranches, numblabels, numMlabels, t;

/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
   printf("B%d=L%d\n", p->s_place, k);
}   

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{
   int c;
   extern int lineno;
   static int laststmt = 0;

   // Print the current line number of each statement
   skip();
   c = getchar();
   putbak(c);
   if (c != '}' && lineno != laststmt) {
      printf("bgnstmt %d\n", lineno);
      laststmt = lineno;
   }
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
   int i = 0;
   struct id_entry *d;
   struct sem_rec *p, *e;

   // Search for the char *f in the lookup table
   if((d = lookup(f, 0)) == NULL) {
      d = install(f, 0);
      d->i_type = T_INT;
      d->i_scope = GLOBAL;
      d->i_defined = 1;
   }

   // Print the arguments
   for (p = args; p; p = p->back.s_link) {
      
      // Count the number of arguments
      i++;

      if (p->s_mode & T_INT) {
         printf("argsi t%d\n", p->s_place);
      } else if (p->s_mode & T_DOUBLE) {
         printf("argsf t%d\n", p->s_place);
      } else if (p->s_mode & T_STR) {
         printf("argsi t%d\n", p->s_place);
      }
   }

   // Print the scope of the current function
   if(d->i_scope & GLOBAL) {
      printf("t%d := global %s\n", nexttemp(), f);
   }

   e = node(currtemp(), GLOBAL, (struct sem_rec *) NULL, (struct sem_rec *) NULL);

   // Print intermediate code for the function call
   printf("t%d := fi t%d %d\n", nexttemp(), e->s_place, i);
}
   
/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccand not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccexpr not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccnot not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccor not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
   struct id_entry *p;

   // Search the symbol table
   if((p = lookup(x, 0)) == NULL) {
      p = install(x, 0);
      p->i_type = T_INT;
      p->i_scope = GLOBAL;
      p->i_defined = 1;
   }

   /* print the quad t%d = const */
   printf("t%d := %s\n", nexttemp(), x);

   /* construct a new node corresponding to this constant generation 
      into a temporary. This will allow this temporary to be referenced
      in an expression later*/
   return(node(currtemp(), p->i_type, (struct sem_rec *) NULL,
            (struct sem_rec *) NULL));
}

/*
 * dobreak - break statement
 */
void dobreak()
{
   fprintf(stderr, "sem: dobreak not implemented\n");
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
   fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
   fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
      int m3, struct sem_rec *n2, int m4)
{
   // Create labels to backpatch a for loop
   backpatch(e2->back.s_true, m3);
   backpatch(e2->s_false, m4);
   backpatch(n1, m1);
   backpatch(n2, m3);
   return;
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{
   fprintf(stderr, "sem: dogoto not implemented\n");
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
   // Create labels to backpatch an if statemnt
   backpatch(e->back.s_true, m1);
   backpatch(e->s_false, m2);
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
      int m2, int m3)
{
   fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{
   // Print intermediate code for a return statement
   if (e->s_mode & T_INT) {
      printf("reti t%d\n", currtemp());
   } else {
      printf("retf t%d\n", currtemp());
   }
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
      int m3)
{
   fprintf(stderr, "sem: dowhile not implemented\n");
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
   numLoops--;
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
   struct sem_rec *p;
 
   // Call merge which uses s_link's to create a expression list
   p = merge(l, e);
   
   return(p);
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
   int i = 0;

   // prints function name
   printf("func %s\n", p->i_name);

   // prints formal variables
   for (i = 0; i < formalnum; i++) {
      if(formaltypes[i] == 'i') {
         // 'i' - formal integer
         printf("formal 4\n");
      } else {
         //'f' - formal double
         printf("formal 8\n");
      }
   }

   // prints local variables
   for (i = 0; i < localnum; i++) {
      if(localtypes[i] == 'i') {
         // 'i' - formal integer
         printf("localloc 4\n");
      } else {
         //'f' - formal double
         printf("localloc 8\n");
      }
   }
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
   struct id_entry *p;

   // Search the symbol table for function name identifers
   if((p = lookup(id, 0)) == NULL) {
      p = install(id, 0);
   } else if(p->i_defined) { yyerror("procedure previous defined");
   } else if(p->i_type != t) { yyerror("function decleration does not match previous use");
   }

   // Set attributes of function in data structure
   p->i_type = t;
   p->i_scope = GLOBAL;
   p->i_defined = 1;
   enterblock();
   formalnum = 0;
   localnum = 0;
   return p;
}

/*
 * ftail - end of function body
 */
void ftail()
{
   printf("fend\n");
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
   struct id_entry *p;

   // Search the symbol table or create an variable reference
   if ((p = lookup(x, 0)) == NULL) {
      yyerror("undeclared identifier");
      p = install(x, -1);
      p->i_type = T_INT;
      p->i_scope = LOCAL;
      p->i_defined = 1;
   }

   // Print out the variables scope type
   if (p->i_scope == GLOBAL)
      printf("t%d := global %s\n", nexttemp(), x);
   else if (p->i_scope == LOCAL)
      printf("t%d := local %d\n", nexttemp(), p->i_offset);
   else if (p->i_scope == PARAM) {
      printf("t%d := param %d\n", nexttemp(), p->i_offset);
      if (p->i_type & T_ARRAY) {
         (void) nexttemp();
         printf("t%d := @i t%d\n", currtemp(), currtemp()-1);
      }
   }

   /* add the T_ADDR to know that it is still an address */
   return (node(currtemp(), p->i_type|T_ADDR, (struct sem_rec *) NULL,
            (struct sem_rec *) NULL));
}

/*
 * indx - subscript
 */
struct sem_rec *indx(struct sem_rec *x, struct sem_rec *i)
{
   /* generate a quad t%d = x [] i */
   printf("t%d := ", nexttemp());
   printf("t%d ", x->s_place);
   if(x->s_mode & T_INT)
      printf("[]i ");
   else
      printf("[]f ");
   printf("t%d\n", i->s_place);

   /* create a new node for the index operation. No links to backpatch */
   return (node(currtemp(), (x->s_mode & ~(T_ARRAY)), 
            (struct sem_rec *)NULL, (struct sem_rec *)NULL));
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{
   fprintf(stderr, "sem: labeldcl not implemented\n");
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
   struct sem_rec *label;

   label = node(++numMlabels, T_LBL, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
   printf("label L%d\n", label->s_place);
   
   return (label->s_place);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
   struct sem_rec *t;

   printf("br B%d\n", ++numBranches);
   t = node(numBranches, 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL);

   return (t);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{

   if(*op == '@') { 
      printf("t%d := @", nexttemp());
      if (y->s_mode & T_INT) { 
         printf("i");
      } else {
         printf("f");
      }
      printf(" t%d\n", y->s_place);

      // Generates a semantic record
      return(node(currtemp(), y->s_mode | T_ADDR, (struct sem_rec*) NULL, (struct sem_rec*) NULL));
   }

   return ((struct sem_rec *) NULL);
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: op2 not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: opb not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
   struct sem_rec *temp;

   // Check if x or y is a int -- convert:
   if ((x->s_mode & T_INT) && (y->s_mode & T_DOUBLE)) { 
      x->s_mode = (double)x->s_mode;
      printf("t%d := cvf t%d\n", nexttemp(), x->s_place);
      temp = node (currtemp(), t, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
      printf("t%d := t%d %sf t%d\n", currtemp(), temp->s_place, op, y->s_place);
      //convert(x, T_DOUBLE);
   } else if ((x->s_mode & T_DOUBLE) && (y->s_mode & T_INT)) { 
      y->s_mode = (double)y->s_mode;
      printf("t%d := cvf t%d\n", nexttemp(), y->s_place);
      temp = node (currtemp(), t, (struct sem_rec *) NULL, (struct sem_rec *) NULL);
      printf("t%d := t%d %sf t%d\n", nexttemp(), x->s_place, op, temp->s_place);
      //convert(y, T_DOUBLE);
   } else if ((x->s_mode & T_INT) && (y->s_mode & T_INT)) { 
      printf("t%d := t%d %si t%d\n", nexttemp(), x->s_place, op, y->s_place);
   } else if ((x->s_mode & T_DOUBLE) && (y->s_mode & T_DOUBLE)) { 
      printf("t%d := t%d %sf t%d\n", nexttemp(), x->s_place, op, y->s_place);
   }

   //if (strcmp(op, "==")) {
   // Check if x or y is a double -- if so:
   //printf("t%d := t%d %sf t%d\n", nexttemp(), x->s_place, op, y->s_place);
   //}

   // Get the type somehow -- record it as t
   struct sem_rec *t1 = node (currtemp(), t, (struct sem_rec *) NULL, 
         (struct sem_rec *) NULL);

   printf("bt t%d B%d\n", t1->s_place, ++numblabels);
   printf("br B%d\n", ++numblabels);

   return (node(0, 0,
            node((numblabels - 1), 0, (struct sem_rec *) NULL, (struct sem_rec *) NULL),
            node(numblabels,     0, (struct sem_rec *) NULL, (struct sem_rec *) NULL)
            ));
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
   /* assign the value of expression y to the lval x */
   struct sem_rec *p, *cast_y;
   cast_y = y;

   if(*op!='\0' || x==NULL || y==NULL){
      p = op1("@", x);
         
      if(p->s_mode & T_INT) {
            printf("t%d := t%d %si t%d\n", nexttemp(), p->s_place, op, y->s_place);
            cast_y = node(currtemp(), T_INT, (struct sem_rec*) NULL, (struct sem_rec*) NULL);
      } else {
            printf("t%d := t%d %sf t%d\n", nexttemp(), p->s_place, op, y->s_place);
            cast_y = node(currtemp(), T_INT, (struct sem_rec*) NULL, (struct sem_rec*) NULL);
      }
   }

   /* if for type consistency of x and y */
   if((x->s_mode & T_DOUBLE) && !(y->s_mode & T_DOUBLE)){

      /*cast y to a double*/
      printf("t%d = cvf t%d\n", nexttemp(), y->s_place);
      cast_y = node(currtemp(), T_DOUBLE, (struct sem_rec *) NULL,
            (struct sem_rec *) NULL);
   }
   else if((x->s_mode & T_INT) && !(y->s_mode & T_INT)){

      /*convert y to integer*/
      printf("t%d = cvi t%d\n", nexttemp(), y->s_place);
      cast_y = node(currtemp(), T_INT, (struct sem_rec *) NULL,
            (struct sem_rec *) NULL);
   }

   /*output quad for assignment*/
   if(x->s_mode & T_DOUBLE)
      printf("t%d := t%d =f t%d\n", nexttemp(), 
            x->s_place, cast_y->s_place);
   else
      printf("t%d := t%d =i t%d\n", nexttemp(), 
            x->s_place, cast_y->s_place);

   /*create a new node to allow just created temporary to be referenced later */
   return(node(currtemp(), (x->s_mode&~(T_ARRAY)),
            (struct sem_rec *)NULL, (struct sem_rec *)NULL));
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
   numLoops++;
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
   struct sem_rec *str;
   printf("t%d := %s\n",nexttemp(), s);
   str = node(currtemp(), T_STR, (struct sem_rec*) NULL, (struct sem_rec*) NULL);
   return (str);
}
