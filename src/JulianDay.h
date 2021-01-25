// JulianDay.h
#ifndef have_JulianDay
#define have_JulianDay

#pragma warning(disable : 4996)

/*
    algorithm from  Bill Jefferys, bill@clyde.as.utexas.edu

    1) Express the date as Y M D, where Y is the year, M is the month
    number (Jan = 1, Feb = 2, etc.), and D is the day in the month.

    2) If the month is January or February, subtract 1 from the year
    to get a new Y, and add 12 to the month to get a new M. (Thus, we
    are thinking of January and February as being the 13th and 14th
    month of the previous year).

    3) Dropping the fractional part of all results of all
    multiplications and divisions, let

      A = Y/100
      B = A/4
      C = 2-A+B
      E = 365.25x(Y+4716)
      F = 30.6001x(M+1)
      JD= C+D+E+F-1524.5

    This is the Julian Day Number for the beginning of the date in
    question at 0 hours, Greenwich time. Note that this always gives
    you a half day extra. That is because the Julian Day begins at
    noon, Greenwich time. This is convenient for astronomers (who
    until recently only observed at night), but it is confusing.

    To convert a Julian Day Number to a Gregorian date, assume that it
    is for 0 hours, Greenwich time (so that it ends in 0.5). Do the
    following calculations, again dropping the fractional part of all
    multiplicatons and divisions. Note: This method will not give
    dates accurately on the Gregorian Proleptic Calendar, i.e., the
    calendar you get by extending the Gregorian calendar backwards to
    years earlier than 1582. using the Gregorian leap year rules. In
    particular, the method fails if Y<400. Thanks to a correspondent,
    Bo Du, for some ideas that have improved this calculation.

      Q = JD+0.5
      Z = Integer part of Q
      W = (Z - 1867216.25)/36524.25
      X = W/4
      A = Z+1+W-X
      B = A+1524
      C = (B-122.1)/365.25
      D = 365.25xC
      E = (B-D)/30.6001
      F = 30.6001xE
      Day of month = B-D-F+(Q-Z)
      Month = E-1 or E-13 (must get number less than or equal to 12)
      Year = C-4715 (if Month is January or February) or C-4716 (otherwise)*/

#include <string>
#include <cmath>

class JulianDay
{
    std::string m_err;
    double m_value;

    double integerPart(double d)
    {
        double res;

        modf(d, &res);

        return res;
    }

public:
    JulianDay(double d)
        : m_value(d)
    {}

    JulianDay(std::string sDate)
    {
        std::string trimmedDate;
        size_t i;
        for (i = 0; i < sDate.size(); i++)
        {
            if (!isspace(sDate[i]))
                trimmedDate.push_back(sDate[i]);
        }

        size_t firstDashPos = trimmedDate.find_first_of("-");
        size_t lastDashPos = trimmedDate.find_last_of("-");

        if (firstDashPos != 4 || lastDashPos != 7 || trimmedDate.size() != 10)
        {
            m_err = sDate + " is not a date";
            return;
        }

        std::string sY = trimmedDate.substr(0,4), 
                    sM = trimmedDate.substr(5,2), 
                    sD = trimmedDate.substr(8,2);

        double dY = atof(sY.c_str()),
               dM = atof(sM.c_str()),
               dD = atof(sD.c_str());

        if (dM == 1 || dM == 2)
        {
            dY = dY - 1;
            dM = dM + 12;
        }

        double A = integerPart(dY/100);
        double B = integerPart(A/4);
        double C = 2-A+B;
        double E = integerPart(365.25 * (dY+4716));
        double F = integerPart(30.6001 * (dM+1));
        m_value = C+dD+E+F-1524.5;
    }
    
    virtual ~JulianDay()
    {}

    operator double()
    {
        if (m_err.empty())
            return m_value;

        return -DBL_MAX;
    }

    operator std::string()
    {
        std::string res = "";

        if (m_err.empty())
        {
            double Q = floor(m_value)+0.5;
            double Z = integerPart(Q);
            double W = integerPart((Z - 1867216.25)/36524.25);
            double X = integerPart(W/4);
            double A = Z+1+W-X;
            double B = A+1524;
            double C = integerPart((B-122.1)/365.25);
            double D = integerPart(365.25 * C);
            double E = integerPart((B-D)/30.6001);
            double F = integerPart(30.6001 * E);
            double dD = B-D-F+(Q-Z);
            double dM = fmod(E-1, 12); // or E-13 (must get number less than or equal to 12)
            double dY = C-4716; // or C-4716 (otherwise)
            if (dM == 1.0 || dM == 2.0) //Month is January or February) 
                dY = C-4715;

            char buf[BUFSIZ];
            sprintf(buf, "%02d-%02d-%02d", (int)dY, (int)dM, (int)dD);
            res = buf;

            return res;
        }

        return std::string();
    }

    std::string getErr()
    {
        return m_err;
    }
};



#endif // have_JulianDay

