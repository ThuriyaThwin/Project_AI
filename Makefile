CC = gcc

CCFLAGS = -Wall

OBJ = *.o

all: main

main: main.c $(OBJ)
	$(CC) $(CCFLAGS) -o main main.c $(OBJ)

util.o: util.c
		$(CC) $(CCFLAGS) -c util.c

generator.o: generator.c
	$(CC) $(CCFLAGS) -c generator.c

backjumping.o: backjumping.c
	$(CC) $(CCFLAGS) -c backjumping.c

solver.o: solver.c
	$(CC) $(CCFLAGS) -c solver.c


.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilo
