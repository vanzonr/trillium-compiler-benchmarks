/// @file readcommandline.cpp
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
/// See @ref readcommandline.h
///
#include "readcommandline.h"
#include <iostream>
#include <boost/program_options.hpp>

int read_command_line(int argc, char* argv[], Parameters& parameters)
{
    using boost::program_options::value;
    boost::program_options::options_description desc("Options for 'percolation'");
    desc.add_options()
        ("help,h",                                    "Print help message")
        ("width,m",      value<int>  (&parameters.M), "width of the percolation domain")
        ("height,n",     value<int>  (&parameters.M), "height of the percolation domain")
        ("empty,p",      value<float>(&parameters.p), "probability for a cell to be empty")
        ("down,g",       value<float>(&parameters.g), "unnormalized probabilty to go down (>1))")
        ("repeat,k",     value<float>(&parameters.K), "number of repeated walkers")
        ("maxtime,s",    value<int>  (&parameters.S), "factor to scale maximum number of steps with")
        ("randomseed,r", value<long> (&parameters.seed), "random seed");
    boost::program_options::variables_map args;
    try {
        store(parse_command_line(argc, argv, desc), args);
        notify(args);
    }
    catch (...) {
        std::cerr << "ERROR in command line arguments!\n" << desc;
        return 2;
    }
    if (args.count("help")) {
        std::cout << "Usage:\n    " << argv[0] << " [OPTIONS]\n" << desc;
        return 1;
    }
    return 0;
}
