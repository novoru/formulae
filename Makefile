CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -std=c11 -ledit -lgc

formulae: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJS): formulae.h

test:
	make
	./formulae -test

run:
	make
	./formulae -repl

clean:
	rm -rf formulae *.o *~ tmp* a.out \#*
