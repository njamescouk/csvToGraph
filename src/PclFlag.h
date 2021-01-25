// PclFlag.h
#ifndef have_PclFlag
#define have_PclFlag

#include <string>

class PclFlag
{
    bool m_hasArg;
    // this is key in PclFlagList std::string m_name;
    std::string m_value;

public:
    PclFlag()
    {
        m_hasArg = false;
    }

    PclFlag(const char *value)
    {
        m_value = value;
        m_hasArg = true;
    }

    virtual ~PclFlag()
    {
    }

    bool hasArg()
    {
        return m_hasArg;
    }

    std::string getValue()
    {
        return m_value;
    }

    void setValue(std::string s)
    {
        m_value = s;
        m_hasArg = true;
    }
};



#endif // have_PclFlag
