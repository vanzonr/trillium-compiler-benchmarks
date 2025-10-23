/// @file parameters.h
///
/// Header to define the struct to hold parameters for the percolation
/// simulations
///
///   M: width of the percolation domain
///   N: height of the percolation domain
///   p: probablity for a cell to be empty
///   g: unnormalized probablity to go down
///   K: number of repeat walkers
///   S: parameter to scale the maximum number of steps to try
///   seed: random seed
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
#ifndef PARAMSH
#define PARAMSH

///
/// @brief Parameters for the simulation
///
struct Parameters {
    int    M;  ///< width of the percolation domain
    int    N;  ///< height of the percolation domain
    float  p;  ///< probablity for a cell to be empty
    float  g;  ///< unnormalized probablity to go down
    float  K;  ///< number of repeat walkers
    int    S;  ///< parameter to scale the maximum number of steps to try
    long   seed;  ///< random seed
};

/// Default values
const Parameters defaultParameters = { 200, 200, 0.7f, 2.0f, 25, 20, 1342 };

#endif
