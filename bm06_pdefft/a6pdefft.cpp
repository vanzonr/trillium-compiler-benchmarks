/// @file a6_pdefft.cpp
///
/// Solves the KPP-Fisher equation on an interval [0,L]
/// with initial condition u(x) = A*[sin(2*pi*x/L)]^100
///
/// Reference solution for assignment 6 of the PHY1610 Winter 2025 course.
///
#include <rarray>
#include <iostream>
#include <fftw3.h>
#include <complex>
#include "params.h"
#include "output.h"
#include "readcommandline.h"

using complex = std::complex<double>;

/// struct to collect variables to be kept between time steps
/// (avoids having to reallocate arrays and fftw plans)
struct state
{
    rvector<double> u;
    rvector<double> c;
    rvector<complex> uhat;
    fftw_plan planforward;
    fftw_plan planbackward;
};

///
/// @brief  Initialize the state
///
/// @param  L  length of the interval
/// @param  n  number of point in the interval
///
state init(double L, int n)
{
    state result;
    // vector for u
    result.u = rvector<double>(n);
    // vector for its complex-valued fourier transform, which is only n/2+1 points long.
    result.uhat = rvector<complex>(n/2+1);
    // c = k^2, which we recompute.
    // This is needed in the fourier transform, so is also n/2+1 points long.
    result.c = rvector<double>(n/2+1);
    for (int q=0; q<n/2+1; q++) 
        result.c[q] = pow(2*M_PI*q/L,2);
    // plan for performing the forward transform
    result.planforward = fftw_plan_dft_r2c_1d(result.u.size(),
                                              result.u.data(),
                                              (fftw_complex*)(result.uhat.data()),
                                              FFTW_ESTIMATE);
    // plan for performing the backward transform
    result.planbackward = fftw_plan_dft_c2r_1d(result.u.size(),
                                               (fftw_complex*)(result.uhat.data()),
                                               result.u.data(),
                                               FFTW_ESTIMATE);
    return result;
}

///
/// @brief Diffusion portion of the time step
///
/// @param  s       the state of the system (contains u, will be updated)
/// @param  deltat  time to evolve over
///
void diffusion_propagation(state& s, double deltat)
{
    // forward transform
    fftw_execute(s.planforward);
    // multiply with exp(-k^2*delta t), which is precomputed in s.c[q]
    for (int q = 0; q < s.uhat.size(); q++)
        s.uhat[q] *= std::complex{exp(-deltat*s.c[q])};
    // transform back
    fftw_execute(s.planbackward);
    // normalize
    const auto n = s.u.size();
    for (auto& ui: s.u)
        ui /= n;
}


/// @brief Reaction portion of the time step
///
/// @param  s       the state of the system (contains u, will be updated)
/// @param  deltat  time to evolve over
///
void reaction_propagation(state& s, double deltat)
{
    for (auto& ui: s.u)
        ui = ui/(ui + (1 - ui)* exp(-deltat));
}
    
///
/// @brief solution of the KPP_Fisher PDE
///
/// @param p the parameters; see @ref params.h (Param)
///
void simulation(const Param& p)
{
    state sys = init(p.L, p.N);

    // Initial value of u
    for (int j = 0; j < p.N; j++) {
        double x = (p.L*j)/p.N;
        sys.u[j] = p.A*pow(sin(M_PI*x/p.L),100); 
    }
    
    // Derived parameters
    double dx = p.L/(p.N - 1);

    // 
    for (int s = 0; s < p.P;  s++) {
        // evolve
        output(s*p.T/p.P, dx, sys.u);
        for (int subs = 0; subs < p.T/p.D/p.P; subs++) {
            reaction_propagation(sys, p.D/2);
            diffusion_propagation(sys, p.D);
            reaction_propagation(sys, p.D/2);
        }
    }    
}

///
/// @brief Main function of the program
///
int main(int argc, char* argv[])
{
    // Define defaults settings
    Param p = defaultParam;
    // Parse the command line
    int status = read_command_line(argc, argv, p);
    if (status > 0) 
        return status - 1;
    // Report parameters
    std::cout << "#P " << p.P << "\n#L " << p.L << "\n"
              << "#A " << p.A << "\n#N " << p.N << "\n"
              << "#T " << p.T << "\n#D " << p.D << "\n";
    // Perform the simulation 
    simulation(p);
}

