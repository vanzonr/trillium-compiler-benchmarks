// timestep.cpp
//
// Implements of the routine defined in timestep.h to advance to
// gameof1d system by one time step.
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#include "timestep.h"

//
// Internal routine to determine the next alive status of the cell at
// location 'index' within the linear set of cells 'cell_alive', based
// on the alive status of its neighboring cells.
//
// Not visible outside of this module.
//
bool is_cell_alive_next(const rvector<bool>& cell_alive, int index)
{
    int num_cells = cell_alive.size();
    int alive_neighbours = 0;
    for (int offset = -2; offset <= 2; offset++)
        if (offset != 0 and cell_alive[(index+offset+num_cells)%num_cells]) // modulus (%) enforces periodic boundary conditions
            alive_neighbours++;
    if (cell_alive[index] and
        (alive_neighbours == 2 or alive_neighbours == 4))
        return true;
    else if (not cell_alive[index] and
             (alive_neighbours == 2 or alive_neighbours == 3))
        return true;
    else
        return false;
}

//
// Update cells of gameof1d.
//
// Arguments are alive_status, which should contain the current values.
//
// Returns the new alive_status.
//
// Note to TA: a version which takes two rvectors and swaps them is also acceptable.
//
rvector<bool> onetimestep(const rvector<bool>& alive_status)
{
    rvector<bool> next_alive_status(alive_status.size());
    if (next_alive_status.size() != alive_status.size())
        next_alive_status = rvector<bool>(alive_status.size());
    for (int i = 0; i < alive_status.size(); i++) 
        next_alive_status[i] = is_cell_alive_next(alive_status, i);
    // Return next status
    return next_alive_status;  
}
