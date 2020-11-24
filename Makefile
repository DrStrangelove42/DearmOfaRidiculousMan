# $@  cible
# $<  first dependency
# $^  dependencies list

CC      = g++

LIBS 	= -lSDL2 -lSDL2_ttf

CFLAGS  = -Wsign-conversion -std=c++14 `sdl2-config --cflags` #-I/usr/include/SDL2 -D_REENTRANT #-Weffc++ -Wall  -Wextra 
CFLAGS += -g

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard,.,*.cpp)
OBJ = $(SRC:.cpp=.o)

all: doarm

doarm: $(OBJ)
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f doarm
