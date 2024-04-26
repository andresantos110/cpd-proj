#include "io.h"

void get_input(int argc, char* argv[], int* num_generations, long long* cube_side, float* density, int* seed) {
    if (argc != 5) {
        printf("Usage: %s <num_generations> <cube_side> <density> <seed>\n", argv[0]);
        exit(1);
    }

    *num_generations = atoi(argv[1]);
    *cube_side = atoll(argv[2]);
    *density = atof(argv[3]);
    *seed = atoi(argv[4]);
}

void print_time(double exec_time) { fprintf(stderr, "%.1fs\n", exec_time); }

void print_result(Species species[]) {
    int i;
    for (i = 1; i <= N_SPECIES; i++) {
        printf("%d %lld %d\n", i, species[i - 1].max_pop, species[i - 1].biggest_gen);
    }
}
