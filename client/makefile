.PHONY  = all clean
CC      = gcc
CFLAGS  = -ansi -Wall -W -pedantic -g
OBJ     = util.o command.o client.o main.o
BIN     = ..\client.exe

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del *.o *~ $(BIN)