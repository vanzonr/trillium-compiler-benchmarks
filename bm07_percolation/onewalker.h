/// @file onewalker.h
///
/// Module to simulate a single random walker through a porous medium.
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
#ifndef ONEWALKERH
#define ONEWALKERH

#include <rarray>
#include "parameters.h"
#include "prng.h"

///
/// Structure to hold a position in the
///
struct Point {
    int i; // vertical position
    int j; // horizontal position
};

///
/// @brief Tries to have one walker run through the emptiness lattice
///        for S*(N*N+M*M) steps or until it reaches the bottom.
///
/// @param  p
/// @param  empty_cells
/// @param  initial
/// @param  rng
///
/// @returns the final position of the walker
///
Point one_walker(const Parameters& p,
                 const rmatrix<bool>& empty_cells,
                 const Point& initial,
                 PRNG& rng);
#endif
