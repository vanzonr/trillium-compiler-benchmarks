#
# Makefile for assignment 5 of PHY1610 Winter 2025
#
# Reference solution
#
# Required modules:
#  gcc
#  rarray
#  boost
#  openblas or another blas
#

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

CPPFLAGS += $(if $(BOOSTINCDIR), -I$(BOOSTINCDIR))
LDFLAGS  += $(if $(BOOSTLIBDIR), -L$(BOOSTLIBDIR))
LDLIBS   += $(if $(BOOSTLIBS), $(BOOSTLIBS))

CPPFLAGS += $(if $(BLASINCDIR), -I$(BLASINCDIR))
LDFLAGS  += $(if $(BLASLIBDIR), -L$(BLASLIBDIR))
LDLIBS   += $(if $(BLASLIBS), $(BLASLIBS))

all: answer1 answer2 answer3

run: answer1 answer2 answer3
	./answer1 -P 400 -L 5.0 -A 0.2 -N 100 -T 10 -D 0.001 > answer1.out
	./answer2 -P 400 -L 5.0 -A 0.2 -N 100 -T 10 -D 0.001 > answer2.out
	./answer3 -P 400 -L 5.0 -A 0.2 -N 100 -T 10 -D 0.001 > answer3.out

bigrun: answer1 answer2 answer3
	/usr/bin/time taskset -c 0 ./answer1 -P 40 -L 5.0 -A 0.2 -N 800 -T 50 -D 0.0000150 > biganswer1.out
	/usr/bin/time taskset -c 0 ./answer2 -P 40 -L 5.0 -A 0.2 -N 800 -T 50 -D 0.0000150 > biganswer2.out
	/usr/bin/time taskset -c 0 ./answer3 -P 40 -L 5.0 -A 0.2 -N 800 -T 500 -D 0.0000150 > biganswer3.out

answer1: answer1.o output.o readcommandline.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

answer2: answer2.o output.o readcommandline.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

answer3: answer3.o output.o readcommandline.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

answer1.o: answer1.cpp params.h output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

answer2.o: answer2.cpp params.h output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

answer3.o: answer3.cpp params.h output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

output.o: output.cpp output.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

readcommandline.o: readcommandline.cpp readcommandline.h params.h ../config.mk
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) output.o readcommandline.o answer1.o answer2.o answer3.o 

distclean: clean
	$(RM) answer1 answer2 answer3 answer1.out answer2.out answer3.out biganswer1.out biganswer2.out biganswer3.out

.PHONY: all run clean distclean bigrun
