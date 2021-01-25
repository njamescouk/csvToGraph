// PclFlagInstance.h
#ifndef have_PclFlagInstance
#define have_PclFlagInstance

#include <string>

class PclFlagInstance
{
    std::string m_name;
    std::string m_value;
    bool m_hasArg;

public:
    PclFlagInstance()
        : m_hasArg(false)
    {}

    PclFlagInstance(std::string name)
        : m_name(name),
          m_hasArg(false)
    {}
    
    PclFlagInstance(std::string name, std::string value)
        : m_name(name),
          m_value(value),
          m_hasArg(true)
    {}
    
    virtual ~PclFlagInstance(){}

    std::string getName()
    {
        return m_name;
    }

    std::string getValue()
    {
        return m_value;
    }

    bool hasArg()
    {
        return m_hasArg;
    }
};



#endif // have_PclFlagInstance

