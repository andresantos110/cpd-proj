#include "simulator.h"

char get_majority(const unsigned char* neighbors) {
    unsigned char max = 0;
    char majority = 0;

    for (int i = 1; i <= N_SPECIES; i++) {
        if (neighbors[i - 1] > max) {
            max = neighbors[i - 1];
            majority = i;
        }
    }

    return majority;
}

char next_state(const char* grid, long long x, long long y, long long z, long long cube_side) {
    long long index = x * cube_side * cube_side + y * cube_side + z;
    unsigned char neighbors[N_SPECIES] = {0};
    unsigned char count = 0;

    long long neighbors_x[3] = {x - 1, x, x + 1};
    if (x == 0) {
        neighbors_x[0] = cube_side - 1;
    } else if (x == cube_side - 1) {
        neighbors_x[2] = 0;
    }
    long long neighbors_y[3] = {y - 1, y, y + 1};
    if (y == 0) {
        neighbors_y[0] = cube_side - 1;
    } else if (y == cube_side - 1) {
        neighbors_y[2] = 0;
    }
    long long neighbors_z[3] = {z - 1, z, z + 1};
    if (z == 0) {
        neighbors_z[0] = cube_side - 1;
    } else if (z == cube_side - 1) {
        neighbors_z[2] = 0;
    }

    for (int i = 0; i < 3; i++) {
        long long next_x = neighbors_x[i];
        for (int j = 0; j < 3; j++) {
            long long next_y = neighbors_y[j];
            for (int k = 0; k < 3; k++) {
                long long next_z = neighbors_z[k];
                if (next_x == x && next_y == y && next_z == z) {
                    continue;
                }

                char neighbor = grid[next_x * cube_side * cube_side + next_y * cube_side + next_z];
                if (neighbor == 0) {
                    continue;
                }
                neighbors[neighbor - 1]++;
                count++;
            }
        }
    }

    /*long long next_x, next_y, next_z;
    for (long long dx = -1; dx <= 1; dx++) {
        next_x = x + dx;
        if (next_x < 0) {
            next_x += cube_side;
        } else if (next_x >= cube_side) {
            next_x -= cube_side;
        }

        for (long long dy = -1; dy <= 1; dy++) {
            next_y = y + dy;
            if (next_y < 0) {
                next_y += cube_side;
            } else if (next_y >= cube_side) {
                next_y -= cube_side;
            }

            for (long long dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) {
                    continue;
                }

                next_z = z + dz;
                if (next_z < 0) {
                    next_z += cube_side;
                } else if (next_z >= cube_side) {
                    next_z -= cube_side;
                }

                char neighbor = grid[next_x * cube_side * cube_side + next_y * cube_side + next_z];
                if (neighbor == 0) {
                    continue;
                }
                neighbors[neighbor - 1]++;
                count++;
            }
        }
    }*/

    if (grid[index] != 0) {
        if (count < 5 || count > 13) {
            return 0;
        } else {
            return grid[index];
        }
    } else {
        if (count > 6 && count < 11) {
            return get_majority(neighbors);
        } else {
            return 0;
        }
    }
}

void simulate(char* front_grid, char* back_grid, Species* record, int num_generations, long long cube_side) {
    long long current_species_count[N_SPECIES] = {0};
    long long max_population[N_SPECIES] = {0};
    int best_generation[N_SPECIES] = {0};

#pragma omp parallel for reduction(+ : current_species_count)
    for (long long x = 0; x < cube_side; x++) {
        for (long long y = 0; y < cube_side; y++) {
            for (long long z = 0; z < cube_side; z++) {
                char current = back_grid[x * cube_side * cube_side + y * cube_side + z];
                if (current != 0) {
                    current_species_count[current - 1]++;
                }
            }
        }
    }
#pragma omp simd
    for (int j = 0; j < N_SPECIES; j++) {
        max_population[j] = current_species_count[j];
        best_generation[j] = 0;
        current_species_count[j] = 0;
    }

    long long x_linearized, y_linearized;
    for (int i = 0; i < num_generations; i++) {
#pragma omp parallel for reduction(+ : current_species_count) private(x_linearized, y_linearized)
        for (long long x = 0; x < cube_side; x++) {
            x_linearized = x * cube_side * cube_side;
            for (long long y = 0; y < cube_side; y++) {
                y_linearized = y * cube_side;
                for (long long z = 0; z < cube_side; z++) {
                    char next = next_state(back_grid, x, y, z, cube_side);
                    front_grid[x_linearized + y_linearized + z] = next;
                    if (next != 0) {
                        current_species_count[next - 1]++;
                    }
                }
            }
        }
#pragma omp simd
        for (int j = 0; j < N_SPECIES; j++) {
            if (current_species_count[j] > max_population[j]) {
                max_population[j] = current_species_count[j];
                best_generation[j] = i + 1;
            }
            current_species_count[j] = 0;
        }

        char* temp = front_grid;
        front_grid = back_grid;
        back_grid = temp;
    }
#pragma omp simd
    for (int i = 0; i < N_SPECIES; i++) {
        record[i].max_pop = max_population[i];
        record[i].biggest_gen = best_generation[i];
    }
}
