/// @file readcommandline.cpp
///
/// Part of the reference solution for assignment 5 of the PHY1610 Winter 2025 course.
///
/// See @ref readcommandline.h
///

#include "readcommandline.h"
#include <iostream>
#include <boost/program_options.hpp>

int read_command_line(int argc, char* argv[], Param& param)
{
    using boost::program_options::value;
    boost::program_options::options_description desc("Options for answerA");
    desc.add_options()
        ("help,h",                              "Print help message")
        ("snapshots,P",value<int>   (&param.P), "number of snapshots to output")
        ("length,L",   value<double>(&param.L), "length of interval")
        ("amplitude,A",value<double>(&param.A), "boundary driving amplitude")
        ("points,N",   value<int>   (&param.N), "number of grid points")
        ("time,T",     value<double>(&param.T), "time to simulate")
        ("deltat,D",   value<double>(&param.D), "time step");
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
