# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
# the build target executable:
TESTPROGRAM = testQuestion2 main randomDistrib

all: $(TESTPROGRAM)

main.o : main.c
	$(CC) -c -o  $@ $< $(CFLAGS) -lm

%.o: %.c
	$(CC) -c -o  $@ $< $(CFLAGS) 

clean:
	rm -rf *.o $(TESTPROGRAM)                              