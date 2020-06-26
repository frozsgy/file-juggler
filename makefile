CC=gcc
CFLAGS=-pedantic-errors -Wall
LFLAGS=-lm
SRCDIR=src

all: $(SRCDIR)/*.c 
	$(CC) $(LFLAGS) $(SRCDIR)/*.c -o juggle
	
clean:
	-rm -f *.o
	-rm juggle

