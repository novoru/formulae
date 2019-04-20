CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -std=c11 -ledit

formulae: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJS): formulae.h

test:
	make
	./formulae -test

clean:
	rm -rf formulae *.o *~ tmp* a.out \#*
