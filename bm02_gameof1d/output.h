// output.h
//
// Contains the routine that displays the gameof1d system to console.
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#ifndef OUTPUTH
#define OUTPUTH

#include <rarray>

//
// Output time step, life status of cells, and fraction of alive cells
// as one line to the console
//
// Input arguments required is the current time step number and the rvector
// containing the alive status of the cells.
//
// Output goes to the console.
//
void output(int step, rvector<bool> alive_status);

#endif
