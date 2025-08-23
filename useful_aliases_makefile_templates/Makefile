# Quick C Development Makefile
# Usage: make test    (compiles test.c)
#        make run     (compiles and runs)
#        make clean   (cleanup)

CC = gcc
CFLAGS = -Wall -Werror -pthread -O
DEBUGFLAGS = -Wall -Werror -pthread -g

# Default target - compile whatever .c file you're working on
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Quick test compilation
test: test.c
	$(CC) $(CFLAGS) -o test test.c

# Compile and run immediately
run: test.c
	$(CC) $(CFLAGS) -o test test.c && ./test

# Debug version
debug: test.c
	$(CC) $(DEBUGFLAGS) -o test test.c

# Cleanup
clean:
	rm -f *.o test temp_prog a.out core pzip

# For pzip specifically
pzip: pzip.c
	$(CC) $(CFLAGS) -o pzip pzip.c

.PHONY: clean run debug