#define COMMA_IN_QUOTE 257
#define COMMA 258
#define END_QUOTE 259
#define ESCAPED_QUOTE 260
#define QUOTE 261
#define STR 262
#define NEWLINE_IN_QUOTE 263
#define NEWLINE 264
#define WS_IN_QUOTE 265
#define WS 266
#define END_OF_FILE 267
#define LEXERR 268
typedef union 
{
    std::string *csvStr;
    CsvField *csvField;
    CsvRecord *csvRecord;
} YYSTYPE;
extern YYSTYPE pcsvlval;
