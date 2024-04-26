#include "world_gen.h"

unsigned int seed;

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