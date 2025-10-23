// hydrogen.cpp
#include <iostream>
#include <rarray>
#include "eigenval.h"
#include "output.h"
#include "init.h"
int main(int argc, char** argv) {
    const int z = (argc>1)?atoi(argv[1]):8;
    const int it = (argc>2)?atoi(argv[2]):20;
    const int n = (2*z+1)*(2*z+1)*(2*z+1);
    rmatrix<double> m = initMatrix(n);
    rvector<double> a;
    double e;    
    groundState(m, e, a, it);
    std::cout<<"Ground state energy="<<e<<"\n";
    writeText("data.txt", a);
    writeBinary("data.bin", a);
}
