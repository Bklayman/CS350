TARGET=flip
CC=gcc
CFLAGS=-Wall -DBSD -DNDEBUG

all: $(TARGET)

$(TARGET): flip.o getopt.o
	$(CC) $(CFLAGS) -o flip flip.o getopt.o

flip.o: flip.c flip.h
	$(CC) $(CFLAGS) -c flip.c

getopt.o: getopt.c flip.h
	$(CC) $(CFLAGS) -c getopt.c

flip.man: flip.1
	nroff -man flip.1 > flip.man

clean:
	rm -rf *.o $(TARGET)
