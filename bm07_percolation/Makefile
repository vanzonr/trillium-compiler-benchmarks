#
# Makefile for assignment 7 of PHY1610 Winter 2025
#
# Reference solution
#
# Required modules (in addition to a compiler):
#  rarray
#  boost

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

CPPFLAGS += $(if $(BOOSTINCDIR), -I$(BOOSTINCDIR))
LDFLAGS  += $(if $(BOOSTLIBDIR), -L$(BOOSTLIBDIR))
LDLIBS   += $(if $(BOOSTLIBS), $(BOOSTLIBS))

all: percolation

run: percolation
	./percolation --width 200 --height 200 --empty 0.7 --down 2 --repeat 25 --maxtime 20 --randomseed 1342

bigrun: percolation
	/usr/bin/time taskset -c 0 ./percolation --width 300 --height 300 --empty 0.7 --down 2 --repeat 100 --maxtime 30 --randomseed 1342 > bigrun07.txt 

percolation: percolation.o readcommandline.o medium.o onewalker.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

percolation.o: percolation.cpp parameters.h readcommandline.h prng.h onewalker.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

medium.o: medium.cpp medium.h prng.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

onewalker.o: onewalker.cpp onewalker.h prng.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

readcommandline.o: readcommandline.cpp readcommandline.h parameters.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) readcommandline.o percolation.o onewalker.o medium.o 

distclean: clean
	$(RM) percolation bigrun07.txt 

.PHONY: all run clean distclean
