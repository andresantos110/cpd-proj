#ifndef LIFE3D_IO_H
#define LIFE3D_IO_H

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

/**
 * @brief Read the simulation configuration from the command line
 * @param argc: Main's argc
 * @param argv: Main's argv
 * @param num_generations: Number of generations to simulate
 * @param cube_side: Width of the grid
 * @param density: Initial density of the grid
 * @param seed: Seed for the random number generator
 * @return void
 */
void get_input(int argc, char* argv[], int* num_generations, long long* cube_side, float* density, int* seed);

/**
 * @brief Print the execution time of the simulation
 * @param exec_time: Time in seconds
 * @return void
 */
void print_time(double exec_time);

/**
 * @brief Print the result of the simulation
 * @param species: Array of Species
 * @return void
 */
void print_result(Species species[]);

#endif
