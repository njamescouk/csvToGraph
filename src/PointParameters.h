// PointParameters.h
#ifndef have_PointParameters
#define have_PointParameters

enum POINT_SYMBOL
{
    POINT_SYMBOL_CIRCLE,
    POINT_SYMBOL_SQUARE,
    POINT_SYMBOL_TRIANGLE,
    POINT_SYMBOL_DIAMOND,
    POINT_SYMBOL_INVERTED_TRIANGLE,
    POINT_SYMBOL_CROSS,
};

const POINT_SYMBOL POINT_SHAPE[] =
{
    POINT_SYMBOL_CIRCLE,
    POINT_SYMBOL_SQUARE,
    POINT_SYMBOL_TRIANGLE,
    POINT_SYMBOL_DIAMOND,
    POINT_SYMBOL_INVERTED_TRIANGLE,
    POINT_SYMBOL_CROSS,
};

const int g_NumPointShapes = sizeof(POINT_SHAPE) / sizeof(int);

const std::string COLOURS[] =
{
    "white",
    "black",
    "red",
    "green",
    "blue",
    "cyan",
    "magenta",
    "orange"
};

const int g_NumColours = sizeof(COLOURS) / sizeof(std::string);

struct PointParameters
{
    int m_colourNdx;
    POINT_SYMBOL m_pointNdx;
    double m_xSF;
    double m_ySF;

    PointParameters()
    {}

    PointParameters(int colourNdx,
                    int pointNdx,
                    double xSF,
                    double ySF)
    : m_colourNdx((colourNdx % (g_NumColours - 1)) + 1) // don't use white
    , m_pointNdx((POINT_SYMBOL)(pointNdx % g_NumPointShapes))
    , m_xSF(xSF)
    , m_ySF(ySF)
    {}
};



#endif // have_PointParameters

