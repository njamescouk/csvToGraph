// PclArgList.h
#ifndef have_PclArgList
#define have_PclArgList

#include <string>
#include <vector>

class PclArgList : public std::vector<std::string>
{
public:
    PclArgList(){}
    virtual ~PclArgList(){}

    std::string toString()
    {
        std::string res;

        std::vector<std::string>::iterator it;
        for(it = begin(); it != end(); it++)
        {
            if (it != begin())
                res += " ";

            res += *it; 
        }

        return res;
    }

    std::string makeTrace()
    {
        std::string res;

        std::vector<std::string>::iterator it;
        for(it = begin(); it != end(); it++)
        {
            if (it != begin())
                res += "->";

            res += *it; 
        }

        return res;
    }
};



#endif // have_PclArgList
