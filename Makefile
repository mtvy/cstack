CC=g++
CFLAGS=-c 
DBFLAGS=-c -Wall -Wextra -fsanitize=address

vlg: build valgrind

sntz:
        $(CC) $(DBFLAGS) cstack.cpp
        $(CC) $(DBFLAGS) test.cpp
        $(CC) cstack.o test.o -o build



all: build 

build: cstack.o test.o
        $(CC) cstack.o test.o -o build

cstack.o: cstack.cpp
        $(CC) $(CFLAGS) cstack.cpp

test.o: test.cpp
        $(CC) $(CFLAGS) test.cpp

clear:
        rm -rf cstack.o test.o

clean:
        rm -rf cstack.o test.o algrind-out.txt

DB:
        $(CC) $(DBFLAGS) cstack.cpp
        $(CC) $(DBFLAGS) test.cpp
        $(CC) cstack.o test.o -o build

valgrind:
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./build
