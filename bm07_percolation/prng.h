/// @file prng.h
///
/// Header to define a class for drawing random numbers, based on <random>.
///
/// Part of the reference solution for assignment 7 of the PHY1610 Winter 2025 course
///
#ifndef PRNGH
#define PRNGH

#include <random>

///
/// Class to hold the Mersenne-Twister random number generator and a
/// uniform distributibetween 0 and 1, so it can generate random
/// numbers between 0 and 1.
///
class PRNG {
  private:
    std::mt19937 engine;
    std::uniform_real_distribution<float> uniform;
  public:
    /// Constructor; enforces that one must supply a seed
    PRNG(long seed)
      : engine(seed), uniform(0.0, 1.0)
    {}
    /// Method to draw a number between 0 and 1.
    float draw() {
        return uniform(engine);
    }
};

#endif
