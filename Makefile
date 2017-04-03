CC = gcc

CCFLAGS = -Wall

OBJ = util.o generator.o backjumping.o

all: main

main: main.c $(OBJ)
	$(CC) $(CCFLAGS) -o main main.c $(OBJ)

util.o: util.c
		$(CC) $(CCFLAGS) -c util.c

generator.o: generator.c
	$(CC) $(CCFLAGS) -c generator.c

backjumping.o: backjumping.c
	$(CC) $(CCFLAGS) -c backjumping.c



.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilo
