/// @file medium.cpp
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
/// See @ref medium.h
///
#include "medium.h"

rmatrix<bool> generate_medium(int N, int M, float p, PRNG& rng)
{
    rmatrix<bool> empty_cells(N,M);
    for (int i = 0 ; i< N; i++)
        for (int j = 0 ; j< M; j++)
            if (rng.draw() < p)
                empty_cells[i][j] = true;
            else
                empty_cells[i][j] = false;
    return empty_cells;
}
