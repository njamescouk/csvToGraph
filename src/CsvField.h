// CsvField.h
#ifndef have_CsvField
#define have_CsvField

#include <string>
#include <cfloat>
#include <cstdlib>
#include "JulianDay.h"

#pragma warning (disable: 4996)

enum CSV_FIELD_TYPE
{
    CSV_FIELD_TYPE_BEGIN
    , CSV_FIELD_TYPE_NONE
    , CSV_FIELD_TYPE_TEXT
    , CSV_FIELD_TYPE_EMPTY_TEXT
    , CSV_FIELD_TYPE_INTEGRAL
    , CSV_FIELD_TYPE_REAL
    , CSV_FIELD_TYPE_ACTUAL_DOUBLE
    , CSV_FIELD_TYPE_DATE
    , CSV_FIELD_TYPE_ANY
    , CSV_FIELD_TYPE_END
};

enum PARSED_COLUMN_TYPE
{
    PARSED_COLUMN_TYPE_BEGIN
    , PARSED_COLUMN_TYPE_NONE
    , PARSED_COLUMN_TYPE_TEXT
    , PARSED_COLUMN_TYPE_EMPTY_TEXT
    , PARSED_COLUMN_TYPE_INTEGRAL
    , PARSED_COLUMN_TYPE_REAL
    , PARSED_COLUMN_TYPE_DATE
    , PARSED_COLUMN_TYPE_EMPTY
    , PARSED_COLUMN_TYPE_END
};

class CsvField : public std::string
{
    bool m_isQuoted;
    CSV_FIELD_TYPE m_type;
    int m_columnIndex;
    double m_double;

public:
    CsvField()
        : m_isQuoted(false)
        , m_type(CSV_FIELD_TYPE_NONE)
        , m_columnIndex(-1)
        , m_double(DBL_MIN)
    {
    }

    CsvField(double d)
        : m_isQuoted(false)
        , m_type(CSV_FIELD_TYPE_ACTUAL_DOUBLE)
        , m_columnIndex(-1)
        , m_double(d)
    {
    }

    CsvField(std::string s, bool isQuoted, CSV_FIELD_TYPE fieldType)
        : std::string(s)
        , m_type(fieldType)
        , m_isQuoted(isQuoted)
        , m_columnIndex(-1)
        , m_double(DBL_MIN)
    {
        if (m_type == CSV_FIELD_TYPE_DATE)
        {
            JulianDay jd(*this);
            if (jd.getErr().empty())
            {
                m_double = jd;
            }
        }
    }

    CsvField(std::string sDate, bool isQuoted)
        : std::string(sDate)
        , m_type(CSV_FIELD_TYPE_DATE)
        , m_isQuoted(isQuoted)
        , m_columnIndex(-1)
        , m_double(DBL_MIN)
    {
        m_double = JulianDay(sDate);
    }

    void setColumnIndex(int i)
    {
        m_columnIndex = i;
    }

    void setType(CSV_FIELD_TYPE ty)
    {
        m_type = ty;
    }

    CSV_FIELD_TYPE getType()
    {
        return m_type;
    }

    int getColumnIndex()
    {
        return m_columnIndex;
    }

    bool isQuoted()
    {
        return m_isQuoted;
    }

    bool isNumeric() const
    {
        if (m_type == CSV_FIELD_TYPE_INTEGRAL
            || m_type == CSV_FIELD_TYPE_REAL
            || m_type == CSV_FIELD_TYPE_ACTUAL_DOUBLE
            || m_type == CSV_FIELD_TYPE_DATE)
            return true;

        return false;
    }

    double getDouble() const
    {
        if (m_type == CSV_FIELD_TYPE_ACTUAL_DOUBLE || m_type == CSV_FIELD_TYPE_DATE)
        {
            return m_double;
        }
        else if (m_type == CSV_FIELD_TYPE_INTEGRAL
                 || m_type == CSV_FIELD_TYPE_REAL)
        {
            return atof(c_str());
        }

        return -DBL_MAX;
    }

    void write(FILE *fp)
    {
        if (m_isQuoted
            || m_type == CSV_FIELD_TYPE_TEXT
            || m_type == CSV_FIELD_TYPE_EMPTY_TEXT
            || m_type == CSV_FIELD_TYPE_DATE)
        {
            fprintf(fp, "\"%s\"", this->c_str());
        }
        else if (m_type == CSV_FIELD_TYPE_INTEGRAL)
        {
            fprintf(fp, "%d", atoi(c_str()));
        }
        else if (m_type == CSV_FIELD_TYPE_REAL
                 || m_type == CSV_FIELD_TYPE_ACTUAL_DOUBLE)
        {
            fprintf(fp, "%f", m_double);
        }
    }

    std::string toString()
    {
        std::string res = *this;
        
        if (res.empty())
            res = "\"\"";
        
        return res;
    }

    std::string toDebugString()
    {
        std::string res = *this;
        
        if (res.empty())
            res = "\"\"";
        
        res = res + " is ";
                
        if (m_type == CSV_FIELD_TYPE_INTEGRAL)
            res += "integral";
        else if (m_type == CSV_FIELD_TYPE_REAL)
            res += "real";
        else
            res += "text";

        return res;
    }
};


#endif // have_CsvField

