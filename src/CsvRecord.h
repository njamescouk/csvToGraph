// CsvRecord.h
#ifndef have_CsvRecord
#define have_CsvRecord

#pragma warning (disable: 4996)
#include <vector>
#include "CsvField.h"

class CsvRecord : public std::vector<CsvField>
{
public:

    bool isEmpty()
    {
        bool noFields = (size() == 0);
        bool oneEmptyField = (size() == 1 && at(0).size() == 0);

        return noFields || oneEmptyField;
    }

    bool contains(std::string name)
    {
        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (at(i) == name)
                return true;
        }

        return false;
    }

    CsvField getField(size_t i)
    {
        return at(i);
    }

    void applyColumnIndex(int colNdx)
    {
        if ((size_t)colNdx < size())
        {
            at(colNdx).setColumnIndex(colNdx);
        }
    }

    std::string toString()
    {
        std::string res = "";
        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (i != 0)
                res += ", ";

            res += at(i).toString();
        }

        return res;
    }

    std::string  writeHtmlRow(FILE *fp)
    {
        std::string res;

        size_t i;
        for (i = 0; i < size(); i++)
        {
            res += "<td><pre>";
            res += "%s", at(i);
            res += "</pre></td>\n";
        }

        return res;
    }

    std::string writePipeEnclosed()
    {
        std::string res = "|";

        size_t i;
        for (i = 0; i < size(); i++)
        {
            res += at(i);
            if (i < size() - 1)
                res += "|";
        }

        res += "|";

        return res;
    }

    size_t getNonEmptyFieldCount()
    {
        size_t res = 0;

        size_t i;
        for (i = 0; i < size(); i++)
        {
            if (!at(i).empty())
                res++;
        }

        return res;
    }
}
;

#endif
