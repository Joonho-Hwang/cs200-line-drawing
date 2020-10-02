/*
 * Rudy Castan
 * Graphics Library
 * CS200
 * Fall 2020
 */
#include "draw_line.h"

#include "test_cases.hpp"

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>


using namespace CS200;

constexpr Color BLACK{0x000000FF};
constexpr Color BEAUTY_BUSH_PINK{0xf0bcd4FF};


template <typename ARRAY>
void print_image(const ARRAY& image)
{
    for (int row = HEIGHT-1; row >= 0; --row)
    {
        for (int column = 0; column < WIDTH; ++column)
        {
            if (image[row * WIDTH + column])
            {
                std::cout << '#';
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

int main(void)
{
    int  max_visuals_report = 10;
    long numCasesPassed     = 0;

    for (const auto& test_case : gTestCases)
    {
        std::array<bool, WIDTH * HEIGHT> image{};
        CS200::draw_line(test_case.x0, test_case.y0, test_case.x1, test_case.y1, BEAUTY_BUSH_PINK,
                         [&](int x, int y, Color) {
                             const bool column_is_good = (x >= 0 && x < WIDTH);
                             const bool row_is_good    = (y >= 0 && y < HEIGHT);

                             if (column_is_good && row_is_good)
                             {
                                 image[y * WIDTH + x] = true;
                             }
                             else
                             {
                                 std::cerr << "Failed Test Case - " << test_case.name << '\n';
                                 std::cerr << "BAD SETPIXEL VALUE: (" << x << ", " << y << ")\n";
                                 std::exit(-1);
                             }
                         });
        if (image != test_case.result)
        {
            if (max_visuals_report > 0)
            {
                std::cout << " Failed Test Case - " << test_case.name << '\n';

                std::cout << "---------------\n"
                          << "Expected\n"
                          << "---------------\n";
                print_image(test_case.result);

                std::cout << "---------------\n"
                          << "Student Produced\n"
                          << "---------------\n";
                print_image(image);
                --max_visuals_report;
            }
        }
        else
        {
            ++numCasesPassed;
        }
    }
    std::cout << " Test Cases passed " << numCasesPassed << "/" << gTestCases.size() << '\n';

    return 0;
}
