# ------------------- #
# Makefile for tetris #
# ------------------- #

CC       = g++
CFLAGS   = -O2 -Wall -Wextra 
SOURCES  = src/draw.cpp src/exit_game.cpp src/game.cpp src/get_window_size.cpp \
           src/input.cpp src/main.cpp

build/tetris :
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) -o build/tetris

