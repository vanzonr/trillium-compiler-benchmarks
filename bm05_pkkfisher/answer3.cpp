/// @file answer3.cpp
///
/// Reference solution for part 1 of assignment 5 of the PHY1610 Winter 2025 course.
/// (matrix-vector multiplication using non-zero elements only)
///
#include <rarray>
#include <iostream>
#include "params.h"
#include "output.h"
#include "readcommandline.h"

///
/// @brief Solution of the PDE using sparseness of the matrix in the matrix-vector multiplication, by just writing it out (no blas, no matrix)
///
/// @param p the parameters; see @ref params.h (Param)
///
void using_mv_sparse(const Param& p)
{
    // Derived parameters
    int nsteps = p.T / p.D;
    double dx = p.L/(p.N - 1);
    double alpha = p.D / (dx*dx);
    // Create vectors and matrices
    rvector<double> u(p.N); 
    rvector<double> uold(p.N);
    u.fill(0.0);
    // Time stepping starts
    for (int s = 0; s <= nsteps; s++) {
        if (s%(nsteps/p.P)==0)
            output(s*p.D, dx, u);
        std::swap(u, uold);
        for (int i = 1; i < p.N-1; i++)
            u[i] = uold[i] + alpha*(uold[i-1]+uold[i+1]-2*uold[i]);
        for (int i = 0; i < p.N; i++)
            u[i] += p.D * uold[i] * (1-uold[i]);
        u[0] = p.A*pow(sin((s+1)*p.D),2);
        u[p.N-1] = 0.0;
    }
}

///
/// @brief main function of the answer1 program
///
int main(int argc, char* argv[])
{
    // Define defaults settings
    Param p = defaultParam;
    // Parse the command line
    int status = read_command_line(argc, argv, p);
    if (status > 0) 
        return status - 1;
    // Report
    std::cout << "#P " << p.P << "\n#L " << p.L << "\n"
              << "#A " << p.A << "\n#N " << p.N << "\n"
              << "#T " << p.T << "\n#D " << p.D << "\n";
    using_mv_sparse(p);
}

