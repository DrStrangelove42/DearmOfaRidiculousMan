# $@  cible
# $<  first dependency
# $^  dependencies list

CC      = g++

LIBS 	= -lSDL2

CFLAGS  = -Wall  -Wextra -Wsign-conversion -std=c++14 `sdl2-config --cflags` #-I/usr/include/SDL2 -D_REENTRANT #-Weffc++
CFLAGS += -g

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJ = $(SRC:.cpp=.o)

all: doarm

doarm: $(OBJ) 
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf doarm
