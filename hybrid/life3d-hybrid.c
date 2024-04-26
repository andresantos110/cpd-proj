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

    int pid;
    int world_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    long long local_width = cube_side / world_size + 4;
    long long remainder = cube_side % world_size;
    if (pid < remainder) {
        local_width++;
    }
    long long start_x = pid * (long long)(cube_side / world_size) + (pid < remainder ? pid : remainder);

    char* grid = (char*)calloc(cube_side * cube_side * cube_side, sizeof(char));
    char* front_row = (char*)calloc(local_width * cube_side * cube_side, sizeof(char));
    char* back_row = (char*)calloc(local_width * cube_side * cube_side, sizeof(char));
    
    gen_initial_grid(grid, cube_side, density, seed);
    gen_initial_row(grid, back_row, cube_side, start_x, local_width - 4);

    // for(int i = 0; i < 64; i++){
    //     printf("initial grid: %d\n", grid[i]);
    // }
    // for(int i = 0; i < 64; i++){
    //     printf("initial rows: %d\n", back_row[i]);
    // }

    exec_time = -omp_get_wtime();

    simulate(front_row, back_row, species, num_generations, local_width, cube_side, pid, world_size);

    exec_time += omp_get_wtime();

    MPI_Finalize();

    if(pid == 0){
        print_time(exec_time);

        print_result(species);  // to the stdout!
    }

    free(grid);
    free(front_row);
    free(back_row);

    return 0;
}
