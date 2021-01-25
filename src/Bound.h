// Bound.h
#ifndef have_Bound
#define have_Bound

#include "StandardForm.h"
#include <cassert>

class Bound
{
    double m_userLo;
    double m_userHi;
    double m_boundLo;
    double m_boundHi;
    double m_magnitude;
    double m_boundSpan;
    std::string m_err;

    int getNumDigits(double d)
    {
        double res = 0;

        double absD = fabs(d);
        if (absD > 1.0 + DBL_EPSILON)
        {
            double logd = log10(absD);
            res = fabs(floor(logd) + 1);
        }

        return (int)res;
    }

    int getExponent(double d)
    {
        double res = 0;

        double absD = fabs(d);
        if (absD > DBL_EPSILON)
        {
            double logd = log10(absD);
            res = floor(logd);
        }

        return (int)res;
    }

public:
    Bound()
    {}

    /*
        magnitude         gridSpacing 
        ---------   =     -----------
        boundSpan          pixels
    */
    Bound(double d1, double d2)
    {
        if (d1 > d2)
        {
            m_userLo = d2;
            m_userHi = d1;
        }
        else if (d1 < d2)
        {
            m_userLo = d1;
            m_userHi = d2;
        }
        else
        { 
            // pretend 1 either side
            m_userHi = d2 + 1;
            m_userLo = d2 - 1;
        }

        assert (fabs(m_userLo) > DBL_EPSILON || fabs(m_userHi) > DBL_EPSILON);

        double userSpan = m_userHi - m_userLo;
        StandardForm stfoUserSpan(userSpan);
        m_magnitude = pow(10, stfoUserSpan.getExponent());

        /*
        compute bounds by expressing userVal as (newMantissa * 10^something) * m_magnitude

        so if userVal = mantissa * 10^exp = (mantissa * 10^exp/10^mag) * 10^mag
        newMantissa = (mantissa * 10^exp/10^mag) = userVal/10^mag

        note - userVal now expressed as (mantissa * 10^exp/10^mag) * 10^mag

        take floor of userLo newMantissa as mantissa of boundLo
        take ceil of userLo newMantissa as mantissa of boundHi
        */

        double rebasedLo = m_userLo / m_magnitude;
        m_boundLo = floor(rebasedLo) * m_magnitude;

        double rebasedHi = m_userHi / m_magnitude;
        m_boundHi = ceil(rebasedHi) * m_magnitude;

        m_boundSpan = m_boundHi - m_boundLo;

        if (fabs(m_boundSpan) < DBL_EPSILON)
        {
            char buf[BUFSIZ];
            sprintf(buf, "bound (%f, %f) failed\n", d1, d2);
            m_err = buf;
            m_boundSpan = m_magnitude;
        }

        assert (m_magnitude <= m_boundSpan);
        return;
    }

    virtual ~Bound(){}

    double lo()
    {
        return m_boundLo;
    }

    double hi()
    {
        return m_boundHi;
    }

    double span()
    {
        return m_boundSpan;
    }

    double magnitude()
    {
        return m_magnitude;
    }

    std::string err()
    {
        return m_err;
    }

    std::string toString()
    {
        char buf[BUFSIZ];

        if (fabs(m_boundHi) > DBL_MAX - 1
            || fabs(m_boundLo) > DBL_MAX - 1
            || fabs(m_magnitude) > DBL_MAX - 1
            || fabs(m_userHi) > DBL_MAX - 1
            || fabs(m_userLo) > DBL_MAX - 1
            )
        {
            return "out of range";
        }

        sprintf(buf, 
                "userLo      : %f\n"
                "userHi      : %f\n"
                "boundLo     : %f\n"
                "boundHi     : %f\n"
                "magnitude   : %f",
                m_userLo,
                m_userHi,
                m_boundLo,
                m_boundHi,
                m_magnitude);

        return buf;
    }

};



#endif // have_Bound

