// SvgWriter.h
#ifndef have_SvgWriter
#define have_SvgWriter

#include <string>
#include <algorithm>
#include "Graphing.h"
#include "GraphParameters.h"
#include "LineParameters.h"
#include "PointParameters.h"
#include "Bound.h"
#include "Pixel.h"
#include "UserToGraph.h"

const Pixel g_graphWidth(500);
const Pixel g_graphHeight(500);

const Pixel g_graphTopMargin(100);
const Pixel g_graphBottomMargin(150);
const Pixel g_graphLeftMargin(100);
const Pixel g_graphRightMargin(500);

const Pixel g_outputWidth(g_graphWidth 
                            + g_graphLeftMargin 
                            + g_graphRightMargin);
const Pixel g_outputHeight(g_graphHeight 
                            + g_graphTopMargin 
                            + g_graphBottomMargin);

const int g_dashSpace = 2;
const int g_pathSplit = 5; // for pretty printing
const std::string g_gridColour = "grey";
const std::string g_axisColour = "dimgrey";
const std::string g_dashDef = "stroke-dasharray=\"5, 5\"";

/*
    coordinates are stored as user values in doubles
    when writing svg we give user values which are 
    translated to svg coordinates.

    svg coordinates are scaled, reflected in y = 0
    and written. The whole shebang ends up with the 
    user origin at svg(0,0) so we have to translate 
    the graph (which may not contain the origin) into
    the svg drawing.
*/
class SvgWriter
{
    FILE *m_ofp;
    Bound m_xBounds;
    Bound m_yBounds;
    Graphing m_graph;
    GraphParameters m_params;
    UserToGraph m_userToGraph;
    std::string m_err;

    std::string makePointTitle(std::string colName, CsvField xVal, CsvField yVal)
    {
        char szTitle[BUFSIZ];

        if (xVal.getType() == CSV_FIELD_TYPE_DATE)
        {
            if (yVal.getType() == CSV_FIELD_TYPE_DATE)
            {
                sprintf (szTitle, 
                         "title=\"%s (%s, %s)\" ", 
                         colName.c_str(),
                         xVal.c_str(),
                         yVal.c_str());
            }
            else
            {
                sprintf (szTitle, 
                         "title=\"%s (%s, %f)\" ", 
                         colName.c_str(),
                         xVal.c_str(),
                         yVal.getDouble());
            }
        }
        else
        {
            if (yVal.getType() == CSV_FIELD_TYPE_DATE)
            {
                sprintf (szTitle, 
                         "title=\"%s (%f, %s)\" ", 
                         colName.c_str(),
                         xVal.getDouble(),
                         yVal.c_str());
            }
            else
            {
                if (xVal.getType() == CSV_FIELD_TYPE_TEXT)
                    sprintf (szTitle, 
                             "title=\"%s (%s, %f)\" ", 
                             colName.c_str(),
                             xVal.c_str(),
                             yVal.getDouble());
                else
                    sprintf (szTitle, 
                             "title=\"%s (%f, %f)\" ", 
                             colName.c_str(),
                             xVal.getDouble(),
                             yVal.getDouble());
            }
        }

        return szTitle;
    }

    Pixel xGridSpacing()
    {
        Pixel res = m_userToGraph.xGridSpacing();
        if (res >= g_graphWidth/3)
            res /= 2;

        return res;
    }

    double numXGridPoints()
    {
        Pixel span = m_userToGraph.xDistance(m_xBounds.span());
        Pixel spacing = xGridSpacing();
        return floor(span.m_value / spacing.m_value + .5);
    }

    Pixel yGridSpacing()
    {
        Pixel res = m_userToGraph.yGridSpacing();
        if (res >= g_graphHeight/3)
            res /= 2;

        return res;
    }

    double numYGridPoints()
    {
        Pixel span = m_userToGraph.yDistance(m_yBounds.span());
        Pixel spacing = yGridSpacing();
        return floor(span.m_value / spacing.m_value + .5);
    }

    void startSvg()
    {
        int xDisplacement = (int)(g_graphLeftMargin - m_userToGraph.xDistance(m_xBounds.lo())).m_value;
        int yDisplacement = (int)(g_graphTopMargin + g_graphHeight + m_userToGraph.yDistance(m_yBounds.lo())).m_value;
                 
        fprintf(m_ofp, 
                "<svg xmlns=\"http://www.w3.org/2000/svg\"\n"
                "xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
                "xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n");
        fprintf(m_ofp, " width=\"%.0f\"\n", g_outputWidth.m_value);
        fprintf(m_ofp, " height=\"%.0f\"\n", g_outputHeight.m_value);
        fprintf(m_ofp, ">\n");
        /*
        fprintf(fp, "<defs>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphCircle\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - circle</desc>\n");
        fprintf(fp, "    <circle cx=\"10\" cy=\"10\" r=\"10\"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphCross\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - cross</desc>\n");
        fprintf(fp, "    <path stroke=\"black\"\n");
        fprintf(fp, "    stroke-width=\"3\"\n");
        fprintf(fp, "    fill=\"black\"\n");
        fprintf(fp, "    class=\"pathWriter\"\n");
        fprintf(fp, "    d=\"m0 0 h-20 m10 0 m0 10 v-20 \"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphDiamond\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - diamond</desc>\n");
        fprintf(fp, "    <path stroke=\"black\"\n");
        fprintf(fp, "    stroke-width=\"1\"\n");
        fprintf(fp, "    fill=\"black\"\n");
        fprintf(fp, "    class=\"pathWriter\"\n");
        fprintf(fp, "    d=\"m0 0 m0 10 l10 -10 l10 10 l-10 10 l-10 -10 \"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphInvTriangle\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - inverted triangle</desc>\n");
        fprintf(fp, "    <path stroke=\"black\"\n");
        fprintf(fp, "    stroke-width=\"1\"\n");
        fprintf(fp, "    fill=\"black\"\n");
        fprintf(fp, "    class=\"pathWriter\"\n");
        fprintf(fp, "    d=\"m0 0 m0 17 m10 0 l10 -17 h-20 l10 17 \"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphSqare\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - square</desc>\n");
        fprintf(fp, "    <rect x=\"1\" y=\"1\" width=\"19\" height=\"19\"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "<symbol opacity=\"1.0\" fill=\"black\" id=\"cvsToGraphTriangle\" viewBox=\"0 0 20 20\">\n");
        fprintf(fp, "    <desc>cvsToGraph - triangle</desc>\n");
        fprintf(fp, "    <path stroke=\"black\"\n");
        fprintf(fp, "    stroke-width=\"1\"\n");
        fprintf(fp, "    fill=\"black\"\n");
        fprintf(fp, "    class=\"pathWriter\"\n");
        fprintf(fp, "    d=\"m0 0 m0 19 h20 l-10 -17 l-10 17 \"/>\n");
        fprintf(fp, "</symbol>\n");
        fprintf(fp, "</defs>\n");
        */
        fprintf(m_ofp, "<!--\n%s\n-->\n", toString().c_str());
        fprintf(m_ofp, 
                "<g transform=\"translate(%d,%d)\">\n", 
                xDisplacement, 
                yDisplacement); 
        
        /*
        fprintf(fp, 
                "<g>\n"); 
        */
    }

    void startLine(LineParameters params, std::string colName) const
    {
        fprintf(m_ofp, 
                "    <path stroke=\"%s\" stroke-width=\"%d\" fill=\"none\" title=\"%s\"\n    d=\"",
                COLOURS[params.m_colourNdx].c_str(),
                params.m_width,
                colName.c_str());
    }

    void startLine(std::string colour, int width, std::string colName) const
    {
        fprintf(m_ofp, 
                "    <path stroke=\"%s\" stroke-width=\"%d\" fill=\"none\" title=\"%s\"\n    d=\"",
                colour.c_str(),
                width,
                colName.c_str());
    }

    void endLine()
    {
        fprintf(m_ofp, "\"/>\n");
    }

    void grid()
    {
        fprintf(m_ofp, "<!-- graph paper -->\n");
        hGrid();
        vGrid();
    }

   /*
       draw horizontal grid lines from left to right
       starting at bottom and extending to top.
   */
    void hGrid()
    {
        Pixel gridSpacing = yGridSpacing();
        double numLines = numYGridPoints();

        Pixel lineLen = m_userToGraph.xDistance(m_xBounds.span());
        Pixel leftEdge = m_userToGraph.xDistance(m_xBounds.lo());
        Pixel loY = m_userToGraph.yDistance(m_yBounds.lo());

        fprintf(m_ofp, "<g>\n");    
        fprintf (m_ofp, 
                    "    <path title=\"HGrid\" stroke=\"%s\" %s \n    d=\"",
                    // g_dashSpace,
                    g_gridColour.c_str(),
                    g_dashDef.c_str());

        int pathCount = 0;
        double dYNdx;
        for (dYNdx = loY.m_value; pathCount <= numLines; dYNdx += gridSpacing.m_value)
        {
            if ((pathCount + 1) % g_pathSplit == 0)
                fprintf(m_ofp, "\n    ");
            fprintf(m_ofp, 
                    "M %.0f %.0f h %.0f ", 
                    leftEdge.m_value, 
                    -dYNdx,  // svg y goes south
                    lineLen.m_value); 
            pathCount++;
        }

        fprintf (m_ofp, "\"/>\n");
        fprintf(m_ofp, "</g>\n");    
    }

   /*
       draw vertical grid lines from bottom to top
       starting at left and extending to right.
   */
    void vGrid()
    {
        Pixel gridSpacing = xGridSpacing();
        double numLines = numXGridPoints();

        Pixel lineLen = m_userToGraph.yDistance(m_yBounds.span());
        Pixel bottomEdge = m_userToGraph.yDistance(m_yBounds.lo());
        Pixel loX = m_userToGraph.xDistance(m_xBounds.lo());

        fprintf(m_ofp, "<g>\n");    
        fprintf (m_ofp, 
                    "    <path title=\"VGrid\" stroke=\"%s\" %s \n    d=\"",
                    // g_dashSpace,
                    g_gridColour.c_str(),
                    g_dashDef.c_str());

        int pathCount = 0;
        double dXNdx;
        for (dXNdx = loX.m_value; pathCount <= numLines; dXNdx += gridSpacing.m_value)
        {
            if ((pathCount + 1) % g_pathSplit == 0)
                fprintf(m_ofp, "\n    ");
            fprintf(m_ofp, 
                    "M %.0f %.0f v %.0f ", 
                    dXNdx, 
                    -bottomEdge.m_value, 
                    -lineLen.m_value); 
            pathCount++;
        }

        fprintf (m_ofp, "\"/>\n");
        fprintf(m_ofp, "</g>\n");    
    }

    void axes()
    {
        fprintf(m_ofp, "<!-- axes -->\n");
        xAxis();
        yAxis();
    }

    void xAxis()
    {
        Pixel yPos = 0.0;
        Pixel yScaledLo = m_userToGraph.yDistance(m_yBounds.lo());
        Pixel yScaledHi = m_userToGraph.yDistance(m_yBounds.hi());
        Pixel xScaledLo = m_userToGraph.xDistance(m_xBounds.lo());
        Pixel xScaledHi = m_userToGraph.xDistance(m_xBounds.hi());

        if (m_yBounds.lo() > 0 || m_yBounds.hi() < 0) // if y bounds don't span 0
            yPos = yScaledLo; // put x axis at bottom

        // y = 0;
        fprintf(m_ofp, "<!-- x axis -->\n");
        fprintf(m_ofp, "<g>\n");    
        startLine(g_axisColour, 2, "x axis");
        setCp(xScaledLo.m_value, yPos.m_value);
        lineTo(xScaledHi.m_value, yPos.m_value);
        endLine();

        Pixel yNumPos = yPos - 20;
        Pixel gridSpacing = xGridSpacing();
        double numSpacing = gridSpacing.m_value / m_userToGraph.xSf();
        double numPoints = numXGridPoints() + 1;
        int numDP = 0;
        double logSpacing = log10(m_xBounds.magnitude());
        if (logSpacing <= 0)
            numDP = (int)(-logSpacing + 1);

        fprintf(m_ofp, "    <!-- x axis labels -->\n");
        bool xIsBig = (std::max(fabs(m_xBounds.lo()), fabs(m_xBounds.hi())) > 100000.0);
        PointParameters pp(0, 1, 1, 1);
        double tickNdx;
        Pixel xNumPos;
        for (tickNdx = 0; tickNdx < numPoints; tickNdx++)
        {
            xNumPos = xScaledLo + Pixel(tickNdx * gridSpacing.m_value);
            double xValue = m_xBounds.lo() + numSpacing * tickNdx;
            std::string text = (std::string)JulianDay(m_xBounds.lo() + numSpacing * tickNdx);
            if (m_graph.getXColumn().getType() == PARSED_COLUMN_TYPE_DATE)
            {
                fprintf(m_ofp, "    <!-- julianday %f -->\n", xValue);
                fprintf(m_ofp, 
                        "    <text transform=\"rotate(90, %f, %f)\" "
                        "text-anchor=\"start\" font-size=\"%dpx\" "
                        "x=\"%f\" y=\"%f\" fill=\"%s\">%s</text>\n", 
                        xNumPos.m_value,
                        -yNumPos.m_value,
                        16,
                        xNumPos.m_value, 
                        -yNumPos.m_value,
                        COLOURS[1].c_str(),
                        text.c_str());
            }
            else
            {
                if (m_params.m_xIsOrdinal)
                {
                    CsvColumn xCol = m_graph.getXColumn();
                    if ((int)xValue < (int)xCol.size())
                    {
                        fprintf(m_ofp, 
                                "    <text text-anchor=\"middle\" font-size=\"%dpx\" "
                                "x=\"%f\" y=\"%f\" fill=\"%s\">%s</text>\n", 
                                16,
                                xNumPos.m_value, 
                                -yNumPos.m_value,
                                COLOURS[1].c_str(),
                                m_graph.getXColumn()[(int)xValue].c_str());
                    }
                }
                else
                {
                    if (xIsBig)
                        fprintf(m_ofp, 
                                "    <text text-anchor=\"middle\" font-size=\"%dpx\" "
                                "x=\"%f\" y=\"%f\" fill=\"%s\">%.*e</text>\n", 
                                16,
                                xNumPos.m_value, 
                                -yNumPos.m_value,
                                COLOURS[1].c_str(),
                                numDP, 
                                xValue);
                    else
                        fprintf(m_ofp, 
                                "    <text text-anchor=\"middle\" font-size=\"%dpx\" "
                                "x=\"%f\" y=\"%f\" fill=\"%s\">%.*f</text>\n", 
                                16,
                                xNumPos.m_value, 
                                -yNumPos.m_value,
                                COLOURS[1].c_str(),
                                numDP, 
                                xValue);
                }
            }
        }

        text(m_graph.getXColumn().getName(), 
             xScaledHi.m_value + g_graphLeftMargin.m_value/2, 
             yNumPos.m_value,
             pp,
             24);

        fprintf(m_ofp, "</g>\n");    
    }

    void yAxis()
    {
        Pixel xPos = Pixel(0);
        Pixel yScaledLo = m_userToGraph.yDistance(m_yBounds.lo());
        Pixel yScaledHi = m_userToGraph.yDistance(m_yBounds.hi());
        Pixel xScaledLo = m_userToGraph.xDistance(m_xBounds.lo());
        Pixel xScaledHi = m_userToGraph.xDistance(m_xBounds.hi());

        if (m_xBounds.lo() > 0 || m_xBounds.hi() < 0) // 0 not in range
            xPos = xScaledLo; // put x axis at bottom

        fprintf(m_ofp, "<!-- y axis -->\n");
        fprintf(m_ofp, "<g>\n");    
        // x = 0;
        startLine(g_axisColour, 2, "y axis");
        setCp(xPos.m_value, yScaledLo.m_value);
        lineTo(xPos, yScaledHi);
        endLine();

        // write y labels on y axis near grid points
        Pixel numPos = xPos - 10;
        Pixel gridSpacing = yGridSpacing();
        double numSpacing = gridSpacing.m_value / m_userToGraph.ySf();
        double numPoints = numYGridPoints() + 1;
        int numDP = 0;
        double logSpacing = log10(m_yBounds.magnitude());
        if (logSpacing <= 0)
            numDP = (int)(-logSpacing + 1);

        fprintf(m_ofp, "    <!-- y axis labels -->\n");
        PointParameters pp(0, 1, 1, 1);
        double tickNdx;
        for (tickNdx = 0; tickNdx < numPoints; tickNdx++)
        {
            //char buf[BUFSIZ];
            //sprintf(buf, "%.*f", numDP, m_yBounds.lo() + numSpacing * tickNdx);
            //text(buf, numPos, m_yBounds.scaledLo() + tickNdx * gridSpacing - 6, pp);
            double yLabel = m_yBounds.lo() + (numSpacing * tickNdx);
            fprintf(m_ofp, 
                    "    <text text-anchor=\"end\" font-size=\"%dpx\" "
                    "x=\"%f\" y=\"%f\" fill=\"%s\">%.*f</text>\n", 
                    16,
                    numPos.m_value, 
                    -(m_userToGraph.yDistance(m_yBounds.lo()) 
                      + Pixel(tickNdx * gridSpacing.m_value) 
                      - Pixel(6)).m_value,
                    COLOURS[1].c_str(),
                    numDP, 
                    yLabel);
        }

        fprintf(m_ofp, "</g>\n");    
    }

    void lines()
    {
        fprintf(m_ofp, "<!-- lines -->\n");
        fprintf(m_ofp, "<g>\n");    
        const CsvColumn &xValues = m_graph.getXColumn();

        size_t yCount = 0;
        size_t yColNdx;
        for (yColNdx = 0; yColNdx < m_graph.numYColumns(); yColNdx++)
        {
            const CsvColumn &yValues = m_graph.getYColumn(yColNdx);
            if (xValues.size() != yValues.size())
            {
                if (m_params.m_verbose)
                {
                    char buf[BUFSIZ];
                    sprintf(buf, 
                            "found %ld x values and %ld y values for column \"%s\" of %s\n", 
                            xValues.size(), 
                            yValues.size(),
                            yValues.getName().c_str(),
                            m_params.m_src.c_str());
                    m_err += buf;
                }
                continue;
            }

            if (!yValues.getHasDouble())
            {
                if (m_params.m_verbose)
                {
                    char buf[BUFSIZ];
                    sprintf(buf, 
                            "no numbers found in column \"%s\" of %s\n", 
                            yValues.getName().c_str(),
                            m_params.m_src.c_str());
                    m_err += buf;
                }
                continue;
            }

            std::string colName = yValues.getName();
            fprintf(m_ofp, "    <!-- line for column %s -->\n", colName.c_str());
            LineParameters lp(yCount, 
                                yCount, 
                                m_params.m_nopt, 
                                m_userToGraph.xSf(), 
                                m_userToGraph.ySf());
            startLine(lp, colName);
            line (xValues, yValues, lp);
            endLine();

            yCount++;
        }
        fprintf(m_ofp, "</g>\n");    
    }

enum LineStates
{
    LINE_STATE_START,
    LINE_STATE_START_LINE,
    LINE_STATE_WRITING,
    LINE_STATE_DISCONTINUITY,
    LINE_STATE_DISCONTINUITY_NO_JOIN,
    LINE_STATE_END,
};

enum LineInputs
{
    LINE_INPUT_NO_COORDS,
    LINE_INPUT_INVALID_COORDS,
    LINE_INPUT_INVALID_COORDS_NO_JOIN,
    LINE_INPUT_VALID_COORDS,
};

    /*
        state,input,nextState
        start,invalidCoords,start
        start,invalidNoJoin,start
        start,noCoords,end
        start,validCoords,startLine
        startLine,invalidCoords,discontinuity
        startLine,invalidNoJoin,discNoJoin
        startLine,noCoords,end
        startLine,validCoords,writing
        discontinuity,invalidCoords,discontinuity
        discontinuity,noCoords,end
        discontinuity,validCoords,writing
        discNoJoin,invalidNoJoin,discNoJoin
        discNoJoin,noCoords,end
        discNoJoin,validCoords,writing
        writing,invalidCoords,discontinuity
        writing,invalidNoJoin,discNoJoin
        writing,noCoords,end
        writing,validCoords,writing
    */
    void line(const CsvColumn &xValues, const CsvColumn &yValues, LineParameters lp)
    {
        LineStates state = LINE_STATE_START;
        LineInputs curInput = LINE_INPUT_NO_COORDS;
        size_t rowNdx = 0;
        int coordCount = 0;
        CsvField xField;
        CsvField yField;

        while (state != LINE_STATE_END)
        {
            // get input row
            if (rowNdx < xValues.size() && rowNdx < yValues.size())
            {
                xField = xValues[rowNdx];
                yField = yValues[rowNdx];

                if (m_params.m_xIsOrdinal)
                    xField = CsvField(rowNdx);

                if (xField.isNumeric() && yField.isNumeric())
                {
                    curInput = LINE_INPUT_VALID_COORDS;
                }
                else
                {
                    if (m_params.m_nojoin)
                        curInput = LINE_INPUT_INVALID_COORDS_NO_JOIN;
                    else
                        curInput = LINE_INPUT_INVALID_COORDS;
                }
            }
            else
            {
                curInput = LINE_INPUT_NO_COORDS;
            }

            // find current state, do (action, transition)
            // for current input
            switch (state)
            {
            case LINE_STATE_START:
                if (curInput == LINE_INPUT_NO_COORDS)
                    state = LINE_STATE_END;
                else if (curInput == LINE_INPUT_INVALID_COORDS
                         || curInput == LINE_INPUT_INVALID_COORDS_NO_JOIN)
                    state = LINE_STATE_START;
                else if (curInput == LINE_INPUT_VALID_COORDS)
                {
                    if (rowNdx > 0 && m_params.m_verbose)
                    {
                        char buf[BUFSIZ];
                        sprintf(buf,
                        "starting at row %ld = (%f, %f) for column \"%s\"\n", 
                        rowNdx+1,
                        xField.getDouble(),
                        yField.getDouble(),
                        yValues.getName().c_str());
                        m_err += buf;
                    }
                    setCp(xField.getDouble() * lp.m_xSF, yField.getDouble() * lp.m_ySF);
                    coordCount++;
                    if (coordCount % 4 == 0)
                        fprintf(m_ofp, "\n    ");
                    state = LINE_STATE_START_LINE;
                }
                break;

            case LINE_STATE_START_LINE:
                if (curInput == LINE_INPUT_NO_COORDS)
                {
                    state = LINE_STATE_END;
                }
                else if (curInput == LINE_INPUT_INVALID_COORDS)
                {
                    state = LINE_STATE_DISCONTINUITY;
                }
                else if (curInput == LINE_INPUT_INVALID_COORDS_NO_JOIN)
                {
                    if (m_params.m_verbose)
                    {
                        char buf[BUFSIZ];
                        sprintf(buf,
                        "stopping at row %ld column \"%s\"\n", 
                        rowNdx+1,
                        yValues.getName().c_str());
                        m_err += buf;
                    }
                    state = LINE_STATE_DISCONTINUITY_NO_JOIN;
                }
                else if (curInput == LINE_INPUT_VALID_COORDS)
                {
                    lineTo(xField.getDouble() * lp.m_xSF, yField.getDouble() * lp.m_ySF);
                    coordCount++;
                    if (coordCount % 4 == 0)
                        fprintf(m_ofp, "\n    ");
                    state = LINE_STATE_WRITING;
                }
                break;

            case LINE_STATE_DISCONTINUITY:
                if (curInput == LINE_INPUT_NO_COORDS)
                    state = LINE_STATE_END;
                else if (curInput == LINE_INPUT_INVALID_COORDS)
                    state = LINE_STATE_DISCONTINUITY;
                else if (curInput == LINE_INPUT_VALID_COORDS)
                {
                    lineTo(xField.getDouble() * lp.m_xSF, yField.getDouble() * lp.m_ySF);
                    coordCount++;
                    if (coordCount % 4 == 0)
                        fprintf(m_ofp, "\n    ");
                    state = LINE_STATE_WRITING;
                }
                break;

            case LINE_STATE_DISCONTINUITY_NO_JOIN:
                if (curInput == LINE_INPUT_NO_COORDS)
                    state = LINE_STATE_END;
                else if (curInput == LINE_INPUT_INVALID_COORDS_NO_JOIN)
                    state = LINE_STATE_DISCONTINUITY_NO_JOIN;
                else if (curInput == LINE_INPUT_VALID_COORDS)
                {
                    if (m_params.m_verbose)
                    {
                        char buf[BUFSIZ];
                        sprintf(buf,
                        "starting at row %ld = (%f, %f) for column \"%s\"\n", 
                        rowNdx+1,
                        xField.getDouble(),
                        yField.getDouble(),
                        yValues.getName().c_str());
                        m_err += buf;
                    }
                    setCp(xField.getDouble() * lp.m_xSF, yField.getDouble() * lp.m_ySF);
                    coordCount++;
                    if (coordCount % 4 == 0)
                        fprintf(m_ofp, "\n    ");
                    state = LINE_STATE_WRITING;
                }
                break;

            case LINE_STATE_WRITING:
                if (curInput == LINE_INPUT_NO_COORDS)
                    state = LINE_STATE_END;
                else if (curInput == LINE_INPUT_INVALID_COORDS)
                {
                    state = LINE_STATE_DISCONTINUITY;
                }
                else if (curInput == LINE_INPUT_INVALID_COORDS_NO_JOIN)
                {
                    if (m_params.m_verbose)
                    {
                        char buf[BUFSIZ];
                        sprintf(buf,
                        "stopping at row %ld column \"%s\"\n", 
                        rowNdx+1,
                        yValues.getName().c_str());
                        m_err += buf;
                    }
                    state = LINE_STATE_DISCONTINUITY_NO_JOIN;
                }
                else if (curInput == LINE_INPUT_VALID_COORDS)
                {
                    coordCount++;
                    lineTo(xField.getDouble() * lp.m_xSF, yField.getDouble() * lp.m_ySF);
                    if (coordCount % 4 == 0)
                        fprintf(m_ofp, "\n    ");
                    state = LINE_STATE_WRITING;
                }
                break;

            case LINE_STATE_END:
                state = LINE_STATE_END;
                break;
            }

            rowNdx++; // next row
        }
    }

    void points ()
    {
        fprintf(m_ofp, "<!-- points -->\n");
        fprintf(m_ofp, "<g>\n");
        const CsvColumn &xValues = m_graph.getXColumn();
        size_t colNdx;
        for (colNdx = 0; colNdx < m_graph.numYColumns(); colNdx++)
        {
            const CsvColumn &yValues = m_graph.getYColumn(colNdx);
            if (xValues.size() != yValues.size())
            {
                char buf[BUFSIZ];
                sprintf(buf, 
                        "%ld x values and %ld y values", 
                        xValues.size(), 
                        yValues.size());
                m_err = buf;
            }

            std::string colName = yValues.getName();
            fprintf(m_ofp, "    <!-- points for column %s -->\n", colName.c_str());
            fprintf(m_ofp, "    <g>\n");    

            PointParameters curParams(colNdx, 
                                        colNdx, 
                                        m_userToGraph.xSf(), 
                                        m_userToGraph.ySf());
            size_t rowNdx;
            for (rowNdx = 0; rowNdx < xValues.size(); rowNdx++)
            {
                if (!yValues[rowNdx].isNumeric())
                    continue;

                CsvField curXVal = xValues[rowNdx];
                if (!xValues[rowNdx].isNumeric() && m_params.m_xIsOrdinal)
                    curXVal = CsvField((double)rowNdx);
                CsvField curYVal = yValues[rowNdx];

                std::string title = makePointTitle(colName, xValues[rowNdx], curYVal);
                point(title, curXVal.getDouble(), curYVal.getDouble(), curParams);
            }
            fprintf(m_ofp, "    </g>\n");    
        }
        fprintf(m_ofp, "</g>\n");    
    }

    void point(std::string title, double x, double y, PointParameters params)
    {
        y = -y; // in svg land
        std::string colour = COLOURS[params.m_colourNdx];

        switch(params.m_pointNdx)
        {
        case POINT_SYMBOL_CIRCLE:
        {
            fprintf(m_ofp, 
                    "    <circle %s cx=\"%f\" cy=\"%f\" r=\"5\" fill=\"%s\"/>\n",
                    title.c_str(),
                    x * params.m_xSF,
                    y * params.m_ySF,
                    colour.c_str());
            break;
        }
        case POINT_SYMBOL_SQUARE:
        {
            fprintf(m_ofp, 
                    "    <rect %s x=\"%f\" y=\"%f\" width=\"9\" height=\"9\" fill=\"%s\"/>\n", 
                    title.c_str(),
                    x * params.m_xSF - 9/2, 
                    y * params.m_ySF - 9/2, 
                    colour.c_str());
            break;
        }
        case POINT_SYMBOL_TRIANGLE:
        {
            fprintf(m_ofp, "    <path %s fill=\"%s\" ", title.c_str(), colour.c_str());
            fprintf(m_ofp, "d=\"M%f %f m0 9 h10 l-5 -9 l-5 9 \"/>\n", x * params.m_xSF-5, y * params.m_ySF-5);
            break;
        }
        case POINT_SYMBOL_DIAMOND:
        {
            fprintf(m_ofp, "    <path %s fill=\"%s\" ", title.c_str(), colour.c_str());
            fprintf(m_ofp, "d=\"M%f %f m0 5 l5 -5 l5 5 l-5 5 l-5 -5 \"/>\n", x * params.m_xSF-5, y * params.m_ySF-5);
            break;
        }
        case POINT_SYMBOL_INVERTED_TRIANGLE:
        {
            fprintf(m_ofp, "    <path %s fill=\"%s\" ", title.c_str(), colour.c_str());
            fprintf(m_ofp, "d=\"M%f %f m0 9 m5 0 l5 -9 h-10 l5 9 \"/>\n", x * params.m_xSF-5, y * params.m_ySF-4);
            break;
        }
        case POINT_SYMBOL_CROSS:
        {
            fprintf(m_ofp, "    <path %s stroke=\"%s\" ", title.c_str(), colour.c_str());
            fprintf(m_ofp, "stroke-width=\"3\" ");
            fprintf(m_ofp, "d=\"M%f %f h-10 m5 0 m0 5 v-10 \"/>\n", x * params.m_xSF+4, y * params.m_ySF-0); // +ve y is down
            break;
        }
        }
    }

    void key()
    {
        Pixel keySep = g_graphTopMargin/4.0;
        int maxKeys = (int)(g_graphHeight / keySep).m_value;

        fprintf(m_ofp, "<!-- key -->\n<g>\n");

        Pixel xPos = m_userToGraph.xDistance(m_xBounds.hi()) + (g_graphRightMargin / 2);

        Pixel yPos(0.0);
        double dYPos = m_yBounds.hi();
        if (maxKeys > (int)m_graph.numYColumns())
        {
            // centre key on cl of graph
            // compute cl of graph as user double
            double halfYSpan = m_yBounds.span()/2.0;
            dYPos -= halfYSpan;
            // total height of keys in px
            Pixel keyHeight = m_graph.numYColumns() * keySep.m_value;
            // ... as user double
            double dKeyHeight = keyHeight.m_value / m_userToGraph.ySf();
            dYPos += dKeyHeight/2.0;
        }

        yPos = m_userToGraph.yDistance(dYPos);

        size_t colNdx;
        for (colNdx = 0; colNdx < m_graph.numYColumns(); colNdx++)
        {
            const CsvColumn &yValues = m_graph.getYColumn(colNdx);

            if (!yValues.getHasDouble())
                continue;

            std::string colName = yValues.getName();
            PointParameters curParams(colNdx, colNdx, 1, 1);

            text(colName, xPos + 40, yPos - 5, curParams);

            if (!m_params.m_nopt)
                point("", xPos.m_value, yPos.m_value, curParams);

            if (!m_params.m_nolin)
            {
                LineParameters lp(colNdx, 0, true, 1, 1);
                startLine(lp, "");
                setCp(xPos - 20, yPos);
                lineTo(xPos + 20, yPos);
                endLine();
            }

            yPos -= g_graphTopMargin/4;
        }
        fprintf(m_ofp, "</g>\n");
    }

    void text(std::string s, Pixel x, Pixel y, PointParameters params, int px = 16)
    {
        y = -y.m_value; // in svg land
        std::string colour = COLOURS[params.m_colourNdx];

        fprintf(m_ofp, 
                "    <text font-size=\"%dpx\" x=\"%f\" y=\"%f\" fill=\"%s\">%s</text>\n", 
                px,
                x.m_value * params.m_xSF , 
                y.m_value * params.m_ySF , 
                colour.c_str(),
                s.c_str());
    }

    void endSvg()
    {
        fprintf(m_ofp, "</g>\n");
        fprintf(m_ofp, "</svg>\n");
    }

    void lineTo(Pixel x, Pixel y)
    {
        fprintf(m_ofp, "L%f %f ", x.m_value, -1*y.m_value);
    }

    void setCp(Pixel x, Pixel y)
    {
        fprintf(m_ofp, "M%f %f ", x.m_value, -1*y.m_value);
    }

public:
    SvgWriter(FILE *ofp, Graphing g, GraphParameters params)
        : m_ofp(ofp)
        , m_graph(g)
        , m_params(params)
    {
        if (g.getXColumn().getType() == PARSED_COLUMN_TYPE_TEXT)
            m_params.m_xIsOrdinal = true;

        double minX = g.minX();
        if (minX == DBL_MAX)
        {
            m_err = "cannot compute minimum for x values";
            return;
        }

        double maxX = g.maxX();
        if (maxX == -DBL_MAX)
        {
            m_err = "cannot compute maximum for x values";
            return;
        }

        double minY = g.minY();
        if (minY == DBL_MAX)
        {
            m_err = "cannot compute minimum for y values";
            return;
        }

        double maxY = g.maxY();
        if (maxY == -DBL_MAX)
        {
            m_err = "cannot compute maximum for y values";
            return;
        }

        if (m_params.m_showY0)
        {
            if (g.maxY() < 0.0)
                maxY = 0.0;
            if (g.minY() > 0.0)
                minY = 0.0;
        }

        if (m_params.m_showX0)
        {
            if (g.maxX() < 0.0)
                maxX = 0.0;
            if (g.minX() > 0.0)
                minX = 0.0;
        }

        m_xBounds = Bound(minX, maxX);
        m_err += m_xBounds.err();
        m_yBounds = Bound(minY, maxY);
        m_err += m_yBounds.err();

        m_userToGraph = UserToGraph(g_graphWidth, g_graphHeight, m_xBounds, m_yBounds);
    }

    virtual ~SvgWriter(){}

    void write()
    {
        if (m_graph.numYColumns() < 1)
        {
            m_err += "\nneed 2 or more columns to write graph";
            return;
        }

        std::string xColName = m_graph.getXColumn().getName();
        if (m_graph.getXColumn().size() < 1)
        {
            m_err += "\nno x values in column \"" + xColName + "\"";
            return;
        }

        startSvg();

        if (!m_params.m_nopap)
            grid();

        if (!m_params.m_noax)
            axes();

        if (!m_params.m_nolin)
            lines();

        if (!m_params.m_nopt)
            points();

        if (!m_params.m_nokey)
            key();

        endSvg();
    }

    std::string toString()
    {
        std::string res = m_params.toString() + "\n";
        res += "x bounds:\n" + m_xBounds.toString() + "\n";
        res += "y bounds:\n" + m_yBounds.toString() + "\n";
        res += "userToGraph:\n" + m_userToGraph.toString();

        return res;
    }

    std::string getErr()
    {
        return m_err;
    }
};



#endif // have_SvgWriter

