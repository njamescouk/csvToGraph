// GraphParameters.h
#ifndef have_GraphParameters
#define have_GraphParameters

struct GraphParameters
{
    std::string m_src;
    bool m_nopt;
    bool m_noax;
    bool m_nojoin;
    bool m_nohead;
    bool m_nokey;
    bool m_nolin;
    bool m_nopap;
    bool m_showX0;
    bool m_showY0;
    bool m_xCol;
    bool m_yCol;
    bool m_exclCol;
    bool m_verbose;
    bool m_xIsOrdinal;

    GraphParameters()
    {}

    GraphParameters(std::string src
                    , bool nopt
                    , bool noax
                    , bool nojoin
                    , bool nohead
                    , bool nokey
                    , bool nolin
                    , bool nopap
                    , bool showx
                    , bool showy
                    , bool xcol
                    , bool ycol
                    , bool excl
                    , bool verbose
                    )
    : m_src(src)
    , m_nopt(nopt)
    , m_noax(noax)
    , m_nojoin(nojoin)
    , m_nohead(nohead)
    , m_nokey(nokey)
    , m_nolin(nolin)
    , m_nopap(nopap)
    , m_showX0(showx)
    , m_showY0(showy)
    , m_xCol(xcol)
    , m_yCol(ycol)
    , m_exclCol(excl)
    , m_verbose(verbose)
    , m_xIsOrdinal(false)
    {}

    std::string toString()
    {
        std::string res = "src   : ";
        res += m_src;
        res += "\nnopt  : ";
        res += m_nopt?"true":"false";
        res += "\nnoax  : ";
        res += m_noax?"true":"false";
        res += "\nnojoin: ";
        res += m_nojoin?"true":"false";
        res += "\nnohead: ";
        res += m_nohead?"true":"false";
        res += "\nnokey : ";
        res += m_nokey?"true":"false";
        res += "\nnolin : ";
        res += m_nolin?"true":"false";
        res += "\nnopap : ";
        res += m_nopap?"true":"false";
        res += "\nx0    : ";
        res += m_showX0?"true":"false";
        res += "\ny0    : ";
        res += m_showY0?"true":"false";
        res += "\nverbose  : ";
        res += m_verbose?"true":"false";
        res += "\nxIsOrdinal  : ";
        res += m_xIsOrdinal?"true":"false";
            
        return res;
    }
};



#endif // have_GraphParameters

