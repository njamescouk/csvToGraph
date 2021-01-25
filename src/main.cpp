#include "pcsvfns.h"
#include "CsvParser.h" 
#include "CmdLineParser.h" 
#include "Graphing.h" 
#include "SvgWriter.h"
#include "GraphParameters.h"

extern int yydebug;
char *progname = 0;
char *szVersion = "1.0";
char *szBuildTime = "2021-01-25 00:05:52";

void version(FILE *fp);
void build(FILE *fp);
std::vector<CsvColumn> makeRealColumns(std::string iName, 
                                       ParsedCsv pc, 
                                       int exclColNdx,
                                       bool haveHeader = true, 
                                       bool verbose=false);

//-o I:\usr\NIK\dev\csvToGraph\debug.svg I:\usr\NIK\dev\csvToGraph\doc\example.csv
int main (int argc, char *argv[])
{
    int res = 0;
    progname = argv[0];
    CmdLineSpec specs;

    std::string blurb = progname;
    blurb += " <options> [filename] \n"
             "reads stdin or <filename> as csv numbers with \n"
             "labels on the first line. On success it writes\n"
             "a graph with the first column as x values and\n"
             "the other columns plotted and labelled on the\n"
             "y axis. Output is formatted as svg, optionally\n"
             "written to -o <outputFile>\n\n"

             "If using -excl in conjunction with -xcol and /\n"
             "or -ycol note that exclusion happens first, then\n"
             "-xcol and / or -ycol are applied to what's left.\n"
             "Also take care not to assign to a column now out\n"
             "of bounds. Note that using both -xcol and -ycol\n"
             "excludes all other columns.\n";

    specs["h"] = OptionSpec(false, "this help");
    specs["v"] = OptionSpec(false, "version");
    specs["bld"] = OptionSpec(false, "show build time");
    specs["o"] = OptionSpec(true, "specify output file");
    specs["nopt"] = OptionSpec(false, "don't show points");
    specs["noax"] = OptionSpec(false, "don't show axes");
    specs["nojoin"] = OptionSpec(false, "don't join discontinuties in columns");
    specs["nohead"] = OptionSpec(false, "data doesn't have a header");
    specs["nokey"] = OptionSpec(false, "don't show key to graph");
    specs["nolin"] = OptionSpec(false, "don't show lines between points");
    specs["nopap"] = OptionSpec(false, "don't show graph paper");
    specs["y0"] = OptionSpec(false, "show y = 0");
    specs["x0"] = OptionSpec(false, "show x = 0");
    specs["xcol"] = OptionSpec(true, "use column n as x values");
    specs["ycol"] = OptionSpec(true, "use column n as y values");
    specs["excl"] = OptionSpec(true, "exclude column n");
    specs["vb"] = OptionSpec(false, "verbose - try this if your graph isn't showing up");

    pcldebug = 0;
    CmdLineParser clp(argc, argv, specs);

    Cmdline cmdline = clp.parse();
    if (!cmdline.isValid())
    {
        CmdLineSpec(specs).help(blurb, stderr);
        return 1;
    }

    if (cmdline.hasOption("h"))
    {
        CmdLineSpec(specs).help(blurb, stdout);
        return 0;
    }

    if (cmdline.hasOption("v"))
    {
        version(stdout);
        return 0;
    }

    if (cmdline.hasOption("bld"))
    {
        build(stdout);
        return 0;
    }

    FILE *ifp = stdin;
    std::string fName = "stdin";
    if (cmdline.numArguments() > 0)
    {
        fName = cmdline.getArgument(0);
        // fName = "I:\\usr\\NIK\\dev\\csvToGraph\\test\\test16.csv";
        ifp = fopen(fName.c_str(), "rt");
        if (ifp == 0)
        {
            perror(fName.c_str());
            return 1;
        }
    }

    GraphParameters gp(fName
                       , cmdline.hasOption("nopt")
                       , cmdline.hasOption("noax")
                       , cmdline.hasOption("nojoin")
                       , cmdline.hasOption("nohead")
                       , cmdline.hasOption("nokey")
                       , cmdline.hasOption("nolin")
                       , cmdline.hasOption("nopap")
                       , cmdline.hasOption("x0")
                       , cmdline.hasOption("y0")
                       , cmdline.hasOption("xcol")
                       , cmdline.hasOption("ycol")
                       , cmdline.hasOption("excl")
                       , cmdline.hasOption("vb")
                        );

    int xColNdx = 0;
    if (gp.m_xCol)
        xColNdx = atoi(cmdline.getOptionValue("xcol").c_str()) - 1;

    int yColNdx = -1;
    if (gp.m_yCol)
        yColNdx = atoi(cmdline.getOptionValue("ycol").c_str()) - 1;

    int exclColNdx = -1;
    if (gp.m_exclCol)
        exclColNdx = atoi(cmdline.getOptionValue("excl").c_str()) - 1;

    FILE *ofp = stdout;
    std::string oName;
    if (cmdline.hasOption("o"))
    {
        oName = cmdline.getOptionValue("o");
        ofp = fopen(oName.c_str(), "wt");
        if (ifp == 0)
        {
            perror(oName.c_str());
            fclose(ifp);
            return __LINE__;
        }
    }

    CsvParser cp;
    if (cp.parse(ifp))
    {
        if (!cp.isRectangular())
        {
            fprintf(stderr, "data not a table\n");
            fclose(ifp);
            return __LINE__;
        }

        ParsedCsv pc = cp.getParsedCsv();
        // std::vector<CsvField>
        pc.applyColumnTypes(!gp.m_nohead);
        std::vector<CsvColumn> columns = makeRealColumns(fName, pc, exclColNdx, !gp.m_nohead, gp.m_verbose);
        std::string err;
        Graphing g(columns, xColNdx, yColNdx);
        if (g.getErr().empty())
        {
            SvgWriter sw(ofp, g, gp);
            if (sw.getErr().empty())
            {
                sw.write();
                if (!sw.getErr().empty()/* && gp.m_verbose*/)
                {
                    fprintf(stderr, "%s\n", sw.getErr().c_str());
                    res = __LINE__;
                }
            }
            else
            {
                // if (gp.m_verbose)
                {
                    fprintf(stderr, "%s\n", sw.getErr().c_str());
                    res = __LINE__;
                }
            }
        }
        else
        {
            // if (gp.m_verbose)
            {
                fprintf(stderr, "%s: %s\n", progname, g.getErr().c_str());
                res = __LINE__;
            }
        }
    }

    if (ifp != stdin)
        fclose(ifp);

    if (ofp != stdout)
        fclose(ofp);

    return res;
}

std::vector<CsvColumn> makeRealColumns(std::string iName, 
                                       ParsedCsv pc, 
                                       int exclColNdx,
                                       bool haveHeader, 
                                       bool verbose)
{
    std::vector<CsvColumn> res;

    if (pc.numRecords() == 0)
        return res;

    CsvRecord line1 = pc.getRecord(0);

    std::vector<std::string> rLabels;
    size_t colNdx;
    for (colNdx = 0; colNdx < line1.size(); colNdx++)
    {
        if (exclColNdx == colNdx)
            continue;

        if (pc.getColumnType(colNdx) != PARSED_COLUMN_TYPE_EMPTY)
        {
            if (haveHeader)
            {
                rLabels.push_back(line1[colNdx]);
            }
            else
            {
                size_t headNdx;
                for (headNdx = 0; headNdx < pc.maxFields(); headNdx++)
                {
                    char buf[BUFSIZ];
                    sprintf(buf, "column%ld", headNdx);
                    rLabels.push_back(buf);
                }
            }
        }
        else
        {
            if (verbose)
                fprintf(stderr, 
                        "column \"%s\" of %s is empty\n", 
                        line1[colNdx].c_str(), 
                        iName.c_str());
        }
    }

    // for each column
    int labelNdx = 0;
    for (colNdx = 0; colNdx < line1.size(); colNdx++)
    {
        if (pc.getColumnType(colNdx) == PARSED_COLUMN_TYPE_EMPTY || exclColNdx == colNdx)
        {
            continue;
        }

        // go down the rows storing doubles if poss
        CsvColumn newColumn(pc.getColumnType(colNdx));
        newColumn.setName(rLabels[labelNdx]);
        newColumn.reserve(pc.numRecords());
        size_t rowNdx = 0;
        if (haveHeader)
            rowNdx = 1;
        for (/* see above */; rowNdx < pc.numRecords(); rowNdx++)
        {
            CsvRecord curRec = pc.getRecord(rowNdx);
            CsvField curField = curRec[colNdx];

            if (rowNdx == 0 
                && !haveHeader 
                && !(curField.isNumeric() || curField.getType() == CSV_FIELD_TYPE_ANY))
            {
                if (verbose)
                    fprintf(stderr, 
                            "warning: the field \"%s\" at row %ld, column %ld of %s\n"
                            "doesn't seem to be a number. is -nohead correct?\n",
                            curField.c_str(),
                            rowNdx + 1,
                            colNdx + 1,
                            iName.c_str());
            }

            char *endP = 0;
            double d = strtod(curField.c_str(), &endP);
                
            bool valid = (endP != 0);
            char *ptr = endP;
            while (isspace(*ptr))
                ptr++;

            if (!curField.empty() && valid && (*ptr == 0))
            {
                CsvField convertedField(d);
                newColumn.push_back(convertedField);
                newColumn.setHasDouble();
            }
            else
            {
                newColumn.push_back(curField);
            }
        }

        res.push_back(newColumn);
        labelNdx++;
    }

    return res;
}

void version(FILE *fp)
{
    fprintf(fp, "%s version %s\n", progname, szVersion);
}

void build(FILE *fp)
{
    fprintf(fp, "%s built %s\n", progname, szBuildTime);
}

