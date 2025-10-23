/// @file percolation.cpp
///
/// @brief Performs a percolation simulation of walkers on a partially
/// (randomly) filled 2D lattice.
///
/// The percolation model here consists of a two-dimensional lattice
/// Some cells are 'filled', others are 'empty', representing a
/// porious medium.
///
/// Walkers will try to start at the top and get to the bottom
/// visiting only empty cells. In every time step, the probabilities
/// for going left, right, up, and down are 1/z, 1/z, 1/(gz) and g/z,
/// respectively, where z is such that the probablities sum up to 1.
/// If the cell to go to is either filled or non-existant (at the
/// boundary), that probability is set to zero and z is adjusted.
/// The walker never stays in the same spot.
/// At most S*(M*M+N*N) steps are taken per walker.
///
/// Input parameters are:
///   M: width of the percolation domain
///   N: height of the percolation domain
///   p: probablity for a cell to be empty
///   g: unnormalized probablity to go down
///   K: number of repeat walkers
///   S: parameter to scale the maximum number of steps to try
///   seed: random seed
///
/// The simulation determines the fraction of walkers that made it to the bottom.
///
/// Note: Percolation models are concerned with whether a porous media can be
/// traversed from one end to the other.  This could model e.g. oil
/// in a reservoir, melting snow on compact soil, or brewing drip coffee.
///
/// This program requires the gcc, boost and rarray modules to be
/// loaded on the Teach cluster.
///
/// Reference solution for assignment 7 of PHY1610 Winter 2025
///
#include "parameters.h"
#include "readcommandline.h"
#include "prng.h"
#include "medium.h"
#include "onewalker.h"

extern int t;

int main(int argc, char* argv[])
{
    // Define defaults settings
    Parameters p = defaultParameters;
    
    // Parse the command line
    int status = read_command_line(argc, argv, p);
    if (status > 0) 
        return status - 1;
    
    // Report parameters
    // std::cout << "#M " << p.M << "\n#N " << p.N << "\n"
    //           << "#p " << p.p << "\n#g " << p.g << "\n"
    //           << "#K " << p.K << "\n#S " << p.S << "\n"
    //           << "#seed " << p.seed << "\n";
    
    // The assignment of emptyness is random, such that any cell has a
    // probablity p to be empty.
    PRNG rng(p.seed);
    rmatrix<bool> empty_cells = generate_medium(p.N, p.M, p.p, rng);
    
    // Next, we introduce a "walker" in each of the empty top row cells.
    int nwalkers = 0;
    for (int j = 0 ; j< p.M; j++)
        if (empty_cells[0][j])
            nwalkers++;
    rvector<Point> walker(nwalkers);
    
    // To improve statistics, we repeat the process K times, i.e., we
    // start K walkers in each empty top row cell.
    int number_of_percolators = 0;
    for (int repeat = 0; repeat < p.K; repeat++) {
        // Initialize the walker positions
        int k = 0;
        for (int j = 0 ; j< p.M; j++) 
            if (empty_cells[0][j]) 
                walker[k++] = Point{0,j};
        // See which walkers makes it to the bottom
        for (int k = 0; k < nwalkers; k++) {
            walker[k] = one_walker(p, empty_cells, walker[k], rng);
            if (walker[k].i == p.N-1)
                number_of_percolators++;
        }
    }

    // Report result
    int percolating_walkers_percentage = (100*number_of_percolators)/(nwalkers*p.K);
    std::cout << "Percolating walkers fraction: "
              << percolating_walkers_percentage
              << "%\n";

}

