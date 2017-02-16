CC = gcc

CCFLAGS = -Wall

OBJ = generator.o

all: main

main: main.c $(OBJ)
	$(CC) $(CCFLAGS) -o main main.c $(OBJ)

generator.o: generator.c
	$(CC) $(CCFLAGS) -c generator.c


.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilo
