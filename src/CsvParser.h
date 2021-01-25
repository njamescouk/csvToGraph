// CsvParser.h
#ifndef have_CsvParser
#define have_CsvParser

#include <vector>
#include <string>
#include "ParsedCsv.h"
#include "pcsvfns.h"

extern int pscvdebug;
extern ParsedCsv *pgResult;

class CsvParser
{
    ParsedCsv m_csv;

public:
    CsvParser()
    {}

    virtual ~CsvParser(){}

    ParsedCsv getParsedCsv()
    {
        return m_csv;
    }

    bool parseString(const char *s)
    {
        //pcsvdebug = 1;
        scanString(s);
        pgResult = &m_csv; // pgResult referenced in yyparse
        return pcsvparse() == 0;
    }

    // parse no longer defaults to stdin...
    // use parse(stdin) directly
    bool parse(std::string filename) 
    {
        /*
        std::ifstream ifs;
        ifs.open(filename);
        if (ifs.fail())
        {
            fprintf(stderr, "error: cannot open %s\n", filename.c_str());
        }
        std::string line;
        std::getline(ifs, line);
        */

        FILE *fp = 0;
    
        std::string err;

        if (filename.empty())
        {
            return false;
        }
        else
        {
            fp = fopen(filename.c_str(), "rt");
            if (fp == 0)
            {
                err = "CsvParser::parse: cannot open " + filename;
                perror(err.c_str());
                return false;
            }
        }

        bool res = parse(fp);

        return res;
    }

    bool parse(FILE *fp) 
    {
        if (fp != 0) // shouldn't happen
        {
            pcsvin = fp;
            pgResult = &m_csv; // pgResult referenced in yyparse
            // pcsvdebug = 1;
            int parseRes = pcsvparse();
            return (parseRes == 0);
        }

        return false;
    }

    bool isRectangular()
    {
        return m_csv.isRectangular();
    }

    void writeHtml(FILE *fp)
    {
        return m_csv.writeHtml(fp);
    }
};



#endif // have_CsvParser

