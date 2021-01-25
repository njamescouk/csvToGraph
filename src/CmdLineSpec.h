// CmdLineSpec.h
#ifndef have_CmdLineSpec
#define have_CmdLineSpec

#include <map>
#include <string>
#include <cstdio>
#include "OptionSpec.h"

class CmdLineSpec : public std::map<std::string, OptionSpec>
{
public:
    CmdLineSpec()
    {
    }

    CmdLineSpec(std::map<std::string, OptionSpec> specs)
    {
        insert(specs.begin(), specs.end());
    }

    virtual ~CmdLineSpec()
    {
    }

    bool hasFlag(char *flag)
    {
        if(find(flag) != end())
        {
            return true;
        }

        return false;
    }

    OptionSpec getSpec(std::string name)
    {
        std::map<std::string, OptionSpec>::iterator it = find(name);
        if(it != end())
        {
            return it->second;
        }

        return OptionSpec();
    }

    void help(std::string blurb, FILE* fp)
    {
        // std::string padding = "           ";
        fprintf(fp, "usage: %s\noptions are:\n", blurb.c_str());
        std::map<std::string, OptionSpec>::iterator it;
        for (it = begin(); it != end(); it++)
        {
            std::string opt = it->first;
            std::string hText = opt;
            if (it->second.hasArgument())
                hText = opt + " <value>";
            fprintf(fp, "    -%-15s", hText.c_str());
            OptionSpec osCur = it->second;
            osCur.print(fp);
        }
    }

};



#endif // have_CmdLineSpec

