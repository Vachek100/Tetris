# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -fsanitize=address -I./ `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Source files and object files
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))

# Default target
all: tetris

# Build the executable
tetris: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ_FILES) tetris

# Run the game
run: tetris
	./tetris

# Phony targets
.PHONY: all clean run
