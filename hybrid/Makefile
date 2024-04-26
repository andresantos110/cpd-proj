OBJS	= io.o simulator.o world_gen.o
SOURCE	= io.c simulator.c world_gen.c life3d.c
HEADER	= io.h simulator.h world_gen.h
OUT	= life3d-hybrid
CC	 = mpicc
FLAGS	 = -O2 -fopenmp -g

all: life3d-hybrid io.o simulator.o world_gen.o
	
life3d-hybrid: life3d-hybrid.c $(OBJS)
	$(CC) $(FLAGS) life3d-hybrid.c io.o simulator.o world_gen.o -o life3d-hybrid

io.o: io.c
	$(CC) $(FLAGS) -c io.c -o io.o
	
simulator.o: simulator.c
	$(CC) $(FLAGS) -c simulator.c -o simulator.o

world_gen.o: world_gen.c
	$(CC) $(FLAGS) -c world_gen.c -o world_gen.o

clean:
	rm -f $(OBJS) $(OUT)
