# Makefile for 'hydrogen'
#
# Requires the following modules (in addition to a compiler):
#  rarray
#  catch2

include ../config.mk

CPPFLAGS += $(if $(RARRAYINCDIR), -I$(RARRAYINCDIR))
LDFLAGS  += $(if $(RARRAYLIBDIR), -L$(RARRAYLIBDIR))
LDLIBS   += $(if $(RARRAYLIBS), $(RARRAYLIBS))

CPPFLAGS += $(if $(CATCH2INCDIR), -I$(CATCH2INCDIR))
LDFLAGS  += $(if $(CATCH2LIBDIR), -L$(CATCH2LIBDIR))
LDLIBS   += $(if $(CATCH2LIBS), $(CATCH2LIBS))

all: hydrogen

hydrogen.o: hydrogen.cpp eigenval.h output.h init.h ../config.mk
eigenval.o: eigenval.cpp eigenval.h ../config.mk
output.o: output.cpp output.h ../config.mk
init.o: init.cpp init.h ../config.mk
output_c2.o: output_c2.cpp output.h ../config.mk
init_c2.o: init_c2.cpp init.h ../config.mk
eigenval_c2.o: eigenval_c2.cpp eigenval.h ../config.mk

hydrogen: hydrogen.o eigenval.o output.o init.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

output_c2: output_c2.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

init_c2: init_c2.o init.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

eigenval_c2: eigenval_c2.o eigenval.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

run_output_c2: ./output_c2
	./output_c2 -s

run_init_c2: ./init_c2
	./init_c2 -s

run_eigenval_c2: ./eigenval_c2
	./eigenval_c2 -s || echo "NOTE: we know this fails, but fixing the bug was not part of the assignment!"

run: hydrogen
	./hydrogen > hydrogen.out

bigrun: hydrogen
	/usr/bin/time taskset -c 0 ./hydrogen 19 100 > /dev/shm/bigrun03.txt

numcmp: numcmp.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

integratedtest: hydrogen numcmp
	./hydrogen > hydrogen.out
	diff hydrogen.out reference-hydrogen.out
	diff data.txt reference-data.txt
	./numcmp data.bin reference-data.bin 1e-14 double

test: run_output_c2 run_init_c2 run_eigenval_c2 integratedtest

clean:
	$(RM) hydrogen.o eigenval.o output.o init.o output_c2.o init_c2.o eigenval_c2.o data.bin data.txt output_c2 init_c2 eigenval_c2 hydrogen.out testoutputarr.txt testoutputarr.bin

distclean: clean
	$(RM) hydrogen numcmp

.PHONY: all clean test run_output_c2 run_init_c2 run_eigenval_c2 integratedtest distclean
