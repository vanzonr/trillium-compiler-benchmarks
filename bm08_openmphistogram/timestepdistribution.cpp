/// @file: timestepdistribution.cpp
///
/// A similar simulation as that of assignment 7 has produced a record of
/// the number of steps each walker needed to reach the bottom (instead of
/// the fraction of percolating walkers).
///
/// You are given the data file with these step numbers. All
/// step numbers were less than 100,000,000. Each recorded step number in
/// the file is on a separate line of 8 characters.
///
/// You should write a parallel C++ program using OpenMP to compute the
/// distribution of the time steps.  Because the step numbers vary so much
/// in size, it should compute the histogram not of the values themselves,
/// but of their logarithm.
///
/// The programs should take the base of the logarithm as a command line
/// arguments, as well as the name of the data file.
///

#include <fstream>
#include <filesystem>
#include <iostream>
#include <rarray>

int main(int argc, char** argv)
{
    // read command line arguments
    if (argc != 3) {
        std::cerr << "Error: You must supply two command line arguments: the logarithm base and the name of the data file.\n";
        exit(1);
    }
    double logbase = std::stod(argv[1]);
    std::string filename(argv[2]);
    std::cout << "# Filename: " << filename << "\n";
    std::cout << "# Log base: " << logbase << "\n";
    // read the file (serial for now)
    int filesize = std::filesystem::file_size(filename);
    int nlines = (filesize+8)/9; // each lines is 8 characters plus the end-of-line character
    std::cout << "# File size is " << filesize << " bytes,"
              << "which should be " << nlines << " lines.\n";
    std::ifstream filein(filename);
    rvector<double> times(nlines);
    double maxt = 0;
    for (int i = 0; i < nlines; i++) {
        filein >> times[i];
        if (times[i] > maxt) maxt = times[i];
    }
    filein.close();
    // compute the logarithm with a given base
    int nbins = int(log(maxt)/log(logbase));
    rvector<int> bins(nbins+1);
    bins.fill(0);
    for (int i = 0; i < nlines; i++) {
        int logt = int(log(times[i])/log(logbase));
        bins[logt]++;
    }
    /* The output of the program should have 2 columns. Column 1 has
       the start of the histogram bin and column 2 the number of data
       points that fall into that bin. */
    for (int i = 0; i < nbins; i++) {
        std::cout << pow(logbase,i) << " " << bins[i] << "\n";
    }
    std::cout << pow(logbase,nbins) << " " << 0 << "\n";
}
/*

In the parallelization, both reading the numbers and computing the histogram should be parallelized.

Your submission should use git, and include a README file and include a Makefile that compiles the code.

It should furthermore include three SLURM  job scripts for the Teach cluster, one that runs the code with 1 thread, one with 16 threads, and one with 40 threads. Choose a logarithm base that gives at least 30 bins and have these three scripts measure the elapsed times of their computation. Submit these jobs to the queue and save their output. The output of these three runs should be identical except for the timing.

Submit, in a zip file, your git repo, your code, Makefile and README as well as the output of the three SLURM jobs by midnight March 28, 2025.

*/
