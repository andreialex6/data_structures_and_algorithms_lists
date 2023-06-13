#Girleanu Andrei Alexandru - 313CC

EXECUTABLE = tema1

CC = gcc

CFLAGS = -Wall -Wextra -std=c11

SOURCES = tema1.c

build:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)