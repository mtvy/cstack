CC=g++

CFLAGS=-c 

DBFLAGS=-c -Wall -Wextra -fsanitize=address

vlg: task valgrind

sntz:
        $(CC) $(DBFLAGS) cstack.cpp
        $(CC) $(DBFLAGS) test.cpp
        $(CC) cstack.o test.o -o task



all: task

task: cstack.o test.o

        $(CC) cstack.o test.o -o task

cstack.o: cstack.cpp

        $(CC) $(CFLAGS) cstack.cpp

test.o: test.cpp

        $(CC) $(CFLAGS) test.cpp

clean:
        rm -rf cstack.o test.o algrind-out.txt

DB:
        $(CC) $(DBFLAGS) cstack.cpp
        $(CC) $(DBFLAGS) test.cpp
        $(CC) cstack.o test.o -o task

valgrind:
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./task
