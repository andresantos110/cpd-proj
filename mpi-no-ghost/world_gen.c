#include "world_gen.h"

unsigned int seed;

/**
 * @brief: Mathematically-correct modulo function
 * @param a: Dividend
 * @param b: Divisor
 * @return: The remainder of the division
 */
unsigned long long modulo(long long a, long long b) {
    int result = (a + b) % b;
    return result;
}

void init_r4uni(int input_seed) { seed = input_seed + 987654321; }

float r4_uni() {
    int seed_in = seed;

    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);

    return 0.5 + 0.2328306e-09 * (seed_in + (int)seed);
}

void gen_initial_grid(char* grid, long long cube_side, float density, int input_seed) {
    int x, y, z;

    init_r4uni(input_seed);
    for (x = 0; x < cube_side; x++)
        for (y = 0; y < cube_side; y++)
            for (z = 0; z < cube_side; z++)
                if (r4_uni() < density) grid[x * cube_side * cube_side + y * cube_side + z] = (int)(r4_uni() * N_SPECIES) + 1;
}
void gen_initial_row(const char* grid, char* row, long long cube_side, long long global_start_x, long long local_width) {
    long long x, y, z;

    for (x = -1; x < local_width + 1; x++) {
        long long normalized_x = modulo(x + global_start_x, cube_side);
        for (y = 0; y < cube_side; y++) {
            long long normalized_y = modulo(y, cube_side);
            for (z = 0; z < cube_side; z++) {
                long long normalized_z = modulo(z, cube_side);
                row[(x + 1) * cube_side * cube_side + y * cube_side + z] =
                    grid[normalized_x * cube_side * cube_side + normalized_y * cube_side + normalized_z];
            }
        }
    }
}

// ------- Old 3d array logic -------

/*void print_initial_grid(char*** grid, long long cube_side) {
    FILE* file = fopen("initial_grid.txt", "w");
    int x, y, z;

    for (x = 0; x < cube_side; x++) {
        fprintf(file, "Layer %d:\n", x);
        for (y = 0; y < cube_side; y++) {
            for (z = 0; z < cube_side; z++) fprintf(file, "%d ", grid[x][y][z]);
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

char*** gen_initial_grid(long long cube_side, float density, int input_seed) {
    int x, y, z;

    char*** grid = (char***)malloc(cube_side * sizeof(char**));
    if (grid == NULL) {
        printf("Failed to allocate matrix\n");
        exit(1);
    }
    for (x = 0; x < cube_side; x++) {
        grid[x] = (char**)malloc(cube_side * sizeof(char*));
        if (grid[x] == NULL) {
            printf("Failed to allocate matrix\n");
            exit(1);
        }
        grid[x][0] = (char*)calloc(cube_side * cube_side, sizeof(char));
        if (grid[x][0] == NULL) {
            printf("Failed to allocate matrix\n");
            exit(1);
        }
        for (y = 1; y < cube_side; y++) grid[x][y] = grid[x][0] + y * cube_side;
    }

    init_r4uni(input_seed);
    for (x = 0; x < cube_side; x++)
        for (y = 0; y < cube_side; y++)
            for (z = 0; z < cube_side; z++)
                if (r4_uni() < density) grid[x][y][z] = (int)(r4_uni() * N_SPECIES) + 1;

    return grid;
}

void print_initial_grid_continuous(char* grid, long long cube_side) {
    FILE* file = fopen("initial_grid_continuous.txt", "w");
    int x, y, z;

    for (x = 0; x < cube_side; x++) {
        fprintf(file, "Layer %d:\n", x);
        for (y = 0; y < cube_side; y++) {
            for (z = 0; z < cube_side; z++) fprintf(file, "%d ", grid[x * cube_side * cube_side + y * cube_side + z]);
            fprintf(file, "\n");
        }
    }
}*/
