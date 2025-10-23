// output.cpp
//
// Implements the routines defined in output.h for console output of
// the gameof1d system.
//
// Part of the reference solution of assignment 2 of PHY1610H Winter 2025
//
#include "output.h"
#include <string>

//
// Output time step, life status of cells, and fraction of alive cells
//
void output(int step, rvector<bool> alive_status)
{
    constexpr char alive_char = 'O';
    constexpr char dead_char = ' ';
    constexpr char chars[2] = {dead_char, alive_char};    
    std::string string_representation(alive_status.size(),' ');
    double fraction = std::count(alive_status.begin(), alive_status.end(), true)
        / double(alive_status.size());
    for (int i = 0; i < alive_status.size(); i++) 
	string_representation[i] = chars[alive_status[i]];
    std::cout << step << "\t" << string_representation << " " << fraction << "\n";
}
