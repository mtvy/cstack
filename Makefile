CC=clang++
CFLAGS=-c

all: test

all: clean

test: test.o cstack.o
	$(CC) test.o cstack.o -o test

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

cstack.o: cstack.cpp
	$(CC) $(CFLAGS) cstack.cpp

clean:
	rm -rf *.o
