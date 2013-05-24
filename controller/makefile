.PHONY  = all clean
CC      = gcc
CFLAGS  = -ansi -Wall -W -pedantic -g
INCDIR  = ..\serial
OBJ     = controller.o main.o
BIN     = ..\controller.exe

all: $(OBJ)
	$(CC) -I$(INCDIR) $(CFLAGS) $(INCDIR)\serial.o $(OBJ) -o $(BIN)

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

clean:
	-del *.o *~ $(BIN)