// Pixel.h
#ifndef have_Pixel
#define have_Pixel

struct Pixel
{
    double m_value;

public:
    Pixel()
        : m_value(0.0)
    {}

    Pixel(double d)
        : m_value(d)
    {}

    bool operator>= (const Pixel &rhs) 
    {
        return m_value >= rhs.m_value;
    }

    Pixel & operator+=(const Pixel &rhs) 
    {
        m_value += rhs.m_value;

        return *this;
    }

    const Pixel operator+(const Pixel &other) const 
    {
        Pixel res = *this;
        res += other;

        return res;
    }

    Pixel & operator-=(const Pixel &rhs) 
    {
        m_value -= rhs.m_value;

        return *this;
    }

    const Pixel operator-(const Pixel &other) const 
    {
        Pixel res = *this;
        res -= other;

        return res;
    }

    Pixel & operator*=(const Pixel &rhs) 
    {
        m_value *= rhs.m_value;

        return *this;
    }

    const Pixel operator*(const Pixel &other) const 
    {
        Pixel res = *this;
        res *= other;

        return res;
    }

    Pixel & operator/=(const Pixel &rhs) 
    {
        m_value /= rhs.m_value;

        return *this;
    }

    const Pixel operator/(const Pixel &other) const 
    {
        Pixel res = *this;
        res /= other;

        return res;
    }

    virtual ~Pixel(){}
};



#endif // have_Pixel

