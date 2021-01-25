// CmdLineParser.h
#ifndef have_CmdLineParser
#define have_CmdLineParser

#include <string>
#include "CmdLine.h"
#include "CmdLineSpec.h"
#include "pclYaccfns.h"

extern Cmdline gPclResult;
std::map<std::string, OptionSpec> cmdlineLexingSpecs;

class CmdLineParser
{
    std::string m_scanString;
    CmdLineSpec m_spec;

public:
    CmdLineParser()
    {
    }

    CmdLineParser(int argc, char *argv[], CmdLineSpec cls, bool debug = false)
        : m_spec(cls)
    {
        if (debug)
            pcldebug = 1;

        m_scanString.clear();

        // argc == n => n-1 args in argv[1] ... argv[n-1]
        int i;
        for (i = 1; i < argc; i++)
        {
            m_scanString += argv[i];
            m_scanString += 0x1e;
        }
    }

    virtual ~CmdLineParser()
    {
    }

    // return possibly valid (against spec in CmdLineSpec) Cmdline 
    Cmdline parse()
    {
        Cmdline res;
        // pcldebug = 1;
        // -bbbb -x -c 8uggg 222 iuoiuoiu-66
        pclScanString(m_scanString.c_str());
        cmdlineLexingSpecs = m_spec;
        if (pclparse() == 0)
        {
            res = gPclResult;
            res.validate(m_spec);
        }
        else
        {
            res.invalidate();
        }

        return res;
    }

};



#endif // have_CmdLineParser

