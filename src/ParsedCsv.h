// ParsedCsv.h
#ifndef have_ParsedCsv
#define have_ParsedCsv

#include <vector>
#include <map>
#include <cstdio>
#include "CsvField.h"
#include "CsvRecord.h"
#include "CsvColumn.h"

#pragma warning (disable: 4996)


class State
{
    PARSED_COLUMN_TYPE m_colType;

public:
    State()
        : m_colType(PARSED_COLUMN_TYPE_END)
    {}

    State(PARSED_COLUMN_TYPE s)
        : m_colType(s)
    {}

    virtual ~State(){}

    PARSED_COLUMN_TYPE getColumnType()
    {
        return m_colType;
    }

    int getInt() const
    {
        return (int)m_colType;
    }

    State &operator=(int rhs)
    {
        if (rhs >= PARSED_COLUMN_TYPE_BEGIN && rhs <= PARSED_COLUMN_TYPE_END)
            m_colType = (PARSED_COLUMN_TYPE)rhs;
        else
            m_colType = PARSED_COLUMN_TYPE_END;

        return *this;
    }
    
    bool operator==(State rhs) const
    {
        return m_colType == rhs.m_colType;
    }

    bool operator!=(State rhs)
    {
        return m_colType != rhs.m_colType;
    }

    State operator ++()
    {
        if (m_colType < PARSED_COLUMN_TYPE_END)
            m_colType = (PARSED_COLUMN_TYPE) (m_colType + 1);
        else
            m_colType = PARSED_COLUMN_TYPE_END;

        return *this;
    }

    bool operator< (State rhs) const
    {
        return (int)m_colType < (int)rhs.m_colType;
    }
};

class Input
{
    CSV_FIELD_TYPE m_fieldType;

public:
    Input()
        : m_fieldType(CSV_FIELD_TYPE_END)
    {}

    Input(CSV_FIELD_TYPE i)
        : m_fieldType(i)
    {}

    virtual ~Input(){}

    int getInt() const
    {
        return (int)m_fieldType;
    }

    Input &operator=(int rhs)
    {
        if (rhs >= CSV_FIELD_TYPE_BEGIN && rhs <= CSV_FIELD_TYPE_END)
            m_fieldType = (CSV_FIELD_TYPE)rhs;
        else
            m_fieldType = CSV_FIELD_TYPE_END;

        return *this;
    }

    bool operator==(Input rhs) const
    {
        return m_fieldType == rhs.m_fieldType;
    }

    bool operator!=(Input rhs)
    {
        return m_fieldType != rhs.m_fieldType;
    }

    Input operator ++()
    {
        if (m_fieldType < CSV_FIELD_TYPE_END)
            m_fieldType = (CSV_FIELD_TYPE) (m_fieldType + 1);
        else
            m_fieldType = CSV_FIELD_TYPE_END;

        return *this;
    }

    bool operator< (Input rhs) const
    {
        return (int)m_fieldType < (int)rhs.m_fieldType;
    }
};

class StateInput
{
    State m_state;
    Input m_input;

public:
    StateInput(State state, Input input)
        : m_state(state)
        , m_input(input)
    {}

    virtual ~StateInput(){}

    bool operator< (StateInput rhs) const
    {
        if (m_state < rhs.m_state)
            return true;
        else if (m_state == rhs.m_state)
            return m_input < rhs.m_input;

        return false;
    }

};

class Machine : public std::map<StateInput, State> // (state, input) -> nextState 
{
};

class ParsedCsv
{
    std::vector<CsvRecord> m_records;
    std::map<int, PARSED_COLUMN_TYPE> m_columnTypes; // m_columnTypes[column index] -> column type
    bool m_haveColumnTypes;
    bool m_emptyIsReallyEmpty;

    bool isColEmptyish(size_t col)
    {
        return (m_columnTypes[(int)col] == PARSED_COLUMN_TYPE_EMPTY)
               || (m_columnTypes[(int)col] == PARSED_COLUMN_TYPE_EMPTY_TEXT);
    }

    bool isColReallyEmpty(size_t col)
    {
        return m_columnTypes[col] == PARSED_COLUMN_TYPE_EMPTY;
    }

    /*

                          \   field: type FIELD_TYPE_NONE    FIELD_TYPE_EMPTY_TEXT  FIELD_TYPE_TEXT   FIELD_TYPE_INTEGRAL   FIELD_TYPE_REAL   FIELD_TYPE_DATE     FIELD_TYPE_ANY
    current column type    \
    --------------------   |         ----------------------  ----------------------  ----------------  --------------------  ----------------  -----------------  ----------------------
    COLUMN_TYPE_NONE       |         COLUMN_TYPE_NONE        COLUMN_TYPE_EMPTY_TEXT  COLUMN_TYPE_TEXT  COLUMN_TYPE_INTEGRAL  COLUMN_TYPE_REAL  COLUMN_TYPE_DATE   COLUMN_TYPE_EMPTY
    COLUMN_TYPE_TEXT       |         COLUMN_TYPE_TEXT        COLUMN_TYPE_TEXT        COLUMN_TYPE_TEXT  COLUMN_TYPE_TEXT      COLUMN_TYPE_TEXT  COLUMN_TYPE_TEXT   COLUMN_TYPE_TEXT
    COLUMN_TYPE_EMPTY_TEXT |         COLUMN_TYPE_EMPTY_TEXT  COLUMN_TYPE_EMPTY_TEXT  COLUMN_TYPE_TEXT  COLUMN_TYPE_INTEGRAL  COLUMN_TYPE_REAL  COLUMN_TYPE_DATE   COLUMN_TYPE_EMPTY_TEXT
    COLUMN_TYPE_INTEGRAL   |         COLUMN_TYPE_INTEGRAL    COLUMN_TYPE_INTEGRAL    COLUMN_TYPE_TEXT  COLUMN_TYPE_INTEGRAL  COLUMN_TYPE_REAL  COLUMN_TYPE_TEXT   COLUMN_TYPE_INTEGRAL
    COLUMN_TYPE_REAL       |         COLUMN_TYPE_REAL        COLUMN_TYPE_REAL        COLUMN_TYPE_TEXT  COLUMN_TYPE_REAL      COLUMN_TYPE_REAL  COLUMN_TYPE_TEXT   COLUMN_TYPE_REAL
    COLUMN_TYPE_DATE       |         COLUMN_TYPE_DATE        COLUMN_TYPE_DATE        COLUMN_TYPE_TEXT  COLUMN_TYPE_TEXT      COLUMN_TYPE_TEXT  COLUMN_TYPE_DATE   COLUMN_TYPE_DATE
    COLUMN_TYPE_EMPTY      |         COLUMN_TYPE_EMPTY       COLUMN_TYPE_EMPTY_TEXT  COLUMN_TYPE_TEXT  COLUMN_TYPE_INTEGRAL  COLUMN_TYPE_REAL  COLUMN_TYPE_DATE   COLUMN_TYPE_EMPTY
    */
    
    Machine makeMachine()
    {
        Machine res;

        // everything to identity
        State stateNdx;
        for (stateNdx = PARSED_COLUMN_TYPE_BEGIN + 1; stateNdx != State(PARSED_COLUMN_TYPE_END); ++stateNdx)
        {
            Input inputNdx;
            for (inputNdx = CSV_FIELD_TYPE_BEGIN + 1; inputNdx != Input(CSV_FIELD_TYPE_END); ++inputNdx)
            {
                StateInput si(stateNdx, inputNdx);
                res[si] = stateNdx;
            }
        }

        // now do special cases
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_EMPTY_TEXT)] = PARSED_COLUMN_TYPE_EMPTY_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_INTEGRAL)] = PARSED_COLUMN_TYPE_INTEGRAL;
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_REAL)] = PARSED_COLUMN_TYPE_REAL;
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_DATE)] = PARSED_COLUMN_TYPE_DATE;
        res[StateInput(PARSED_COLUMN_TYPE_NONE, CSV_FIELD_TYPE_ANY)] = PARSED_COLUMN_TYPE_EMPTY;

        res[StateInput(PARSED_COLUMN_TYPE_EMPTY_TEXT, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY_TEXT, CSV_FIELD_TYPE_INTEGRAL)] = PARSED_COLUMN_TYPE_INTEGRAL;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY_TEXT, CSV_FIELD_TYPE_REAL)] = PARSED_COLUMN_TYPE_REAL;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY_TEXT, CSV_FIELD_TYPE_DATE)] = PARSED_COLUMN_TYPE_DATE;

        res[StateInput(PARSED_COLUMN_TYPE_INTEGRAL, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_INTEGRAL, CSV_FIELD_TYPE_REAL)] = PARSED_COLUMN_TYPE_REAL;
        res[StateInput(PARSED_COLUMN_TYPE_INTEGRAL, CSV_FIELD_TYPE_DATE)] = PARSED_COLUMN_TYPE_TEXT;

        res[StateInput(PARSED_COLUMN_TYPE_REAL, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_REAL, CSV_FIELD_TYPE_DATE)] = PARSED_COLUMN_TYPE_TEXT;

        res[StateInput(PARSED_COLUMN_TYPE_DATE, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_DATE, CSV_FIELD_TYPE_INTEGRAL)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_DATE, CSV_FIELD_TYPE_REAL)] = PARSED_COLUMN_TYPE_TEXT;

        res[StateInput(PARSED_COLUMN_TYPE_EMPTY, CSV_FIELD_TYPE_EMPTY_TEXT)] = PARSED_COLUMN_TYPE_EMPTY_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY, CSV_FIELD_TYPE_TEXT)] = PARSED_COLUMN_TYPE_TEXT;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY, CSV_FIELD_TYPE_INTEGRAL)] = PARSED_COLUMN_TYPE_INTEGRAL;
        res[StateInput(PARSED_COLUMN_TYPE_EMPTY, CSV_FIELD_TYPE_REAL)] = PARSED_COLUMN_TYPE_REAL;

        return res;
    }

public:
    ParsedCsv() 
        : m_haveColumnTypes(false)
        , m_emptyIsReallyEmpty(true)
    {}

    virtual ~ParsedCsv(){}

    size_t numRecords()
    {
        return m_records.size();
    }

    CsvRecord getRecord(size_t i)
    {
        if (i < m_records.size() && !m_records.empty())
            return m_records[i];

        return CsvRecord();
    }

    /*
    const std::map<int, PARSED_COLUMN_TYPE> getColumnTypes()
    {
        if (m_haveColumnTypes)
            return m_columnTypes;

        return std::map<int, PARSED_COLUMN_TYPE>();
    }
    */

    const std::map<int, PARSED_COLUMN_TYPE> getColumnTypes()
    {
        if (m_haveColumnTypes)
            return m_columnTypes;

        return std::map<int, PARSED_COLUMN_TYPE>();
    }

    PARSED_COLUMN_TYPE getColumnType(size_t i)
    {
        if (m_columnTypes.count(i) > 0)
        {
            return m_columnTypes[i];
        }

        return PARSED_COLUMN_TYPE_NONE;
    }

    bool isRectangular()
    {
        if (m_records.size() == 0 || m_records.size() == 1)
            return true;

        size_t numCols = m_records[0].size();
    
        size_t i;
        for (i = 1; i < m_records.size(); i++)
        {
            if (m_records[i].size() != numCols)
                return false;
        }

        return true;
    }

    size_t maxFields()
    {
        if (m_records.size() == 0)
            return 0;

        size_t res = m_records[0].size();
    
        size_t i;
        for (i = 1; i < m_records.size(); i++)
        {
            size_t fieldsI = m_records[i].size();
            if (fieldsI > res)
                res = fieldsI;
        }

        return res;
    }

    size_t minFields()
    {
        if (m_records.size() == 0)
            return 0;

        size_t res = m_records[0].size();
    
        size_t i;
        for (i = 1; i < m_records.size(); i++)
        {
            size_t fieldsI = m_records[i].size();
            if (fieldsI < res)
                res = fieldsI;
        }

        return res;
    }

    void applyColumnTypes(bool firstLineIsHeading)
    {
        applyColumnNumbers();

        Machine m = makeMachine();

        size_t colNdx;
        size_t biggestRecord = maxFields();
        for (colNdx = 0; colNdx < biggestRecord; colNdx++)
        {
            PARSED_COLUMN_TYPE colType = computeColumnType(colNdx, firstLineIsHeading, m); // no point making m every time
            m_columnTypes[colNdx] = colType;
        }

        m_haveColumnTypes = true;
    }

    void applyColumnNumbers()
    {
        size_t colNdx;
        size_t biggestRecord = maxFields();
        for (colNdx = 0; colNdx < biggestRecord; colNdx++)
        {
            size_t recordNdx;
            for (recordNdx = 0; recordNdx < numRecords(); recordNdx++)
            {
                CsvRecord &cur = m_records[recordNdx];
                cur.applyColumnIndex(colNdx);
            }
        }
    }

    PARSED_COLUMN_TYPE computeColumnType(size_t colNdx, bool firstLineIsHeading, Machine m)
    {
        PARSED_COLUMN_TYPE res = PARSED_COLUMN_TYPE_NONE;

        // go down column colNdx changing res according to 
        // (res, curFieldType)
        // bail out if we get to PARSED_COLUMN_TYPE_TEXT
        // otherwise res is whatever survives at the end of the column

        size_t recordNdx = 0;
        if (firstLineIsHeading)
            recordNdx = 1;
        for (; recordNdx < numRecords(); recordNdx++)
        {
            CsvRecord cur = m_records[recordNdx];
            if (colNdx < cur.size())
            {
                CSV_FIELD_TYPE curFieldType = cur[colNdx].getType();
                res = m[StateInput(res, curFieldType)].getColumnType();
                if (res == PARSED_COLUMN_TYPE_TEXT)
                    break;
            }
        }

        return res;
    }

    void writeHtml(FILE *fp)
    {
        fprintf(fp, "<html>");
        fprintf(fp, "<head>");
        fprintf(fp, "</head>");
        fprintf(fp, "<body>");

        fprintf(fp, "<table border=\"1\">\n");
        size_t i;
        for (i = 0; i < m_records.size(); i++)
        {
            fprintf(fp, "<tr>\n");
            m_records[i].writeHtmlRow(fp);
            fprintf(fp, "</tr>\n");
        }
        fprintf(fp, "</table>\n");

        fprintf(fp, "</body>");
        fprintf(fp, "</html>");
    }

    void writePipeEnclosed(FILE *fp)
    {
        size_t i;
        for (i = 0; i < m_records.size(); i++)
        {
            fprintf(fp, "%s", m_records[i].writePipeEnclosed().c_str());
        }
    }

    std::string toString()
    {
        std::string res;

        size_t i;
        for (i = 0; i < m_records.size(); i++)
        {
            res += m_records[i].toString() + "\n";
        }

        return res;
    }

    void push_back(CsvRecord r)
    {
        m_records.push_back(r);
    }

    bool isColIntegral(size_t col)
    {
        return m_columnTypes[(int)col] == PARSED_COLUMN_TYPE_INTEGRAL;
    }

    bool isColReal(size_t col)
    {
        return m_columnTypes[(int)col] == PARSED_COLUMN_TYPE_REAL;
    }

    bool isColEmpty(size_t col)
    {
        if (m_emptyIsReallyEmpty)
            return isColReallyEmpty(col);

        return isColEmptyish(col);
    }

    size_t numEmptyCols()
    {
        size_t res = 0;
        size_t i;
        for (i = 0; i < numRecords(); i++)
        {
            if (isColEmpty(i))
                res++;
        }

        return res;
    }
};





#endif // have_ParsedCsv

