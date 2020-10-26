# $@  cible
# $<  first dependency
# $^  dependencies list

CC      = g++

LIBS 	= -lSDL2

CFLAGS  = -Wall -Weffc++ -Wextra -Wsign-conversion `sdl2-config --cflags` #-I/usr/include/SDL2 -D_REENTRANT
CFLAGS += -g

all: doarm

doarm: main.o $(LIBS)
	$(CC) $(LDFLAGS)  $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf main
