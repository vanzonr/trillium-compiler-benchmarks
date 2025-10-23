/// @file output.cpp
///
/// Part of the reference solution for assignment 5 of the PHY1610 Winter 2025 course.
///
/// See @ref output.h
///
#include "output.h"
#include <iostream>

void output(double t, double dx, const rvector<double>&a)
{
    std::cout << "\n";
    int i = 0;
    for (auto& x: a) 
        std::cout << t << " " << dx*i++ << " " << x << "\n";
}
