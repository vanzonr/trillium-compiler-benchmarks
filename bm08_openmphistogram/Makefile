# Makefile for timestepdistribution.cpp
#
# Requires a C++ compiler and the rarray module

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

all: timestepdistribution timestepdistribution-omp

run: timestepdistribution timestepdistribution-omp stepnumbers.dat
	./timestepdistribution 1.1 stepnumbers.dat > thist.dat
	export OMP_NUM_THREADS=8 && ./timestepdistribution-omp 1.1 stepnumbers.dat > thist-omp.dat
	diff thist.dat thist-omp.dat

bigrun: timestepdistribution timestepdistribution-omp morestepnumbers.dat
	/usr/bin/time ./timestepdistribution 1.1 morestepnumbers.dat > morethist.dat
	export OMP_NUM_THREADS=8 && /usr/bin/time ./timestepdistribution-omp 1.1 morestepnumbers.dat > morethist-omp.dat

timestepdistribution: timestepdistribution.o 
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

timestepdistribution.o: timestepdistribution.cpp ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

timestepdistribution-omp: timestepdistribution-omp.o
	$(CXX) $(LDFLAGS) $(OMPFLAGS) -o $@ $^ $(LDLIBS)

timestepdistribution-omp.o: timestepdistribution-omp.cpp ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OMPFLAGS) -c -o $@ $<

clean:
	$(RM) timestepdistribution.o timestepdistribution-omp.o

distclean: clean
	$(RM) thist.dat thist-omp.dat morethist.dat morethist-omp.dat timestepdistribution timestepdistribution-omp stepnumbers.dat morestepnumbers.dat

.PHONY: run clean all distclean

