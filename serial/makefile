.PHONY  = all clean
CC      = gcc
CFLAGS  = -ansi -Wall -W -pedantic -g -c
OBJ     = serial.o

all: $(OBJ)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	-del *.o *~