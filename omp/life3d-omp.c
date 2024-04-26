#include "io.h"
#include "simulator.h"
#include "world_gen.h"

int main(int argc, char* argv[]) {
    double exec_time;

    int num_generations, seed;
    long long cube_side;
    float density;

    get_input(argc, argv, &num_generations, &cube_side, &density, &seed);

    Species species[N_SPECIES] = {0};
    char* front_grid = (char*)malloc(cube_side * cube_side * cube_side * sizeof(char));
    char* back_grid = (char*)malloc(cube_side * cube_side * cube_side * sizeof(char));
    gen_initial_grid(back_grid, cube_side, density, seed);

    exec_time = -omp_get_wtime();

    simulate(front_grid, back_grid, species, num_generations, cube_side);

    exec_time += omp_get_wtime();

    print_time(exec_time);

    print_result(species);  // to the stdout!
}
