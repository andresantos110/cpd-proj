#include "life3d.h"

int main(int argc, char *argv[])
{
    //TODO: processamento de argumentos de entrada (N, seed, density) - declarar no .h para serem globals?

    double exec_time;
    grid = gen_initial_grid(N, seed, density);

    exec_time = -omp_get_wtime();

    simulation();

    exec_time += omp_get_wtime();

    fprintf(stderr, "%.1fs\n", exec_time);

    print_result(); // to stdout
}

void print_result()
{

}