#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

#define N_SPECIES 9

typedef struct {
    int biggest_gen;
    long long max_pop;
} Species;

/**
 * @brief Simulate the evolution of the grid
 * @param front_grid The next grid
 * @param back_grid The previous grid
 * @param record The record of every species
 * @param num_generations The number of generations to simulate
 * @param x_side The side of the x-axis
 * @param slice_side The side of the slice
 * @param pid OpenMPI process ID
 * @param worldsize Number of MPI processes
 * @return void
 */
void simulate(char* front_grid, char* back_grid, Species* record, int num_generations, long long x_side, long long slice_side, int pid, int worldsize);

#endif
