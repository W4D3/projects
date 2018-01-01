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
extern YYSTYPE yylval;
