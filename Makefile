# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable name
TARGET = test

# Source files
SOURCES = test.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lcurl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJECTS) $(TARGET)
