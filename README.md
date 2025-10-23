# trillium-compiler-benchmarks

A collection of codes to assert the performance of several compiler on
the Trillium supercomputer (CPU subcluster only).

Many of these code were taken from the Winter 2025 PHY1610 course on
Scientific Computing assignments to test various compilers/

The script called "joballbms.sh" compiles and runs all the codes
mentioned below to test the compilers. This will also try to install a
lot of missing libraries for some of the compilers.

When run as "joballbms.sh bigrun" (or submitted woth sbatch), it runs
and times larger variations of some of these codes to test the
performance of the executable produced by various compilers.

## bm02_gameof1d

A one-dimensional variant of Conway's Game of Life from Jonathan
K. Millen, published in BYTE magazine, December, 1978.

**USAGE**
    ./gameof1d NUMCELLS NUMSTEPS INITIALFRACTION

**MODEL**
A linear set of NUMCELLS cells that are either "alive" or "dead"

**COMPUTATION**
Takes NUMSTEPS discrete time steps, where the state of each cell at
the next time step depends on its present state and that of its
neighbours, in the following way:

  - First, count the number of alive neighbours at most 2 cells away;
  - An alive cell stays alive if that count is 2 or 4, else it dies;
  - A dead cell becomes alive if that count is 2 or 3, else it stays dead.

Since the first two and the last two cells would not have enough
neighbours to apply this rule, we will use cells on the other side as
neighbours, i.e., we use 'periodic boundary conditions'.

**INITIALIZATION**
A given INITIALFRACTION of alive cells are nearly equally spaced among
dead cells.

**OUTPUT**
For each time step, prints out a line with a representation of the
state and fraction of alive cells.

**DEPENDENCIES**
rarray https://github.com/vanzonr/rarray

**BIG RUN PARAMETERS**
NUMCELLS = 120000
NUMSTEPS = 400000
INITIALFRACTION = 0.48 

## bm03_hydrogen

Computes the ground state energy of the hydrogen atom, i.e., the
lowest eigenvalue of the Hamiltonian matrix.

**USAGE**
    ./hydrogen N K

Run integrated test and unit tests with "make tests" (some tests will
fail by design).

**COMPUTATION**
First constructs the Hamiltonian matrix H in spatial representation by
discretizing if in a cubic domain [-L/2,L/2]^3 where L=50 (in certain
units) with 2N+1 points in each direction.  The total dimension of the
matrix H is therefore (2N+1)^3.

Then computes the eigenvector corresponding to the lowest eigenvalue,
by applying H - b1 to an inital uniform vector for a total of K times,
where b is the largest diagonal element.  The larger K, the more
accurate the result.  This method can fail, but that failure would be
detected.

The lowest eigenvalue is then determined as the expectation value of H
for that eigenvector.

**OUTPUT**
Prints the value it found for the hydrogen ground state.

**DEPENDENCIES**
rarray https://github.com/vanzonr/rarray
Catch2 https://github.com/catchorg/Catch2.

**BIG RUN PARAMETERS**
N = 19
K = 100
This amounts to 100 multiplications of a 59319x59319 matrix and a vector.
The code does not use call BLAS routines, but rather has its
own a naieve matrix-vector multiplication routine.
 
## bm05_pkkfisher

Simulation of the KPP-Fisher's equation, a diffusion equation with a non-linear reaction term, implemented in three different ways.

**USAGE**

  ./answer1 --snapshots P --length L --amplitude A --points N --time T --deltat DT
  ./answer2 --snapshots P --length L --amplitude A --points N --time T --deltat DT
  ./answer3 --snapshots P --length L --amplitude A --points N --time T --deltat DT

**MODEL**

The model consists of the following partial differential equation:

$$\frac{\partial u}[\partial t} - \frac{\partial^2 u}{\partial u^2} = u (1-u)$$

with x values restricted to the interval [0,L] and boundary values such that $u(0,t)=A\sin^2(t), and u(L,t) = 0 (for all t).  The initial value is given by u(x,0)=0.

**COMPUTATION**

The solution is numerically computed with an explicit time-stepping scheme using timesteps DT up to a time T and using a discretization of the interval into N points using the forward Euler integration scheme.

There are three implementations of the single-time step:

answer1:
Implements the diffusion part of the equation as a matrix-vector multiplication (with full matrices), with an explicit loop for that multiplication.

answer2:
Implements the diffusion part of the equation as a matrix-vector multiplication (with full matrices), using a dgemv BLAS call. 

answer3:
Implements the diffusion part of the equation using a discrete difference scheme, which is in a sense a sparse matrix-vector multiplication. 


**OUTPUT***
During the simulation, it creates P snapshots of the value of u on these N points to be printed to stdout. The format of the output contains the time, position, and value of u on separate lines in the output.

**DEPENDENCIES**
rarray   https://github.com/vanzonr/rarray
boost    https://www.boost.org
openblas or another blas

**BIG RUN PARAMETERS**
P = 40
L = 5.0
A = 0.2
N = 800
DT = 0.000015
T = 50 (500 for answer3).

## 06_pdefft

TBD

## 07_percolation

TBD

## 08_openmphistogram

TBD

