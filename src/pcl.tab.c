#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define yyparse pclparse
#define yylex pcllex
#define yyerror pclerror
#define yychar pclchar
#define yyval pclval
#define yylval pcllval
#define yydebug pcldebug
#define yynerrs pclnerrs
#define yyerrflag pclerrflag
#define yyss pclss
#define yyssp pclssp
#define yyvs pclvs
#define yyvsp pclvsp
#define yylhs pcllhs
#define yylen pcllen
#define yydefred pcldefred
#define yydgoto pcldgoto
#define yysindex pclsindex
#define yyrindex pclrindex
#define yygindex pclgindex
#define yytable pcltable
#define yycheck pclcheck
#define yyname pclname
#define yyrule pclrule
#define YYPREFIX "pcl"
/* C definitions 
can be #included
*/
#pragma warning( disable : 4786 )
#pragma warning( disable : 4996 )

#include "Cmdline.h"
#include "PclArgList.h"
#include "PclFlagList.h"
#include "PclFlagInstance.h"
#include "PclArg.h"
#include "pclYaccFns.h"

Cmdline gPclResult;
bool gShowErr = false;

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
#define MINUS 257
#define STRING 258
#define FLAG_VALUE 259
#define LEXERR 260
#define YYERRCODE 256
short pcllhs[] = {                                        -1,
    0,    0,    0,    0,    2,    2,    3,    3,    1,    1,
    4,
};
short pcllen[] = {                                         2,
    2,    1,    1,    0,    1,    2,    2,    3,    1,    2,
    1,
};
short pcldefred[] = {                                      0,
    0,   11,    0,    0,    0,    5,    9,    0,   10,    0,
    6,    8,
};
short pcldgoto[] = {                                       3,
    4,    5,    6,    7,
};
short pclsindex[] = {                                   -255,
 -254,    0,    0, -253, -255,    0,    0, -252,    0, -253,
    0,    0,
};
short pclrindex[] = {                                      8,
    0,    0,    0,    9,   10,    0,    0,    1,    0,   11,
    0,    0,
};
short pclgindex[] = {                                      0,
    7,    0,   12,   -4,
};
#define YYTABLESIZE 259
short pcltable[] = {                                       9,
    7,    1,    2,    8,    2,    9,   12,    4,    2,    3,
    1,   10,    0,    0,    0,    0,   11,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    7,    7,
};
short pclcheck[] = {                                       4,
    0,  257,  258,  258,  258,   10,  259,    0,    0,    0,
    0,    5,   -1,   -1,   -1,   -1,    5,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 260
#if YYDEBUG
char *pclname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"MINUS","STRING","FLAG_VALUE",
"LEXERR",
};
char *pclrule[] = {
"$accept : cmdline",
"cmdline : flagList argList",
"cmdline : argList",
"cmdline : flagList",
"cmdline :",
"flagList : flag",
"flagList : flagList flag",
"flag : MINUS STRING",
"flag : MINUS STRING FLAG_VALUE",
"argList : arg",
"argList : argList arg",
"arg : STRING",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
/* user code */

void yyerror (char *s)
{
    if (gShowErr)
        fprintf (stderr, "%s\n", s);
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
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
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
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
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
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
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
{
        /* flagList argList */
        if (yyvsp[-1].PclFlagListPtr != 0 && yyvsp[0].ArgListPtr != 0)
        {
            gPclResult.setFlags(*yyvsp[-1].PclFlagListPtr);
            gPclResult.setArgList(*yyvsp[0].ArgListPtr);

            delete yyvsp[-1].PclFlagListPtr;
            delete yyvsp[0].ArgListPtr;
        }
    }
break;
case 2:
{
        /* argList */
        if (yyvsp[0].ArgListPtr != 0)
        {
            gPclResult.setArgList(*yyvsp[0].ArgListPtr);

            delete yyvsp[0].ArgListPtr;
        }
    }
break;
case 3:
{
        /* flagList */
        if (yyvsp[0].PclFlagListPtr != 0)
        {
            gPclResult.setFlags(*yyvsp[0].PclFlagListPtr);

            delete yyvsp[0].PclFlagListPtr;
        }
    }
break;
case 4:
{
        gPclResult = Cmdline();
    }
break;
case 5:
{
        /* flag */
        if (yyvsp[0].PclFlagInstancePtr != 0)
        {
            yyval.PclFlagListPtr = new PclFlagList;
            yyval.PclFlagListPtr->add(*yyvsp[0].PclFlagInstancePtr);

            delete yyvsp[0].PclFlagInstancePtr;
        }
    }
break;
case 6:
{
        /* flagList flag */
        if (yyvsp[-1].PclFlagListPtr != 0 && yyvsp[0].PclFlagInstancePtr != 0)
        {
            yyval.PclFlagListPtr = yyvsp[-1].PclFlagListPtr;
            yyval.PclFlagListPtr->add(*yyvsp[0].PclFlagInstancePtr);

            delete yyvsp[0].PclFlagInstancePtr;
        }
    }
break;
case 7:
{
        /* MINUS STRING */
        yyval.PclFlagInstancePtr = new PclFlagInstance(yyvsp[0].CharPtr);
    }
break;
case 8:
{
        /* MINUS STRING STRING */
        yyval.PclFlagInstancePtr = new PclFlagInstance(yyvsp[-1].CharPtr, yyvsp[0].CharPtr);
    }
break;
case 9:
{
        /* arg */
        if (yyvsp[0].ArgPtr != 0)
        {
            yyval.ArgListPtr = new PclArgList;
            yyval.ArgListPtr->push_back(*yyvsp[0].ArgPtr);

            delete yyvsp[0].ArgPtr;
        }
    }
break;
case 10:
{
        /* argList arg */
        if (yyvsp[-1].ArgListPtr != 0 && yyvsp[0].ArgPtr != 0)
        {
            yyval.ArgListPtr = yyvsp[-1].ArgListPtr;
            yyval.ArgListPtr->push_back(*yyvsp[0].ArgPtr);

            delete yyvsp[0].ArgPtr;
        }
    }
break;
case 11:
{
        /* STRING */
        yyval.ArgPtr = new PclArg(yyvsp[0].CharPtr);
    }
break;
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
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
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
