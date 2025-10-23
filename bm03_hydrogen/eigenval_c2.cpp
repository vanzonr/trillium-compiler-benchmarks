// eigenval_c2.cpp
#include "eigenval.h"

#include <catch2/catch_all.hpp>

TEST_CASE("groundState test 2x2")
{
    // construct a known matrix
    rmatrix<double> M = make_rarray({{-1.0, 1.0},
                                     {2.0,0.0}});
    double E;
    rvector<double> v;
    groundState(M, E, v);
    // the method is not very precise, 0.1% accuracy is all we can hope for
    CHECK_THAT(E, Catch::Matchers::WithinRel(-2.0,1e-3));
}

TEST_CASE("groundState test diag")
{
    // test a number of sizes
    for (int n = 5; n<10; n++) {
        rmatrix<double> M = make_rarray(n,n, 0.0);
        for (int i=0; i<n; i++)
            M[i][i] = -1.5*(i-3);
        double E;
        rvector<double> v;
        groundState(M, E, v);
        // the method is not very precise,
        // 0.1% accuracy is all we can hope for
        CHECK_THAT(E, Catch::Matchers::WithinRel(M[n-1][n-1],1e-3));
    }
}

TEST_CASE("groundState test identity")
{
    // This test currently fails!!!
    // It finds a bug in groundState(...).
    for (int n = 5; n<10; n++) {
        rmatrix<double> M = make_rarray(n,n, 0.0);
        for (int i=0; i<n; i++)
            M[i][i] = 1.0;
        double E;
        rvector<double> v;
        groundState(M, E, v);
        // the method is not very precise,
        // 0.1% accuracy is all we can hope for
        CHECK_THAT(E, Catch::Matchers::WithinRel(1.0,1e-3));
    }
}



