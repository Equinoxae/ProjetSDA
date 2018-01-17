VPATH = ./source ./headers
CC = gcc
HEADERS = ./headers/
SRC = ./source/
OPTS = -L
LIBGRAPH = /usr/X11R6/lib
MATH = -lm
GRAPH = -lX11
DEBUG = -O3 -Wall
OPT := -I$(HEADERS)
SRCS := $(SRC)*.c

All:
	$(CC) $(SRCS) $(OPT) -o program $(MATH) $(OPTS) $(LIBGRAPH) $(GRAPH) $(DEBUG)


install:
	sudo apt-get install libx11-dev

rect:
	./program -r -d -h 200 -l 200 -Dd -Ad

rectl:
	./program -r -v -h 200 -l 200 -g 0.0002 -linear

rectm:
	./program -r -v -h 20 -l 20 -cw 15 -M

carre1:
	./program -c -d -h 20 -l 20 -Dd -Ad -making 1

carre2:
	./program -c -d -h 20 -l 20 -Dd -Ad -making 2

hexa:
	./program -x -d -h 20 -l 20 -Dd -Ad -slowr	

hexal:
	./program -x -d -h 30 -l 30 -linear

hexam:
	./program -x -v -h 15 -l 15 -M

cercle1:
	./program -C -d -h 10 -l 30

cercle2:
	./program -C -v -h 20 -l 90 -cw 15

