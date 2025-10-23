/// @file output.h
///
/// Write the elements of the field at time t to console in three-column format
/// (t, x, a[t,x])
///
/// Part of the reference solution for assignment 5 of the PHY1610 Winter 2025 course.
///
#ifndef OUTPUTH
#define OUTPUTH

#include <rarray>

///
/// @brief output routine to the terminal
///
/// @param t   time (double)
/// @param dx  grid spacing (double)
/// @param a   field at time t (rvector<double>)
///
void output(double t, double dx, const rvector<double>&a);

#endif

