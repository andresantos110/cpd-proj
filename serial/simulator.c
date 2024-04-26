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

    long long neighbors_linear[9] = {
        x - 1, x, x + 1, y - 1, y, y + 1, z - 1, z, z + 1,
    };
    if (x == 0) {
        neighbors_linear[0] = cube_side - 1;
    } else if (x == cube_side - 1) {
        neighbors_linear[2] = 0;
    }
    if (y == 0) {
        neighbors_linear[3] = cube_side - 1;
    } else if (y == cube_side - 1) {
        neighbors_linear[5] = 0;
    }
    if (z == 0) {
        neighbors_linear[6] = cube_side - 1;
    } else if (z == cube_side - 1) {
        neighbors_linear[8] = 0;
    }

    long long next_x, next_y, next_z;
    for (int i = 0; i < 3; i++) {
        next_x = neighbors_linear[i];
        for (int j = 0; j < 3; j++) {
            next_y = neighbors_linear[j + 3];
            for (int k = 0; k < 3; k++) {
                next_z = neighbors_linear[k + 6];
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
    for (int j = 0; j < N_SPECIES; j++) {
        max_population[j] = current_species_count[j];
        best_generation[j] = 0;
        current_species_count[j] = 0;
    }

    long long x_linearized, y_linearized;
    for (int i = 0; i < num_generations; i++) {
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
    for (int i = 0; i < N_SPECIES; i++) {
        record[i].max_pop = max_population[i];
        record[i].biggest_gen = best_generation[i];
    }
}
