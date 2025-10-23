// gameof1d.cpp
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025.
//
// This code computes the evolution of a one-dimensional variant of Conway's Game of Life,
// as conceived by Jonathan K. Millen and published in BYTE magazine in December, 1978.
//
// This system is a linear set of cells that are either "alive" or "dead".
// Time in this system progresses in discrete steps.
//
// The state of each cell at the next time step depends on its present
// state and that of its neighbors, in the following way:
//
//   - First, count the number of alive neighbors at most 2 cells away
//   - An alive cell stays alive if that count is 2 or 4, else it dies
//   - A dead cell becomes alive if that count is 2 or 3, else it stays dead.
//
// Since the first two and the last two cells would not have enough neighbours to apply
// this rule, we use cells on the other side as neighbours, i.e., 'periodic boundaries'.
//
// The initial state of this system is constructed with a given fraction of alive
// cells which are (nearly) equally spaced among dead cells.
//
// Without command line arguments, the program computes the time
// evolution for 120 steps, and for each step, prints out a line with
// a representation of the state and fraction of alive cells.
//
// This code is part of assignment 2 of the 2025 Winter PHY1610 course.
//
// Ramses van Zon, 2023-2025, University of Toronto

#include <iostream>
#include <rarray>
#include "initalive.h"
#include "timestep.h"
#include "output.h"

int main(int argc, char* argv[])
{
    // Set default simulation parameters then accept command line arguments
    int num_cells = 70;
    int num_steps = 120;
    double target_fraction = 0.35;
    try {
        if (argc > 1)
            num_cells = std::stoi(argv[1]);
        if (argc > 2)
            num_steps = std::stoi(argv[2]);
        if (argc > 3)
            target_fraction = std::stod(argv[3]);
    } catch(...) {
        std::cout <<
            "Computes a 1d version of Conway's game of life\n\n"
            "Usage:\n"
            "  gameof1d [-h | --help] | [NUMCELLS [NUMSTEPS [FRACTION]]]\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) != "--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }
    // Simulation system is just the alive status of each cell
    rvector<bool> alive_status = make_alive_status_by_fraction(num_cells, target_fraction);
    // Output the first step
    output(0, alive_status);
    // Time evolution loop
    for (int step = 1; step <= num_steps; step++) {
        // Update cells
        alive_status = onetimestep(alive_status);
        // Output time step, life status of cells, and fraction of
        // alive cells
        output(step, alive_status);
    }
} // end main
