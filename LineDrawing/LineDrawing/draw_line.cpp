// Name       : Joonho Hwang
// Assignment : Line Rasterization
// Course     : CS200
// Term & Year: Fall 2020

#include "draw_line.h"

namespace CS200
{
    void draw_line_helper_high(const int x0, const int y0, const int x1, const int y1, const Color color, SetPixel setpixel, const bool mirrorX = false)
    {
        const int xSign = mirrorX ? -1 : 1;

        const int dx = x1 - x0;
        const int dy = y1 - y0;

        const int incrementN = 2 * -dx;
        const int incrementNE = 2 * (xSign * dy - dx);

        setpixel(x0, y0, color);

        int d = xSign * dy - 2 * dx;
        for (int y = y0 + 1, x = x0; y <= y1; ++y)
        {
            if (xSign * d < 0)
            {
                d += incrementNE;
                x += xSign;
            }
            else
            {
                d += incrementN;
            }

            setpixel(x, y, color);
        }
    }
	
    void draw_line_helper_low(const int x0, const int y0, const int x1, const int y1, const Color color, SetPixel setpixel, const bool mirrorX = false)
    {
        const int xSign = mirrorX ? -1 : 1;
    	
        const int dx = x1 - x0;
        const int dy = y1 - y0;

        const int incrementE = 2 * dy * xSign;
        const int incrementNE = 2 * (xSign * dy - dx);

        setpixel(x0, y0, color);

        int d = xSign * 2 * dy - dx;
        for (int x = x0 + xSign, y = y0; (mirrorX ? x >= x1 : x <= x1); x += xSign)
        {
            if (xSign * d < 0 || (!mirrorX && d == 0))
            {
                d += incrementE;
            }
            else
            {
                d += incrementNE;
                ++y;
            }

            setpixel(x, y, color);
        }
    }
	
    void draw_line(const int x0, const int y0, const int x1, const int y1, const Color color, SetPixel setpixel)
    {
        const int dx = x1 - x0;
        const int dy = y1 - y0;

    	// point
        if (dx == 0 && dy == 0)
        {
            setpixel(x0, y0, color);
            return;
        }
    	
        const double slope = static_cast<double>(dy) / dx;

        // octant 0 & 4
        if (0 <= slope && slope <= 1)
        {
        	// octant 0 & horizontal
            if (dx > 0)
            {
                draw_line_helper_low(x0, y0, x1, y1, color, setpixel);
            }
        	// octant 4
            else
            {
                draw_line_helper_low(x1, y1, x0, y0, color, setpixel);
            }
        }
        // octant 1 & 5
        else if (slope > 1)
        {
        	// octant 1 & vertical
        	if (dx >= 0)
        	{
                draw_line_helper_high(x0, y0, x1, y1, color, setpixel);
        	}
        	// octant 5
            else
            {
                draw_line_helper_high(x1, y1, x0, y0, color, setpixel);
            }
        }
    	// octant 2 & 6
        else if (slope < -1)
        {
        	// octant 2
            if (dx < 0)
            {
                draw_line_helper_high(x0, y0, x1, y1, color, setpixel, true);
            }
        	// octant 6
            else
            {
                draw_line_helper_high(x1, y1, x0, y0, color, setpixel, true);
            }
        }
    	// octant 3 & 7
        else if (-1 <= slope && slope < 0)
        {
        	// octant 3
	        if (dx < 0)
	        {
                draw_line_helper_low(x0, y0, x1, y1, color, setpixel, true);
	        }
        	// octant 7
            else
            {
                draw_line_helper_low(x1, y1, x0, y0, color, setpixel, true);
            }
        }
    }
}