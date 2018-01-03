VPATH = ./source ./headers
CC = gcc
HEADERS = ./headers/
SRC = ./source/
OPTS = -L
LIBGRAPH = /usr/X11R6/lib
GRAPH = -lX11
DEBUG = -g
OPT := -I$(HEADERS)
SRCS := $(SRC)*.c

All:
	$(CC) $(SRCS) $(OPT) -o program $(OPTS) $(LIBGRAPH) $(GRAPH) $(DEBUG)
