# Makefile for modular gameof1d
#
# Reference solution of assignment 2 of PHY1610H Winter 2025
#
# Requires, in addition to a compiler, the rarray module to be loaded

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

all: gameof1d

gameof1d: gameof1d.o initalive.o timestep.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gameof1d.o: gameof1d.cpp initalive.h timestep.h output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

initalive.o: initalive.cpp initalive.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

timestep.o: timestep.cpp timestep.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

output.o: output.cpp output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: gameof1d
	./gameof1d 

bigrun: gameof1d
	/usr/bin/time taskset -c 0 ./gameof1d 120000 400000 0.48 > /dev/shm/bigrun02.out

clean:
	$(RM) gameof1d.o timestep.o output.o initalive.o

distclean: clean
	$(RM) gameof1d /dev/shm/bigrun02.out

.PHONY: all clean run distclean bigrun
