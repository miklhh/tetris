# ------------------------------- #
# ----  Makefile for tetris  ---- #
# ------------------------------- #

CC       = g++
CFLAGS   = -O2 -Wall -Wextra -std=c++11
LINK	 = -lSDL2main -lSDL2
SOURCES  = src/draw.cpp src/exit_game.cpp src/game.cpp src/get_window_size.cpp \
           src/input.cpp src/main.cpp

build/tetris :
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) $(LINK) -o build/tetris

