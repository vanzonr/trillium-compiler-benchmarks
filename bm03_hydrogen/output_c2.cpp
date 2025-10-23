// output_c2.cpp
#include "output.h"
#include <fstream>

#include <catch2/catch_all.hpp>

TEST_CASE("writeText test")
{
    // create file:
    rvector<double> a(3);
    a = 1,2,3;
    writeText("testoutputarr.txt", a);
    // read back:
    std::ifstream in("testoutputarr.txt");
    std::string s[3];
    in >> s[0] >> s[1] >> s[2];
    // check
    REQUIRE(s[0]=="1");
    REQUIRE(s[1]=="2");
    REQUIRE(s[2]=="3");
}

TEST_CASE("writeBinary test")
{
    // create file:
    rvector<double> a = make_rarray({1.0,2.0,3.0});
    writeBinary("testoutputarr.bin", a);
    // read back, one double at a time
    std::ifstream in("testoutputarr.bin",std::ios::binary);
    for (double x: a) {
        double y;
        in.read(reinterpret_cast<char*>(&y), sizeof(double));
        REQUIRE(x == y);
    }
    in.close();
}
