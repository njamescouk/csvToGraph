// CsvColumn.h
#ifndef have_CsvColumn
#define have_CsvColumn

#pragma warning (disable: 4996)
#include <vector>
#include "CsvField.h"

class CsvColumn : public std::vector<CsvField>
{
    std::string m_name;
    bool m_hasDoubleVal;
    PARSED_COLUMN_TYPE m_type;

public:
    CsvColumn()
        : m_hasDoubleVal(false)
    {}

    CsvColumn(PARSED_COLUMN_TYPE ty)
        : m_hasDoubleVal(false)
        , m_type(ty)
    {}

    virtual ~CsvColumn(){}

    void setName(std::string s)
    {
        m_name = s;
    }

    PARSED_COLUMN_TYPE getType() const
    {
        return m_type;
    }

    void setHasDouble()
    {
        m_hasDoubleVal = true;
    }

    bool getHasDouble() const
    {
        return m_hasDoubleVal;
    }

    std::string getName() const
    {
        return m_name;
    }

    double getMin(bool ignoreNonNumeric = true)
    {
        double res = DBL_MAX;

        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (at(i).isNumeric() || !ignoreNonNumeric)
            {
                double d = at(i).getDouble();
                if (d < res)
                    res = d;
            }
        }

        return res;
    }

    double getMax(bool ignoreNonNumeric = true)
    {
        double res = -DBL_MAX;

        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (at(i).isNumeric() || !ignoreNonNumeric)
            {
                double d = at(i).getDouble();
                if (d > res)
                    res = d;
            }
        }

        return res;
    }
    /*
    // return index of firstDouble in &index
    bool findFirstDouble(size_t &index) const
    {
        bool res = false;
        index = (size_t)-1;

        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (at(i).isNumeric())
            {
                index = i;
                res = true;
                break;
            }
        }

        return res;
    }
    */
    /*
    // return index of double after &index in &index
    bool findNextNumeric(size_t &index) const
    {
        bool res = false;

        size_t i;
        for (i = index + 1; i < size(); i++)
        {
            if (at(i).isNumeric())
            {
                index = i;
                res = true;
                break;
            }
        }

        return res;
    }
*/
};



#endif // have_CsvColumn

