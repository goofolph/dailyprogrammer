CC=g++
CFLAGS=-g -Wall -Wextra
RM=rm -rf

all: smoosh

smoosh: smoosh.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) smoosh smoosh.exe
