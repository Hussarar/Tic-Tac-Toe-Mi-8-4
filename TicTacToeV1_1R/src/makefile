IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lncurses -lpdcurses

_DEPS = gamevisuals.h gamelogic.h color.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o gamevisuals.o gamelogic.o color.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TicTacToe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 