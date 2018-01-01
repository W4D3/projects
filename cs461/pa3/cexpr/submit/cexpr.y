/* ex.y
   Mitchell Wade
   Oct. 9, 2015

   This program uses lex and yacc to create a grammar for a basic
   C expression calculator.
*/


/* Definitions */
%{
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
%}

%union {
  int num;
  int var;
}

%{
    int sigma[26];
    int overflow = 0;
    int div_by_zero = 0;
%}

%token <num> DUMP
%token <num> CLEAR
%token <num> NUM
%token <var> VAR
%token <num> PEQ
%token <num> MEQ
%token <num> TEQ
%token <num> DEQ
%token <num> REQ
%token <num> LSEQ
%token <num> RSEQ
%token <num> AEQ
%token <num> XOREQ
%token <num> OREQ
%token <num> BOR
%token <num> BXOR
%token <num> BAND
%token <num> LS
%token <num> RS

%type <num> expr
%type <num> assignment
%type <num> bitwise_or
%type <num> bitwise_xor
%type <num> bitwise_and
%type <num> shift
%type <num> add_sub
%type <num> mul_div_rem
%type <num> neg
%type <num> bitwise_not
%type <num> parenthesis

/* Grammar */
%%

commands:
	|	commands command
	;

command: assignment ';' {   if(overflow == 1) {
                                printf("overflow\n");
                                overflow = 0;
                            } else if(div_by_zero == 1) {
                                        printf("dividebyzero\n");
                                        div_by_zero = 0;
                            } else printf("%d\n", $1); 
                        }
    |   DUMP ';'           { dump(); }
    |   CLEAR ';'           { clear(); }
    ;

assignment: VAR '=' assignment   { sigma[$1] = $3; $$ = sigma[$1]; } 
    |   VAR PEQ bitwise_or       { overflow1(sigma[$1], $3, 0);
                                   sigma[$1] += $3; $$ = sigma[$1]; 
                                 }
    |   VAR MEQ bitwise_or       { overflow1(sigma[$1], $3, 1);
                                   sigma[$1] -= $3; $$ = sigma[$1]; 
                                 }
    |   VAR TEQ bitwise_or       { overflow2(sigma[$1], $3);
                                   sigma[$1] *= $3; $$ = sigma[$1]; 
                                 }
    |   VAR DEQ bitwise_or       { if($3 != 0) {
                                      sigma[$1] /= $3; 
                                      $$ = sigma[$1]; 
                                   } else {
                                        sigma[$1] /= $3;
                                        $$ = sigma[$1];
                                   }
                                 }      
    |   VAR REQ bitwise_or       { sigma[$1] %= $3; $$ = sigma[$1]; }
    |   VAR LSEQ bitwise_or      { sigma[$1] <<= $3; $$ = sigma[$1]; }
    |   VAR RSEQ bitwise_or      { sigma[$1] >>= $3; $$ = sigma[$1]; }
    |   VAR AEQ bitwise_or       { sigma[$1] &= $3; $$ = sigma[$1]; }
    |   VAR XOREQ bitwise_or     { sigma[$1] ^= $3; $$ = sigma[$1]; }
    |   VAR OREQ bitwise_or      { sigma[$1] |= $3; $$ = sigma[$1]; }
    |   bitwise_or                { $$ = $1; }
    ;

bitwise_or: bitwise_or BOR bitwise_xor   { $$ = $1 | $3; }
    |   bitwise_xor                      { $$ = $1; }
    ;

bitwise_xor: bitwise_xor BXOR bitwise_and { $$ = $1 ^ $3; }
    |   bitwise_and                       { $$ = $1; }
    ;

bitwise_and: bitwise_and BAND shift { $$ = $1 & $3; }
    |   shift                       { $$ = $1; }
    ;

shift: shift LS add_sub  { $$ = $1 << $3; }
    |   shift RS add_sub { $$ = $1 >> $3; }
    |   add_sub          { $$ = $1; }
    ;

add_sub: add_sub '+' mul_div_rem    { overflow1($1, $3, 0); $$ = $1 + $3; }
    |   add_sub '-' mul_div_rem     { overflow1($1, $3, 1); $$ = $1 - $3; }
    |   mul_div_rem                 { $$ = $1; }
    ;

mul_div_rem: mul_div_rem '*' neg    { overflow2($1, $3); $$ = $1 * $3; }
    |   mul_div_rem '/' neg         { if($3 != 0) $$ = $1 / $3; 
                                        else {
                                            $$ = $1;
                                            div_by_zero = 1;
                                        }
                                    }
    |   mul_div_rem '%' neg         { $$ = $1 % $3; }
    |   neg                         { $$ = $1; }
    ;

neg: '-' neg            { $$ = $2 * -1; }
    |   bitwise_not     { $$ = $1; }
    ;

bitwise_not: '~' bitwise_not        { $$ = ~$2; }
    | parenthesis                   { $$ = $1; }
    ;

parenthesis: '(' assignment ')'     { $$ = $2; }
    |   expr                        { $$ = $1; }
    ;

expr:   VAR         { $$ = sigma[$1];}
    |	NUM         { $$ = $1; }
    ;

%%

/* Subroutines */
main()
{
   if (yyparse())
      printf("\nInvalid expression.\n");
   else
      printf("\nCalculator off.\n");
}

yyerror(s)
char *s;
{
   fprintf(stderr, "%s\n", s);
}

// Prints out the current state of the 26 integer variables
dump() {
    int i;
    for (i = 0; i < 26; i++) printf("%c: %d\n", i + 'a', sigma[i]);
}

// Clears the current state of the 26 integer variables
clear() {
    int i;
    for (i = 0; i < 26; i++) sigma[i] = 0;
}

// Checks for multiplication overflow
overflow2(int a, int b) {
    int check = a * b;

    if(a != 0 && (check/a) != b) overflow = 1;
}

// Checks for subtraction and addition overflow
// Transform an equation with subtraction to an equation 
// with addition to simplify checking for overflow
overflow1(int a, int b, int flag) {
    int max = INT_MAX;
    int x1;
    int x2;

    // Transforms one negative value to positive
    if(flag == 1) x2 = b * -1;
    else {
        x2 = b;
        x1 = a;
    }

    // Transforms both negative values to positive
    if(x1 < 0 && x2 < 0) {
        x1 = abs(x1);
        x2 = abs(x2);
    }

    // Checks two positive values for overflow
    if(x1 > 0 && x2 > 0) {
        if(a > b) {
            if((max - b) < a) overflow = 1;
        } else if((max - a) < b) overflow = 0;
    }
}
