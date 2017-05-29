# ------------------------------- #
# ----  Makefile for tetris  ---- #
# ------------------------------- #

CC       = g++
CFLAGS   = -O2 -Wall -Wextra -std=c++11
CPPFLAGS = -I/usr/include/SDL2
LINK	 = -lSDL2main -lSDL2
SOURCES  = src/draw.cpp src/exit_game.cpp src/game.cpp src/get_window_size.cpp \
           src/input.cpp src/main.cpp

build/tetris :
	mkdir -p build
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) $(LINK) -o build/tetris
