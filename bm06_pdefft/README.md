This is the reference solution for assigment 6 of PHY1610 Winter 2025,
which asks to solve the KPP_Fisher equation by using a agternation of
a diffusion step in fourier space and a reaction step in real space.

The program requires the gcc, rarray, fftw and boost modules to be
loaded on the Teach cluster.

To compile and run the program, type "make run".

The program contains 6 source files:

params.h
: contains definition of a structure containing all the parameters

a6pdefft.cpp
: the main program that runs the simulation

output.h
: the header file for the output module

output.cpp
: the implementation file for the output module

readcommandline.h
: the header file for the module that interprets the command line parameters

readcommandline.cpp
: the implementation file for the module that interprets the command line parameters

