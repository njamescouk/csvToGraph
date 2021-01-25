// Cmdline.h
#ifndef have_Cmdline
#define have_Cmdline

#include <string>
#include "PclFlagList.h"
#include "PclArgList.h"
#include "CmdLineSpec.h"

class Cmdline
{
    PclFlagList m_flags;
    PclArgList m_args;
    bool m_valid;

public:
    Cmdline(bool valid = false) 
        : m_valid(valid)
    {
    }

    virtual ~Cmdline()
    {
    }

    void setFlags(PclFlagList flags)
    {
        m_flags = flags;
    }

    void setArgList(PclArgList args)
    {
        m_args = args;
    }

    PclArgList getArgList()
    {
        return m_args;
    }

    void appendArgument(std::string s)
    {
        m_args.push_back(s);
    }

    void addOption(std::string name)
    {
        m_flags[name] = PclFlag();
    }

    void addOption(std::string name, std::string value)
    {
        m_flags[name] = PclFlag(value.c_str());
    }

    void invalidate()
    {
        m_valid = false;
    }

    bool isValid()
    {
        return m_valid;
    }

    bool hasOption(std::string sought)
    {
        if (m_flags.count(sought) == 0)
            return false;
        
        return true;
    }

    std::string getOptionValue(std::string sought)
    {
        std::string res = "";

        if (hasOption(sought))
        {
            PclFlag fl = m_flags[sought];
            if (fl.hasArg())
            {
                res = fl.getValue();
            }
        }

        return res;
    }

    size_t numArguments()
    {
        return m_args.size();
    }

    size_t numOptions()
    {
        return m_flags.size();
    }

    std::string getArgument(size_t i)
    {
        std::string res = "";

        if (i < m_args.size())
        {
            res = m_args[i];
        }

        return res;
    }

    std::string toString()
    {
        std::string res = "";

        res += optionsString();
        
        size_t i;
        for (i = 0; i < m_args.size(); i++)
        {
            res += m_args[i] + "\n";
        }

        return res;
    }

    std::string optionsString()
    {
        std::string res = "";
        PclFlagList::iterator it;
        for (it = m_flags.begin(); it != m_flags.end(); it++)
        {
            res += "-" + it->first;
            PclFlag fl = it->second;
            if (fl.hasArg())
            {
                res += ":" + fl.getValue();
            }
            res += "\n";
        }

        return res;
    }

    void validate(CmdLineSpec ls)
    {
        m_valid = true;

        if (m_flags.empty() && m_args.empty())
        {
            return;
        }

        PclFlagList::iterator it;
        for (it = m_flags.begin(); it != m_flags.end() && m_valid; it++)
        {
            std::string flagName = it->first;
            PclFlag argCur = it->second;

            OptionSpec os = ls.getSpec(flagName);
            if (os.empty())
            {
                m_valid = false;
            }
            else
            {
                if (os.hasArgument() != argCur.hasArg())
                    m_valid = false;
            }
        }
    }
};



#endif // have_Cmdline
