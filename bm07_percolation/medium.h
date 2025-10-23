/// @file medium.h
///
/// Module to generate a matrix representing porous media.
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
#ifndef MEDIUMH
#define MEDIUMH

#include <rarray>
#include "prng.h"

///
/// @brief Generates an NxM lattice of empty (true) or filled (false)
/// cells representing a porous medium.
///
/// @param  N    width of the lattice
/// @param  M    height of the lattice
/// @param  p    probability to be empty
/// @param  rng  random number generator
///
/// @returns an NxM rmatrix of bools
///
rmatrix<bool> generate_medium(int N, int M, float p, PRNG& rng);

#endif
    
