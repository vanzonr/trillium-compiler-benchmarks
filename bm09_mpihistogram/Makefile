# Makefile for mpitimestepdistribution.cpp
# requires an mpi compiler and the rarray module

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

CXX=$(MPICXX)

all: mpitimestepdistribution mpitimestepdistributionV2

run: mpitimestepdistribution mpitimestepdistributionV2 stepnumbers.dat
	mpirun -n 4 ./mpitimestepdistribution 1.1 stepnumbers.dat 100000 > thist-mpi4.dat
	mpirun -n 1 ./mpitimestepdistribution 1.1 stepnumbers.dat 100000 > thist-mpi1.dat
	mpirun -n 4 ./mpitimestepdistributionV2 1.1 stepnumbers.dat 100000 > thist-mpi4V2.dat
	mpirun -n 1 ./mpitimestepdistributionV2 1.1 stepnumbers.dat 100000 > thist-mpi1V2.dat
	diff --ignore-matching-lines='^#' thist-mpi4.dat thist-mpi1.dat || echo "Inconsistent results"
	diff --ignore-matching-lines='^#' thist-mpi4V2.dat thist-mpi4.dat || echo "Inconsistent results"
	diff --ignore-matching-lines='^#' thist-mpi4V2.dat thist-mpi1V2.dat || echo "Inconsistent results"

bigrun: mpitimestepdistribution mpitimestepdistributionV2 morestepnumbers.dat
	/usr/bin/time mpirun -n 4 ./mpitimestepdistribution 1.1 morestepnumbers.dat 100000 > thistbig-mpi4.dat
	/usr/bin/time mpirun -n 1 ./mpitimestepdistribution 1.1 morestepnumbers.dat 100000 > thistbig-mpi1.dat
	/usr/bin/time mpirun -n 4 ./mpitimestepdistributionV2 1.1 morestepnumbers.dat 100000 > thistbig-mpi4V2.dat
	/usr/bin/time mpirun -n 1 ./mpitimestepdistributionV2 1.1 morestepnumbers.dat 100000 > thistbig-mpi1V2.dat

mpitimestepdistribution: mpitimestepdistribution.o ticktock.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

mpitimestepdistributionV2: mpitimestepdistributionV2.o ticktock.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

mpitimestepdistribution.o: mpitimestepdistribution.cpp ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

mpitimestepdistributionV2.o: mpitimestepdistributionV2.cpp  ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

ticktock.o: ticktock.cpp ticktock.h  ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) mpitimestepdistribution.o mpitimestepdistributionV2.o ticktock.o

distclean: clean
	$(RM) mpitimestepdistribution mpitimestepdistributionV2 thist-mpi1.dat thist-mpi4.dat thist-mpi1V2.dat thist-mpi4V2.dat thistbig-mpi1.dat thistbig-mpi4.dat thistbig-mpi1V2.dat thistbig-mpi4V2.dat

.PHONY: run clean distclean all
