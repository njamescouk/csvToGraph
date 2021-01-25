// UserToGraph.h
#ifndef have_UserToGraph
#define have_UserToGraph

#include "Bound.h"
#include "Pixel.h"

class UserToGraph
{
    double m_minX;
    double m_minY;
    double m_xScaleFactor;
    double m_yScaleFactor;
    bool m_xSfIsReciprocal;
    bool m_ySfIsReciprocal;
    Pixel m_xGridSpacing;
    Pixel m_yGridSpacing;

public:
    UserToGraph()
    {}

    UserToGraph(Pixel graphMaxX,
                Pixel graphMaxY,
                Bound xBound,
                Bound yBound)
                : m_minX (xBound.lo())
                , m_minY (yBound.lo())
                , m_xSfIsReciprocal(false)
                , m_ySfIsReciprocal(false)
    {
        if (fabs(xBound.span()) < DBL_EPSILON)
        {
            fprintf(stderr, "xBound too small\n");
            return;
        }

        if (xBound.span() > graphMaxX.m_value)
        {
            m_xScaleFactor = graphMaxX.m_value / xBound.span();
        }
        else
        {
            m_xScaleFactor = xBound.span() / graphMaxX.m_value;
            m_xSfIsReciprocal = true;
        }

        if (yBound.span() > graphMaxY.m_value)
        {
            m_yScaleFactor = graphMaxY.m_value / yBound.span();
        }
        else
        {
            m_yScaleFactor = yBound.span() / graphMaxY.m_value;
            m_ySfIsReciprocal = true;
        }

        if (m_xSfIsReciprocal)
            m_xGridSpacing = xBound.magnitude() / m_xScaleFactor;
        else
            m_xGridSpacing = xBound.magnitude() * m_xScaleFactor;

        if (m_ySfIsReciprocal)
            m_yGridSpacing = yBound.magnitude() / m_yScaleFactor;
        else
            m_yGridSpacing = yBound.magnitude() * m_yScaleFactor;
    }

    virtual ~UserToGraph(){}

    Pixel xDistance(double d)
    {
        if (m_xSfIsReciprocal)
            return Pixel(d / m_xScaleFactor);

        return Pixel(d * m_xScaleFactor);
    }

    Pixel yDistance(double d)
    {
        if (m_ySfIsReciprocal)
            return Pixel(d / m_yScaleFactor);

        return Pixel(d * m_yScaleFactor);
    }

    Pixel xPos(double d)
    {
        if (m_xSfIsReciprocal)
             return Pixel((d - m_minX) / m_xScaleFactor);

        return Pixel((d - m_minX) * m_xScaleFactor);
    }

    Pixel yPos(double d)
    {
        if (m_ySfIsReciprocal)
            return Pixel((d - m_minY) / m_yScaleFactor);

        return Pixel((d - m_minY) * m_yScaleFactor);
    }

    double xSf()
    {
        if (m_xSfIsReciprocal)
            return 1.0 / m_xScaleFactor;

        return m_xScaleFactor;
    }

    double ySf()
    {
        if (m_ySfIsReciprocal)
            return 1.0 / m_yScaleFactor;

        return m_yScaleFactor;
    }

    Pixel xGridSpacing()
    {
        return m_xGridSpacing;
    }

    Pixel yGridSpacing()
    {
        return m_yGridSpacing;
    }

    std::string toString()
    {
        char buf[BUFSIZ];

        sprintf(buf, 
                "minX        : %f\n"
                "minY        : %f\n"
                "xScaleFactor: %f\n"
                "yScaleFactor: %f\n"
                "xGridSpacing: %fpx\n"
                "yGridSpacing: %fpx",
                m_minX,
                m_minY,
                xSf(),
                ySf(),
                m_xGridSpacing.m_value,
                m_yGridSpacing.m_value);

        return buf;
    }
};



#endif // have_UserToGraph

