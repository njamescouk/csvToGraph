// StandardForm.h
#ifndef have_StandardForm
#define have_StandardForm

class StandardForm
{
    double m_mantissa;
    int m_exponent;

public:
    StandardForm()
        : m_mantissa(0.0)
        , m_exponent(0)
    {}
    
    StandardForm(double d)
        : m_mantissa(0.0)
        , m_exponent(0)
    {
        if (fabs(d) > DBL_EPSILON)
        {
            int sign = 1;
            if (d < 0.0)
                sign = -1;

            // d/exponent = mantissa
            double logAbs = log10(fabs(d));
            double flLog = floor(logAbs);
            m_exponent = (int)flLog;
            double logMantissa = logAbs - flLog;
            m_mantissa = pow(10.0, logMantissa) * sign;
        }
    }

    operator double()
    {
        return m_mantissa * pow(10.0, m_exponent);
    }

    double getExponent()
    {
        return m_exponent;
    }

    double getMantissa()
    {
        return m_mantissa;
    }

    virtual ~StandardForm(){}
};



#endif // have_StandardForm

