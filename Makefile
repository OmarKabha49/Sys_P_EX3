PROG1 = main
OBF = main.o StrList.o
HEADER = StrList.h
CC = gcc
CFLAGS = -g -Wall

$(PROG1) : $(OBF)
	$(CC) $(CFLAGS) -o $(PROG1) $(OBF)


.PHONY: clean
clean:
	rm -f main.o StrList.o main 
