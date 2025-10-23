// init_c2.cpp
#include "init.h"

#include <catch2/catch_all.hpp>

TEST_CASE("initMatrix test n=27")
{
    rmatrix<double> M = initMatrix(27);
    REQUIRE(M.extent(0) == 27);
    REQUIRE(M.extent(1) == 27);

}

TEST_CASE("initMatrix test n=0")
{
    rmatrix<double> M = initMatrix(0);
    REQUIRE(M.extent(0) == 0);
    REQUIRE(M.extent(1) == 0);
}

TEST_CASE("initMatrix test n=1")
{
    rmatrix<double> M = initMatrix(1);
    REQUIRE(M.extent(0) == 1);
    REQUIRE(M.extent(1) == 1);
    REQUIRE(fabs(M[0][0]+97.0/2500.0) < 1e-15);
}

