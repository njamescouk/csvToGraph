// PclFlagList.h
#ifndef have_PclFlagList
#define have_PclFlagList

#include <map>
#include <string>
#include "PclFlag.h"
#include "PclFlagInstance.h"

class PclFlagList : public std::map<std::string, PclFlag>
{
public:
    PclFlagList()
    {};
    
    virtual ~PclFlagList()
    {};

    void add(PclFlagInstance fi)
    {
        std::string name = fi.getName();
        PclFlag f;
        if (fi.hasArg())
        {
            f.setValue(fi.getValue());
        }

        (*this)[name] = f;
    }
};



#endif // have_PclFlagList
