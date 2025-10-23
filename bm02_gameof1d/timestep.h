// timestep.h
//
// Contains the routine needed to advance the gameof1d system by one
// time step.
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#ifndef TIMESTEPH
#define TIMESTEPH

#include <rarray>

//
// Update cells of gameof1d.
//
// Arguments are alive_status, which should contain the current values.
//
// Returns the new alive_status.
//
rvector<bool> onetimestep(const rvector<bool>& alive_status);

#endif
