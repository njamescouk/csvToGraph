#define MINUS 257
#define STRING 258
#define FLAG_VALUE 259
#define LEXERR 260
typedef union
{
   /* types available to grammar */
    Cmdline *CmdlinePtr;
    PclArgList *ArgListPtr;
    PclFlagList *PclFlagListPtr;
    PclFlag *PclFlagPtr;
    PclFlagInstance *PclFlagInstancePtr;
    PclArg *ArgPtr;
    char *CharPtr;
} YYSTYPE;
extern YYSTYPE pcllval;
