// Name       : Joonho Hwang
// Assignment : Line Rasterization
// Course     : CS200
// Term & Year: Fall 2020

#include "draw_line.h"

namespace CS200
{
    void draw_line_helper_high(const int x0, const int y0, const int x1, const int y1, const Color color, SetPixel setpixel)
    {
        const int dx = x1 - x0;
        const int dy = y1 - y0;

        const int incrementN = 2 * -dx;
        const int incrementNE = 2 * (dy - dx);

        setpixel(x0, y0, color);

        int d = dy - 2 * dx;
        for (int y = y0 + 1, x = x0; y <= y1; ++y)
        {
            if (d < 0)
            {
                d += incrementNE;
                ++x;
            }
            else
            {
                d += incrementN;
            }

            setpixel(x, y, color);
        }
    }
	
    void draw_line_helper_low(const int x0, const int y0, const int x1, const int y1, const Color color, SetPixel setpixel)
    {
        const int dx = x1 - x0;
        const int dy = y1 - y0;

        const int incrementE = 2 * dy;
        const int incrementNE = 2 * (dy - dx);

        setpixel(x0, y0, color);

        int d = 2 * dy - dx;
        for (int x = x0 + 1, y = y0; x <= x1; ++x)
        {
            if (d <= 0)
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

        const double slope = static_cast<double>(dy) / dx;

        // octant 0 & octant 4
        if (0 <= slope && slope <= 1)
        {
            if (dx > 0)
            {
                draw_line_helper_low(x0, y0, x1, y1, color, setpixel);
            }
            else
            {
                draw_line_helper_low(x1, y1, x0, y0, color, setpixel);
            }
        }
        // octant 1 & octant 5
        else if (slope > 1)
        {
        	if (dx > 0)
        	{
                draw_line_helper_high(x0, y0, x1, y1, color, setpixel);
        	}
            else
            {
                draw_line_helper_high(x1, y1, x0, y0, color, setpixel);
            }
        }
    }
}