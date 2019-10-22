CC=g++
CFLAGS=-g -Wall -Wextra
RM=rm -rf

all: smoosh

smoosh: smoosh.cpp smorseeasy.o smorseinter.o
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) smoosh smoosh.exe *.o
