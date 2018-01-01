%{
#include "y.tab.h"
%}

%%

"+="      { return PEQ; }
"-="      { return MEQ; }
"*="      { return TEQ; }
"/="      { return DEQ; }
"%="      { return REQ; }
"<<="     { return LSEQ; }
">>="     { return RSEQ; }
"&="      { return AEQ; }
"^="      { return XOREQ; }
"|="      { return OREQ; }
"|"       { return BOR; }
"^"       { return BXOR; }
"&"       { return BAND; }
"<<"      { return LS; }
">>"      { return RS; }
"dump"    { return DUMP; }
"clear"   { return CLEAR; }
[a-z]     { yylval.var = (int) *yytext - 'a';
            return VAR;
          }
[ \t\n]     ;
[0-9]+    { sscanf(yytext, "%d", &yylval.num);
            return NUM; }
.         { return yytext[0]; }
