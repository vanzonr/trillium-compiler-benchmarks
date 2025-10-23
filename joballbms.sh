#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=24
#SBATCH --cpus-per-task=8
#SBATCH --time=4:00:00
#SBATCH --output=doall_%j.out
#SBATCH --error=doall_%j.log

set -euo pipefail

COMPILERS=(gcc-12 gcc-13 gcc-14 gcc-15 intel-23 intel-24 aocc-5 clang-18 llvm-20)
CODES=(bm02_gameof1d bm03_hydrogen bm05_pkkfisher bm06_pdefft bm07_percolation bm08_openmphistogram)

export TIME="%e s elapsed"

if ! [ "${1:-}" = bigrun ]; then

    # test compilation and short runs:

    for c in ${COMPILERS[@]}; do
	printf "+-------------------------------+\n+ Compiling with %-9s\t+\n+-------------------------------+\n" "$c"
	source setup-$c
	module -terse list | column -c72
	for code in ${CODES[@]}; do
	    echo "INFO: Compiling code \"$code\" with $c" 1>&2
	    cd "$code"
	    make clean
	    make -j 8
	    echo "INFO: Running \"$code\"" 1>&2
	    make run
	    if grep -q ^test: Makefile; then
		make test
	    fi
	    cd ..
	done
    done
    
else
    
# big runs:

    for code in ${CODES[@]}; do
	cd "$code"
	if grep -q ^bigrun: Makefile; then
	    for c in ${COMPILERS[@]}; do
		echo "INFO: Compiling and running code \"$code\" with $c" 1>&2
		source ../setup-$c 1>&2
		make clean 1>&2
		make -j 10 1>&2
		make bigrun
	    done
	fi
	cd ..
    done
fi

