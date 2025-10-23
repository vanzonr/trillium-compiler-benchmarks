This is the reference solution for assigment 7 of PHY1610 Winter 2025,
which asks to perform a percolation simulation of walkers through a
porous medium.

The program requires the gcc, rarray, and boost modules to be
loaded on the Teach cluster.

To compile and run the program, type "make run".

The program contains 6 source files:

parameters.h
: contains definition of a structure containing all the parameters

prng.h
: contains a class to deal with drawing random numbers, based on the C++ random library

percolation.cpp
: the main program that runs the simulation

medium.h
: the header file for the medium generating module

medium.cpp
: the implementation file for the medium generating module

readcommandline.h
: the header file for the module that interprets the command line parameters

readcommandline.cpp
: the implementation file for the module that interprets the command line parameters

onewalker.h
: the header file for the module that simulates a single walker

onewalker.cpp
: the implementation file for the module that simulates a single walker

