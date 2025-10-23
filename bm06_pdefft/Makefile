#
# Makefile for assignment 6 of PHY1610 Winter 2025
#
# Reference solution
#
# Required modules:
#  gcc
#  rarray
#  boost
#  fftw

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

CPPFLAGS += $(if $(BOOSTINCDIR), -I$(BOOSTINCDIR))
LDFLAGS  += $(if $(BOOSTLIBDIR), -L$(BOOSTLIBDIR))
LDLIBS   += $(if $(BOOSTLIBS), $(BOOSTLIBS))

CPPFLAGS += $(if $(FFTWINCDIR), -I$(FFTWINCDIR))
LDFLAGS  += $(if $(FFTWLIBDIR), -L$(FFTWLIBDIR))
LDLIBS   += $(if $(FFTWLIBS), $(FFTWLIBS))

all: a6pdefft

run: a6pdefft
	./a6pdefft -P 400 -L 5.0 -A 0.2 -N 100 -T 10 -D 0.001 > a6pdefft.out

bigrun: a6pdefft
	/usr/bin/time taskset -c 0 ./a6pdefft -P 400 -L 5.0 -A 0.2 -N 800 -T 2000 -D 0.000030625 > biga6pdefft.out

a6pdefft: a6pdefft.o output.o readcommandline.o 
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

a6pdefft.o: a6pdefft.cpp params.h output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

output.o: output.cpp output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

readcommandline.o: readcommandline.cpp readcommandline.h params.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) output.o readcommandline.o a6pdefft.o

distclean: clean
	$(RM) a6pdefft.out biga6pdefft.out a6pdefft 

.PHONY: all run clean distclean bigrun
