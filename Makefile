# $@  cible
# $<  first dependency
# $^  dependencies list

CC      = g++

LIBS 	= -lSDL2

CFLAGS  = -Wall -Weffc++ -Wextra -Wsign-conversion `sdl2-config --cflags` #-I/usr/include/SDL2 -D_REENTRANT
CFLAGS += -g

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJ = $(SRC:.cpp=.o)

all: main

main: $(OBJ) 
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf main
