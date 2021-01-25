// LineParameters.h
#ifndef have_LineParameters
#define have_LineParameters

extern const int g_NumPointShapes;
extern const int g_NumColours;

enum LINESTYLE
{
    LINESTYLE_SOLID,
    LINESTYLE_DASHED,
};

struct LineParameters
{
    bool m_nopt;
    LINESTYLE m_lineStyle;
    int m_width;
    int m_colourNdx;
    int m_pointNdx;
    double m_xSF;
    double m_ySF;

    LineParameters()
    {}

    LineParameters(int colourNdx,
                    int pointNdx,
                    // LINESTYLE lineStyle,
                    // int width,
                    bool nopt,
                    double xSF,
                    double ySF)
    : m_colourNdx((colourNdx % (g_NumColours - 1)) + 1) // don't use white
    , m_pointNdx((pointNdx % g_NumPointShapes))
    , m_lineStyle(LINESTYLE_SOLID)
    , m_width(2)
    , m_nopt(nopt)
    , m_xSF(xSF)
    , m_ySF(ySF)
    {}
};



#endif // have_LineParameters

