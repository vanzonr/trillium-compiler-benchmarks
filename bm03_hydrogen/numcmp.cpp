// compare binary files as floating point numbers with a tolerance for their difference
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>

template<class T>
int numcmp(std::ifstream& f1, std::ifstream& f2, const T& reltol)
{
    size_t ce = 0;
    while (f1.good() and f2.good()) {
	T d1;
	T d2;
	f1.read((char*)&d1, sizeof(d1)); 
	f2.read((char*)&d2, sizeof(d2));
	if (not f1.good() or not f2.good()) break;
	if (d1!=d2) {
	    T reldiff = 2*std::abs(d1-d2)/(std::abs(d1)+std::abs(d2));
	    if (reldiff > reltol) {
		std::cerr << "Error in number " << ce << "\n"
			  << "reldiff = " << reldiff
			  << " (> " << reltol  << ")\n";
		return 1;
	    }
	}
	ce++;
    }
    return 0;
}

int main(int argc, char** argv)
{
    if (argc<3) return 2;
    
    std::ifstream f1(argv[1], std::ios::binary);
    std::ifstream f2(argv[2], std::ios::binary);
    
    long double reltol = 0;
    if (argc>3)
	reltol = std::stold(argv[3]);

    int result = 0;
    if (argc>4) {
        if (strcmp(argv[4],"float") == 0) {
	    std::cerr << "Comparing single precision floating point numbers\n";
	    result = numcmp<float>(f1, f2, (float)(reltol));	           
	} else if (strcmp(argv[4],"longdouble") == 0) {
	    std::cerr << "Comparing long double precision floating point numbers\n";
	    result = numcmp<long double>(f1, f2, (long double)(reltol));	           
	} else {
	    std::cerr << "Comparing double precision floating point numbers\n";
	    result = numcmp<double>(f1, f2, (double)(reltol));
	}
    } else {
	std::cerr << "Comparing double precision floats\n";
	result = numcmp<double>(f1, f2, (double)(reltol));
    }

    if (result) {
	return result;
    }
    
    if (f1.good() and not f2.good()) {
	std::cerr << "Error: " << argv[1] << " has data beyond the size of "
		  << argv[2] << "\n";
	return 1;
    } else if (f2.good() and not f1.good()) {
	std::cerr << "Error: " << argv[2] << " has data beyond the size of "
		  << argv[1] << "\n";
	return 1;
    }
    std::cerr << "Comparison found no untolerable differences\n";
    return 0;
}

		
