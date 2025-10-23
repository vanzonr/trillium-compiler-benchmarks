// initalive.cpp
//
// Implementation of routines defined in initalive.h
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#include "initalive.h"

//
// Fill cells such that the fraction of alive cells is roughly
// alive_fraction
//
rvector<bool> make_alive_status_by_fraction(int num_cells, double alive_fraction)
{
    rvector<bool> alive_status(num_cells);
    double fill = 0.0;
    for (bool& alive: alive_status) {
        fill += alive_fraction;
        if (fill >= 1.0) {
            alive = true;
            fill -= 1.0;
        } else {
            alive = false;
        }
    }
    return alive_status;
}
