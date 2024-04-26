#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <omp.h>

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
 * @param cube_side The side of the cube
 * @return void
 */
void simulate(char* front_grid, char* back_grid, Species* record, int num_generations, long long cube_side);

#endif
