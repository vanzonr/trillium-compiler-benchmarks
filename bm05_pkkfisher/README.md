This is the reference solution for assignment 5 of the PHY1610H course
in winter 2025.

These codes simulates the KPP-Fisher's equation:

 ∂u/∂t −∂²u/∂x² = u(1−u)

which is a diffusion equation with a non-linear reaction term.

The x values are restricted to the interval [0,L], and the boundary
values are such that u(0,t) = A sin²(t) and u(L,t)=0 (for all t).

The initial value is given by u(x,0)=0.

The solution is numerically computed with an explicit time-stepping
scheme using timesteps Δt up to a time T, using a discretization of
the interval into N points, using forward Euler.

During the simulation, P snapshots are printed to screen of the values
of u on these N points. The format of the output is such that each
line contains three numbers separated by spaces, i.e., the time,
position, and value of u at that time and position.

P,L,A,N,T and Δt are input parameters of the codes.

The simulation is done differently by three applications

 1) in answer1.cpp: using a full matrix and an explicit triple loop
    for the matrix-vector multiplication

 2) in answer2.cpp: using a full matrix and a call to a BLAS routine
    from either openblas for the matrix-vector manipulation.

 3) in answer3.cpp: using only the non-zero elements of the matrix.

Helper code is found in output.h, output.cpp, readcommandline.h and
readcommmandline.cpp, which deal with the data output and the input
parameters.

"make" compiles all three applications (producing answer1, answer2 and
answer3).  On the Teach cluster, this requires the following modules to be loaded: gcc/12.3, rarray/2.8.0, openblas/0.3.24, and boost/1.85.0.

"make run" runs all three applications  using the following parameters:
 L=5, A=0.2, N=100, T=10, P=400, and Δt=0.001

with the results stored in
the files answer1.out, answer2.out, and answer3.out respectively.

