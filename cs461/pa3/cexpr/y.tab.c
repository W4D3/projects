#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 12 "cexpr.y"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#line 17 "cexpr.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int num;
  int var;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 23 "cexpr.y"
    int sigma[26];
    int overflow = 0;
    int div_by_zero = 0;
#line 39 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define DUMP 257
#define CLEAR 258
#define NUM 259
#define VAR 260
#define PEQ 261
#define MEQ 262
#define TEQ 263
#define DEQ 264
#define REQ 265
#define LSEQ 266
#define RSEQ 267
#define AEQ 268
#define XOREQ 269
#define OREQ 270
#define BOR 271
#define BXOR 272
#define BAND 273
#define LS 274
#define RS 275
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   12,   12,   12,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    3,    3,    4,
    4,    5,    5,    6,    6,    6,    7,    7,    7,    8,
    8,    8,    8,    9,    9,   10,   10,   11,   11,    1,
    1,
};
static const short yylen[] = {                            2,
    0,    2,    2,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    3,    1,    3,    3,    1,    3,
    3,    3,    1,    2,    1,    2,    1,    3,    1,    1,
    1,
};
static const short yydefred[] = {                         1,
    0,    0,    0,   41,    0,    0,    0,    0,   39,    0,
    0,    0,    0,    0,    0,    0,   33,   35,   37,    2,
    4,    5,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   40,   34,   36,    0,    3,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    6,   38,
    0,    0,    0,    0,    0,    0,    0,   30,   31,   32,
};
static const short yydgoto[] = {                          1,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,
};
static const short yysindex[] = {                         0,
  -33,  -44,  -34,    0,  -60,   23,   29,   25,    0,  -29,
 -226, -217, -178, -224,   53,   -6,    0,    0,    0,    0,
    0,    0,   23,   23,   23,   23,   23,   23,   23,   23,
   23,   23,   25,    0,    0,    0,   60,    0,   23,   23,
   23,   23,   23,   23,   23,   23,   23,   23, -226, -226,
 -226, -226, -226, -226, -226, -226, -226, -226,    0,    0,
 -217, -178, -224,   53,   53,   -6,   -6,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,  -37,    0,    0,    0,    0,    0,
  -24,    7,  -39,   -2,  -17,  -32,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -15,   -3,
   -1,   12,   13,   18,   19,   21,   35,   38,    0,    0,
    8,    5,    2,  -12,   -7,  -27,  -22,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,   -5,   58,   63,   64,   62,   49,   55,   27,   98,
    0,    0,
};
#define YYTABLESIZE 289
static const short yytable[] = {                         40,
   33,   21,   37,   40,   40,   40,    8,   40,   29,   40,
   29,    6,   29,   27,   21,   27,   17,   27,   28,   21,
   28,   40,   28,   26,   22,    7,   29,   59,   24,   38,
   48,   27,   35,   25,   17,   46,   28,    8,   23,    9,
   47,   26,   22,    7,   39,   20,   24,   19,   18,   42,
   43,   25,   10,   11,   40,    8,   23,    9,   12,   13,
   22,   14,    8,   20,    8,   19,   18,    6,    8,    6,
   10,   11,   68,   69,   70,   15,   12,   13,   16,   14,
   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,
   64,   65,    7,   15,   41,   44,   16,   45,   66,   67,
   60,   61,   63,   62,   36,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    7,    0,
    7,    0,    0,    0,    7,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    2,    3,    4,    5,    0,    0,    0,
    0,   21,   21,   40,   40,   40,   40,   40,   29,   29,
   29,   29,   29,   27,   27,   27,   27,   27,   28,   28,
   28,   28,   28,   26,   26,   26,   26,   26,   24,   24,
   24,   24,   24,   25,   25,   25,   25,   25,   23,   23,
   23,    0,   22,   22,   22,   20,   20,   19,   18,    0,
    0,    4,   34,    4,    5,    0,    0,    4,   34,
};
static const short yycheck[] = {                         37,
   61,   41,    8,   41,   42,   43,   40,   45,   41,   47,
   43,   45,   45,   41,   59,   43,   41,   45,   41,   59,
   43,   59,   45,   41,   59,   41,   59,   33,   41,   59,
   37,   59,    6,   41,   59,   42,   59,   41,   41,   41,
   47,   59,   41,   59,  271,   41,   59,   41,   41,  274,
  275,   59,   41,   41,  272,   59,   59,   59,   41,   41,
   59,   41,   40,   59,   40,   59,   59,   45,   40,   45,
   59,   59,   46,   47,   48,   41,   59,   59,   41,   59,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
   42,   43,  126,   59,  273,   43,   59,   45,   44,   45,
   41,   39,   41,   40,    7,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,
  126,   -1,   -1,   -1,  126,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  257,  258,  259,  260,   -1,   -1,   -1,
   -1,  271,  272,  271,  272,  273,  274,  275,  271,  272,
  273,  274,  275,  271,  272,  273,  274,  275,  271,  272,
  273,  274,  275,  271,  272,  273,  274,  275,  271,  272,
  273,  274,  275,  271,  272,  273,  274,  275,  271,  272,
  273,   -1,  271,  272,  273,  271,  272,  271,  271,   -1,
   -1,  259,  260,  259,  260,   -1,   -1,  259,  260,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 275
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'~'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"DUMP","CLEAR","NUM","VAR","PEQ","MEQ","TEQ","DEQ","REQ","LSEQ","RSEQ",
"AEQ","XOREQ","OREQ","BOR","BXOR","BAND","LS","RS",
};
static const char *yyrule[] = {
"$accept : commands",
"commands :",
"commands : commands command",
"command : assignment ';'",
"command : DUMP ';'",
"command : CLEAR ';'",
"assignment : VAR '=' assignment",
"assignment : VAR PEQ bitwise_or",
"assignment : VAR MEQ bitwise_or",
"assignment : VAR TEQ bitwise_or",
"assignment : VAR DEQ bitwise_or",
"assignment : VAR REQ bitwise_or",
"assignment : VAR LSEQ bitwise_or",
"assignment : VAR RSEQ bitwise_or",
"assignment : VAR AEQ bitwise_or",
"assignment : VAR XOREQ bitwise_or",
"assignment : VAR OREQ bitwise_or",
"assignment : bitwise_or",
"bitwise_or : bitwise_or BOR bitwise_xor",
"bitwise_or : bitwise_xor",
"bitwise_xor : bitwise_xor BXOR bitwise_and",
"bitwise_xor : bitwise_and",
"bitwise_and : bitwise_and BAND shift",
"bitwise_and : shift",
"shift : shift LS add_sub",
"shift : shift RS add_sub",
"shift : add_sub",
"add_sub : add_sub '+' mul_div_rem",
"add_sub : add_sub '-' mul_div_rem",
"add_sub : mul_div_rem",
"mul_div_rem : mul_div_rem '*' neg",
"mul_div_rem : mul_div_rem '/' neg",
"mul_div_rem : mul_div_rem '%' neg",
"mul_div_rem : neg",
"neg : '-' neg",
"neg : bitwise_not",
"bitwise_not : '~' bitwise_not",
"bitwise_not : parenthesis",
"parenthesis : '(' assignment ')'",
"parenthesis : expr",
"expr : VAR",
"expr : NUM",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 156 "cexpr.y"

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
#line 366 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 67 "cexpr.y"
	{   if(overflow == 1) {
                                printf("overflow\n");
                                overflow = 0;
                            } else if(div_by_zero == 1) {
                                        printf("dividebyzero\n");
                                        div_by_zero = 0;
                            } else printf("%d\n", yystack.l_mark[-1].num); 
                        }
break;
case 4:
#line 75 "cexpr.y"
	{ dump(); }
break;
case 5:
#line 76 "cexpr.y"
	{ clear(); }
break;
case 6:
#line 79 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] = yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 7:
#line 80 "cexpr.y"
	{ overflow1(sigma[yystack.l_mark[-2].var], yystack.l_mark[0].num, 0);
                                   sigma[yystack.l_mark[-2].var] += yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; 
                                 }
break;
case 8:
#line 83 "cexpr.y"
	{ overflow1(sigma[yystack.l_mark[-2].var], yystack.l_mark[0].num, 1);
                                   sigma[yystack.l_mark[-2].var] -= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; 
                                 }
break;
case 9:
#line 86 "cexpr.y"
	{ overflow2(sigma[yystack.l_mark[-2].var], yystack.l_mark[0].num);
                                   sigma[yystack.l_mark[-2].var] *= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; 
                                 }
break;
case 10:
#line 89 "cexpr.y"
	{ if(yystack.l_mark[0].num != 0) {
                                      sigma[yystack.l_mark[-2].var] /= yystack.l_mark[0].num; 
                                      yyval.num = sigma[yystack.l_mark[-2].var]; 
                                   } else {
                                        sigma[yystack.l_mark[-2].var] /= yystack.l_mark[0].num;
                                        yyval.num = sigma[yystack.l_mark[-2].var];
                                   }
                                 }
break;
case 11:
#line 97 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] %= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 12:
#line 98 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] <<= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 13:
#line 99 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] >>= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 14:
#line 100 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] &= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 15:
#line 101 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] ^= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 16:
#line 102 "cexpr.y"
	{ sigma[yystack.l_mark[-2].var] |= yystack.l_mark[0].num; yyval.num = sigma[yystack.l_mark[-2].var]; }
break;
case 17:
#line 103 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 18:
#line 106 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num | yystack.l_mark[0].num; }
break;
case 19:
#line 107 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 20:
#line 110 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num ^ yystack.l_mark[0].num; }
break;
case 21:
#line 111 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 22:
#line 114 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num & yystack.l_mark[0].num; }
break;
case 23:
#line 115 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 24:
#line 118 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num << yystack.l_mark[0].num; }
break;
case 25:
#line 119 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num >> yystack.l_mark[0].num; }
break;
case 26:
#line 120 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 27:
#line 123 "cexpr.y"
	{ overflow1(yystack.l_mark[-2].num, yystack.l_mark[0].num, 0); yyval.num = yystack.l_mark[-2].num + yystack.l_mark[0].num; }
break;
case 28:
#line 124 "cexpr.y"
	{ overflow1(yystack.l_mark[-2].num, yystack.l_mark[0].num, 1); yyval.num = yystack.l_mark[-2].num - yystack.l_mark[0].num; }
break;
case 29:
#line 125 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 30:
#line 128 "cexpr.y"
	{ overflow2(yystack.l_mark[-2].num, yystack.l_mark[0].num); yyval.num = yystack.l_mark[-2].num * yystack.l_mark[0].num; }
break;
case 31:
#line 129 "cexpr.y"
	{ if(yystack.l_mark[0].num != 0) yyval.num = yystack.l_mark[-2].num / yystack.l_mark[0].num; 
                                        else {
                                            yyval.num = yystack.l_mark[-2].num;
                                            div_by_zero = 1;
                                        }
                                    }
break;
case 32:
#line 135 "cexpr.y"
	{ yyval.num = yystack.l_mark[-2].num % yystack.l_mark[0].num; }
break;
case 33:
#line 136 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 34:
#line 139 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num * -1; }
break;
case 35:
#line 140 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 36:
#line 143 "cexpr.y"
	{ yyval.num = ~yystack.l_mark[0].num; }
break;
case 37:
#line 144 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 38:
#line 147 "cexpr.y"
	{ yyval.num = yystack.l_mark[-1].num; }
break;
case 39:
#line 148 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 40:
#line 151 "cexpr.y"
	{ yyval.num = sigma[yystack.l_mark[0].var];}
break;
case 41:
#line 152 "cexpr.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
#line 753 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
