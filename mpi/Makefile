OBJS	= io.o simulator.o world_gen.o
SOURCE	= io.c simulator.c world_gen.c life3d-mpi.c
HEADER	= io.h simulator.h world_gen.h
OUT	= life3d-mpi
CC	 = mpicc
FLAGS	 = -O2 -fopenmp

all: life3d-mpi io.o simulator.o world_gen.o
	
life3d-mpi: life3d-mpi.c $(OBJS)
	$(CC) $(FLAGS) life3d-mpi.c io.o simulator.o world_gen.o -o life3d-mpi

io.o: io.c
	$(CC) $(FLAGS) -c io.c -o io.o
	
simulator.o: simulator.c
	$(CC) $(FLAGS) -c simulator.c -o simulator.o

world_gen.o: world_gen.c
	$(CC) $(FLAGS) -c world_gen.c -o world_gen.o

clean:
	rm -f $(OBJS) $(OUT)
