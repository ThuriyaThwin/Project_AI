CC = gcc

CCFLAGS = -Wall

OBJ = generator.o backjumping.o

all: main

main: main.c $(OBJ)
	$(CC) $(CCFLAGS) -o main main.c $(OBJ)

generator.o: generator.c
	$(CC) $(CCFLAGS) -c generator.c

backjumping.o: backjumping.c
	$(CC) $(CCFLAGS) -c backjumping.c


.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilo
