# Flags de compilation
CC=gcc
CFLAGS= -Wall
LDFLAGS= -lpthread

# Pour faire de chaque .c un programme
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c,%,$(SRCS))

.PHONY: clean mrproper

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(BINS)