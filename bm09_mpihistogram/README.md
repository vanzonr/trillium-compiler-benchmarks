# MPI Histogram - Assignment 9

This project computes a logarithmic histogram of numeric data using MPI. It includes two versions of the same computation:

- **Version 1**: Serialized file reader (on process with rank 0)
- **Version 2**: Parallel reads by each MPI process.

## Usage

### Compilation

You can compile both versions using 'make'.  You need to have the modules gcc, openmpi, and rarray loaded. 

### Running

To run a test case, use 'make run'.  To run a real case use

```bash
mpirun -np <P> ./mpitimestepdistribution <log_base> <filename> <batch_size>
```

Example:
```bash
$ mpirun -np 4 ./mpitimestepdistribution 1.1 morestepnumbers.dat 100000 > histP4.dat
```

Inputs

log_base: The base of the logarithmic histogram (e.g., 1.1).

filename: Path to the data file, containing one number per line.

batch_size: Number of values to read and scatter at a time (e.g., 100000).

### Output
The printed histogram consists of two columns:

Start of log bucket

Normalized count (fraction of total)

The numeric outputs should be identical between both versions and across all process counts. Only the timing will differ.

