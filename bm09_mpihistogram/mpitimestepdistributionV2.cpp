/// @file: mpitimestepdistribution.cpp
///
/// A similar simulation as that of assignment 7 has produced a record of
/// the number of steps each walker needed to reach the bottom (instead of
/// the fraction of percolating walkers).
///
/// You are given the data file with very many of these step
/// numbers. All step numbers were less than 100,000,000.
/// Each recorded step number in the file is on a separate line of 8
/// characters.
///
/// This is a MPI-parallel C++ program to compute the distribution of
/// the time steps.  Because the step numbers vary so much in size, it
/// should compute the histogram not of the values themselves, but of
/// their logarithm.
///
/// The programs should take the base of the logarithm as a command
/// line arguments, as well as the name of the data file, and a batch
/// size Z. The latter is a limit on how many numbers to read in at
/// once from the data file before distributing them to the MPI
/// processes.
///

#include <fstream>
#include <filesystem>
#include <iostream>
#include <limits>
#include <rarray>
#include <mpi.h>
#include "ticktock.h"

const double NA = 0; // use to indicate missing data. Note: there are no zero times, and if there were, you couldn't take the log

/// Compute a rounded up division 
int ceildiv(int numerator, int denominator)
{
    return (numerator + denominator-1)/denominator;
}

/// read the file in parallel
rvector<double> read_data(std::string filename, long long batchsize)
{
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // From file size get total number of lines
    int filesize = std::filesystem::file_size(filename);
    int linesize = 9;
    int nlines = ceildiv(filesize,linesize); // each lines is 8 characters plus the end-of-line character
    // Upper bounds on these
    long long localpoints = ceildiv(nlines,size); // number of points per batch per rank
    rvector<double> localtimes(localpoints);
    localtimes.fill(NA); // NA indicates non-read in points (can happen because localpoints is an upper bound)
    if (0 == rank) {
        std::cout << "# File size is " << filesize << " bytes,"
                  << "which is " << nlines << " lines of 8 characters.\n";
    }
    std::ifstream filein(filename);
    filein.seekg(rank*localpoints*linesize);
    for (int i = 0; i < localpoints && not filein.eof(); i++) 
        filein >> localtimes[i];
    return localtimes;
}

/// Compute the maximum of all array in MPI_COMM_WORLD
double mpi_max(const rvector<double>& v)
{
    double max = 0;
    double localmax = 0;
    for (const auto x: v)
        if (localmax < x)
            localmax = x;
    MPI_Allreduce(&localmax, &max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    return max;
}

/// Compute a logarithmic histogram of data in v with given log base, with at most nbins bins
rvector<int> histogram(rvector<double> v, double logbase, int nbins)
{
    rvector<int> h(nbins);
    h.fill(0);
    for (const auto x: v) {
        if (x != NA) {
            int logx = int(log(x)/log(logbase));
            if (logx >= 0 && logx < nbins)
                h[logx]++;
        }
    }
    return h;
}
    

int main(int argc, char** argv)
{
    // Initialize MPI
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Read command line arguments
    if (argc != 4) {
        if (0 == rank)
            std::cerr << "Error: You must supply three MPI_COMM_WORLDand line arguments: the logarithm base, the name of the data file, and the batch size.\n";
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    double      logbase  {std::stod(argv[1])};
    std::string filename {argv[2]};
    long long   batchsize{std::stol(argv[3])};
    if (0 == rank) 
        std::cout << "# Filename:   " << filename  << "\n"
                  << "# Log base:   " << logbase   << "\n"
                  << "# Batch size: " << batchsize << "\n";
    // Read data
    TickTock timer;
    timer.tick();
    rvector<double> localtimes = read_data(filename, batchsize);
    timer.tock("# Reading data took:");
    // Compute logarithmic histogram with a given base
    timer.tick();
    double maxt = mpi_max(localtimes);
    int nbins = int(log(maxt)/log(logbase))+1;
    rvector<int> localbins = histogram(localtimes, logbase, nbins);
    rvector<int> bins(nbins);    
    MPI_Reduce(localbins.data(), bins.data(), localbins.size(), MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    timer.tock("# Histogram of data took:");
    // Output:
    // Column 1 has the start of the histogram bin and
    // Column 2 has the number of data points that fall into that bin (normalized)
    if (0 == rank) {
        long long norm = 0;
        for (int i = 0; i < nbins; i++)
            norm += bins[i];
        std::cout << "Z=" << norm << "\n";
        for (int i = 0; i < nbins; i++)
            std::cout << pow(logbase,i) << " " << bins[i]/double(norm) << "\n";
        std::cout << pow(logbase,nbins) << " " << 0/double(norm)  << "\n";
    }
    MPI_Finalize();
    return 0;
}
