CC=gcc
CFLAGS=-pedantic-errors -Wall -c
LFLAGS=-lm
SRCDIR=src
OBJDIR=obj
BLDDIR=build

all: dir juggler dejuggler

juggler: utils file juggle
	$(CC) $(LFLAGS) $(OBJDIR)/juggle.o $(OBJDIR)/utils.o $(OBJDIR)/file.o -o $(BLDDIR)/juggler

dejuggler: utils file dejuggle
	$(CC) $(LFLAGS) $(OBJDIR)/dejuggle.o $(OBJDIR)/utils.o $(OBJDIR)/file.o -o $(BLDDIR)/dejuggler

utils: $(SRCDIR)/utils.c $(SRCDIR)/blocks.h
	$(CC) $(CFLAGS) $(SRCDIR)/utils.c -o $(OBJDIR)/utils.o

file: $(SRCDIR)/file.c $(SRCDIR)/blocks.h
	$(CC) $(CFLAGS) $(SRCDIR)/file.c -o $(OBJDIR)/file.o

juggle: $(SRCDIR)/juggle.c $(SRCDIR)/blocks.h $(SRCDIR)/file.c $(SRCDIR)/utils.c
	$(CC) $(CFLAGS) $(SRCDIR)/juggle.c -o $(OBJDIR)/juggle.o

dejuggle: $(SRCDIR)/dejuggle.c $(SRCDIR)/blocks.h $(SRCDIR)/file.c $(SRCDIR)/utils.c
	$(CC) $(CFLAGS) $(SRCDIR)/dejuggle.c -o $(OBJDIR)/dejuggle.o
	
clean:
	-rm -f $(OBJDIR)/*.o
	-rm $(BLDDIR)/*

dir:
	-mkdir obj
	-mkdir build

