/*
 * This file defines an example yacc grammar for simple C expressions.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
%}

%union {
  int num;
  int var;
  int id;
}

%token <num> ID
%token <num> NUM
%token <var> VAR
%token <num> LEFT_SHIFT
%token <num> RIGHT_SHIFT
%token <num> PE
%token <num> ME
%token <num> TE
%token <num> DE
%token <num> RE
%token <num> LSE
%token <num> RSE
%token <num> AE
%token <num> XE
%token <num> OE
%token <num> BITOR
%token <num> BITXOR
%token <num> BITAND

%type <num> expr
%type <num> shift
%type <num> ASMT
%type <num> bitor
%type <num> bitxor
%type <num> bitand
%type <num> addsub
%type <num> mdr
%type <num> neg
%type <num> bitnot
%type <num> parens
%type <num> expr

%{
  int sym[26];
  int overflow = 0;
  int divbz = 0;
%}


%%
commands:
	    |	commands command
	    ;

command	:	ASMT ';'              { 
									 if(overflow == 1){
										printf("overflow\n");
									    overflow = 0;
									 }
									 else if(divbz == 1){
										printf("dividebyzero\n");
									    divbz = 0;
									 }
									 else printf("%d\n", $1); 
								   
								   }
		                                                
		|   ID                     {if($1 == -1) dump();
		                             else if($1 == -2) clear();}
		;

ASMT    :   VAR '=' ASMT           { sym[$1] = $3; $$ = sym[$1];}
        |   VAR PE bitor           { ofas(sym[$1], $3, 0);
		                             sym[$1] += $3; $$ = sym[$1];}
		|   VAR ME bitor           { ofas(sym[$1], $3, 1);
		                             sym[$1] -= $3; $$ = sym[$1];}
		|   VAR TE bitor           { ofm(sym[$1],$3);
		                             sym[$1] *= $3; $$ = sym[$1];}
		|   VAR DE bitor           { if($3 != 0){
		                               sym[$1] /= $3; 
									   $$ = sym[$1];
									 } 
									 else{ 
									   $$ = sym[$1];
									   divbz = 1;
									 }
								   }
		|   VAR RE bitor           { sym[$1] %= $3; $$ = sym[$1];}
		|   VAR LSE bitor          { sym[$1] <<= $3; $$ = sym[$1];}
		|   VAR RSE bitor          { sym[$1] >>= $3; $$ = sym[$1];}
		|   VAR AE bitor           { sym[$1] &= $3; $$ = sym[$1];}
		|   VAR XE bitor           { sym[$1] ^= $3; $$ = sym[$1];}
		|   VAR OE bitor           { sym[$1] |= $3; $$ = sym[$1];}
		|   bitor                  { $$ = $1; }
		;

bitor   :   bitor BITOR bitxor     { $$ = $1 | $3; }
        |   bitxor                 { $$ = $1; }
		;

bitxor  :   bitxor BITXOR bitand   { $$ = $1 ^ $3; }
        |   bitand                 { $$ = $1; }
		;

bitand  :   bitand BITAND shift    { $$ = $1 & $3; }
        |   shift                  { $$ = $1; }
		;

shift   :   shift LEFT_SHIFT addsub  { $$ = $1 << $3; }
        |   shift RIGHT_SHIFT addsub { $$ = $1 >> $3; }
		|   addsub                   { $$ = $1; }
		;

addsub  :   addsub '+' mdr         { ofas($1, $3, 0); $$ = $1 + $3; }
        |   addsub '-' mdr         { ofas($1, $3, 1); $$ = $1 - $3; }
        |   mdr                    { $$ = $1; }
		;

mdr     :   mdr '*' neg            {  ofm($1,$3);
                                      $$ = $1 * $3; }
        |   mdr '/' neg            { if($3 != 0) $$ = $1 / $3; 
									 else{
									   $$ = $1;
									   divbz = 1;
									 }
								   }
		|   mdr '%' neg            { $$ = $1 % $3; }
		|   neg                    { $$ = $1; }
		;

neg     :   '-' neg                { $$ = $2 * -1; }
        |   bitnot                 { $$ = $1; }
		;

bitnot  :   '~' bitnot             { $$ = ~$2; }
        |   parens                 { $$ = $1; }
		;  
 
parens  :   '(' ASMT ')'           { $$ = $2; }
        |   expr                   { $$ = $1; }
		;

expr	:	NUM                    { $$ = $1; }
	    |   VAR                    { $$ = sym[$1]; }
		;

%%

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

dump(){
  int i;
  char ch;

  ch = 'a';
  for(i = 0; i < 26; i++){
	printf("%c: %d\n", ch, sym[i]);
	ch++;
  }
}

clear(){
  int i;
  for(i = 0; i < 26; i++) sym[i] = 0;
}

/* Function to check for overflow while multiplying */
ofm(int arg1, int arg2){
  int x;             // For use in testing overflow.

  x = arg1 * arg2;
  if(arg1 != 0 && (x/arg1) != arg2){
	overflow = 1;
  }
}

/* Function to detect overflow while adding */
/* as == 0 indicates adding, as == 1 indicates subtracting */
ofas(int arg1, int arg2, int as){
  int max = INT_MAX;  // To use for testing for overflow.
  int x1;             // Stores val of arg1 for testing.
  int x2;             // Stores val of arg2 for testing.
  
  // If subtracting, make second value negative.
  if(as == 1) x2 = arg2 * -1;
  else x2 = arg2;
  x1 = arg1;

  // If both values are negative, make them both positive.
  if(x1 < 0 && x2 < 0){
    x1 = abs(x1);
	x2 = abs(x2);
  } 

  // If both vals are positive while adding, check for overflow.
  if(x1 > 0 && x2 > 0){
    if(arg1 > arg2){
      if((max-arg2) < arg1){
	    overflow = 1;
	  }
    } else {
      if((max-arg1) < arg2){
  	    overflow = 1;
  	  }
    }
  }
}















