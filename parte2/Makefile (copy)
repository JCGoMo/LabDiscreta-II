CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -pedantic -std=c99 -O3 -DNDEBUG -fsanitize=address,undefined
SOURCES = grafo.c list.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = ejecutable

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) 
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ 
clean:
	$(RM) $(OBJECTS) $(TARGET)
