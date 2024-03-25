CC = gcc
CFLAGS = -Wall  -Wextra -g -pedantic -std=c99 -O3
SOURCES = grafo.c list.c balanced_tree.c main.c adjlist.c
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
# -Werror