This is the reference solution for assigment 8 of PHY1610 Winter 2025,
which asks to perform a histogram of the logarithms of the number of timesteps it takes for walkers to go through a porous medium (the simulation of assignment 7).  The code is parallelized with OpenMP. It takes two command line arguments: the logarithm base and the data file with the timings.  The file is assume to consist of lines exactly 8 characters long (9 counting the end-of-line character), and each lines contains one number.

The program requires the gcc and rarray.

The submission contains two source files, a Makefile, three job submission scripts and three output text files.

timestepdistribution.cpp
: the serial version of the program

timestepdistribution-omp.cpp
: the OpenMP-parallel version of the program

Makefile
: use this to compile and link the program with type "make all". It can also run the codes with "make run", assuming that the data file called stepnumbers.dat is present in the current directory.

However, the program should actually be run in the job queue of the Teach cluster using "sbatch JOBSCRIPT" where JOBSCRIPT is one of the scripts listed below.

jobwith1thread
: Job script for the teach cluster to run the parallel code but with only one thread.

jobwith16threads
: Job script for the teach cluster to run the parallel code with 16 threads


jobwith40threads
: Job script for the teach cluster to run the parallel code with 40 threads.

3390_1thread.out
: Output file from running the "jobwith1thread" script through sbatch.

3389_16threads.out
: Output file from running the "jobwith16threads" script through sbatch.

3388_40threads.out
: Output file from running the "jobwith40threads" script through sbatch.

README.md
: is this file
