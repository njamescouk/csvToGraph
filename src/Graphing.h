// Graphing.h
#ifndef have_Graphing
#define have_Graphing

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include "CsvColumn.h"

class Graphing
{
    CsvColumn m_xColumn;
    std::vector<CsvColumn> m_YColumns;
    double m_minXVal;
    double m_maxXVal;
    double m_minYVal;
    double m_maxYVal;
    CsvColumn m_nullColumn;
    std::string m_err;

public:
    Graphing()
    {}

    Graphing(std::vector<CsvColumn> columns, int xNdx, int yNdx)
    {
        if (columns.size() == 0)
        {
            m_err = "no data";
            return;
        }

        if (xNdx == yNdx)
        {
            char buf[BUFSIZ];
            sprintf(buf, "xcol = %d and ycol = %d", xNdx+1, yNdx+1);
            m_err = buf;
            return;
        }

        if (xNdx >= (int)columns.size())
        {
            char buf[BUFSIZ];
            sprintf(buf, "xcol = %d but only %ld columns", xNdx+1, columns.size());
            m_err = buf;
            return;
        }

        if (yNdx >= (int)columns.size())
        {
            char buf[BUFSIZ];
            sprintf(buf, "ycol = %d but only %ld columns", yNdx+1, columns.size());
            m_err = buf;
            return;
        }

        m_xColumn = columns[xNdx];
        if (m_xColumn.getType() == PARSED_COLUMN_TYPE_TEXT)
        {
            m_minXVal = 0.0;
            m_maxXVal = (double)m_xColumn.size();
        }
        else
        {
            m_minXVal = columns[xNdx].getMin();
            m_maxXVal = columns[xNdx].getMax();
        }

        bool onlyOneYCol = (yNdx >= 0);
        m_minYVal = DBL_MAX;
        m_maxYVal = -DBL_MAX;

        size_t i;
        for (i = 0; i < columns.size(); i++)
        {
            if (i == xNdx || (onlyOneYCol && i != yNdx))
                continue;

            m_YColumns.push_back(columns[i]);
            double colMin = columns[i].getMin();
            double colMax = columns[i].getMax();

            if (colMax > m_maxYVal)
                m_maxYVal = colMax;

            if (colMin < m_minYVal)
                m_minYVal = colMin;
        }
    }

    virtual ~Graphing(){}

    std::string getErr()
    {
        return m_err;
    }

    size_t numYColumns()
    {
        return m_YColumns.size();
    }

    const CsvColumn & getXColumn()
    {
        return m_xColumn;
    }

    const CsvColumn & getYColumn(size_t i)
    {
        if (i < m_YColumns.size())
        {
            return m_YColumns[i];
        }

        return m_nullColumn;
    }

    double minX()
    {
        return m_minXVal;
    }

    double maxX()
    {
        return m_maxXVal;
    }

    double minY()
    {
        return m_minYVal;
    }

    double maxY()
    {
        return m_maxYVal;
    }

    std::string toString()
    {
        std::string res;

        return res;
    }
};



#endif // have_Graphing

