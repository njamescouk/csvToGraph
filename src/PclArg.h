// PclArg.h
#ifndef have_PclArg
#define have_PclArg

#include <string>

class PclArg : public std::string
{
public:
    PclArg(){};
    
    PclArg(char *s)
    {
        assign(s);
    }

    virtual ~PclArg(){};
};



#endif // have_PclArg
