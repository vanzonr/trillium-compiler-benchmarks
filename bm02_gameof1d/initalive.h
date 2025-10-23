// initialive.h
//
// Contains the routine needed to initialize the gameof1d system.
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#ifndef INITALIVEH
#define INITALIVEH

#include <rarray>

//
// Fill cells such that the fraction of alive cells is roughly
// alive_fraction.
//
// Input arguments are the number of cells in the system and the
// target fracion of alive cells.
//
// Returns a newly constructed rarray, which will have an alive
// fraction close to the target fraction. It is not exact because the
// number of cells is finite.
//
rvector<bool> make_alive_status_by_fraction(int num_cells, double alive_fraction);

#endif
