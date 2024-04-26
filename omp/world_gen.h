#ifndef WORLD_GEN_H
#define WORLD_GEN_H

#include <stdio.h>
#include <stdlib.h>

#define N_SPECIES 9

/**
 * @brief Generate the initial grid
 * @param grid: Pointer to the grid
 * @param cube_side: Width of the grid
 * @param density: Initial density of the grid
 * @param input_seed: Seed for the random number generator
 * @return void
 */
void gen_initial_grid(char* grid, long long cube_side, float density, int input_seed);

// char*** gen_initial_grid(long long N, float density, int input_seed);
// void print_initial_grid(char*** grid, long long cube_side);
// void print_initial_grid_continuous(char* grid, long long cube_side);

#endif
