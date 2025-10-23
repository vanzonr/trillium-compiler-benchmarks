/// @file onewalker.cpp
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
/// See @ref onewalker.h
///
#include "onewalker.h"
#include <exception>

int t;

Point one_walker(const Parameters& p,
                 const rmatrix<bool>& empty_cells,
                 const Point& initial,
                 PRNG& rng)
{
    // Check if empty has correct dimensions
    if (empty_cells.extent(0) != p.N or empty_cells.extent(1) != p.M)
        throw std::runtime_error("lattice dimension mismatch");
    
    // Check if Point lies in range    
    if (initial.i < 0 or initial.i > empty_cells.extent(0))
        std::runtime_error("initial vertical coordinate out of bounds");    
    if (initial.j < 0 or initial.j > empty_cells.extent(1))
        std::runtime_error("initial horizontal coordinate out of bounds");

    // Start moving upto a maximum number of S*(M^2+N^2) steps, but
    // stop when the bottom is reached.
    Point walker = initial;
    for (t = 0; t < p.S*(p.M*p.M + p.N*p.N); t++) {       
        // The walker moves one cell to left, right, down or up with
        // probability l, r, d, and u, respectively, which depend on a
        // positive parameter g>1 (representing the downwards
        // tendency): l = 1/z ; r = 1/z ; u = 1/(gz) ; d = g/z where z
        // is such that l+r+u+d = 1.  However, the walker cannot move to a
        // filled cell nor outside of the lattice.
        float l = 1.0;
        float r = 1.0;
        float u = 1.0/p.g;
        float d = p.g;
        // Can't go left when j=0 nor when the left cell is filled
        if (walker.j == 0 or not empty_cells[walker.i][walker.j-1] )
            l = 0;
        // Can't go right when j=M-1 nor when the right cell is filled
        if (walker.j == p.M-1 or not empty_cells[walker.i][walker.j+1])
            r = 0;
        // Can't go up when i=0 nor when the cell above is filled
        if (walker.i == 0 or not empty_cells[walker.i-1][walker.j])
            u = 0;
        // Can't go down when i=N-1 or when the cell below is filled
        if (walker.i == p.N-1 or not empty_cells[walker.i+1][walker.j])
            d = 0;
        float z = l+r+u+d;
        l /= z;
        r /= z;
        u /= z;
        d /= z;
        float c = rng.draw();
        if (c < l)
            walker.j -= 1;
        else if (c < l+r)
            walker.j += 1;
        else if (c < l+r+u)
            walker.i -= 1;
        else
            walker.i += 1;
        // Check if walker is at bottom
        if (walker.i == p.N-1) 
            break;
    }    
    return walker;
}
