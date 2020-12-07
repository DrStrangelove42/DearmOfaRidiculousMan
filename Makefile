# $@  cible
# $<  first dependency
# $^  dependencies list

CC      = g++

LIBS 	= `sdl2-config --libs` -lSDL2_ttf

CFLAGS  =  -std=c++14 `sdl2-config --cflags`
CFLAGS += -g

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard,./Source,*.cpp)
OBJ = $(SRC:.cpp=.o)

all: doarm

doarm: $(OBJ)
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f doarm
	cd Test && make clean
	
doc:
	doxygen Doc/Doxyfile

test:
	cd ./Test && make

.PHONY: clean test doc