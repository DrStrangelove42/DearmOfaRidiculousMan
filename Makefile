# $@  cible
# $<  first dependency
# $^  dependencies list

CXX      = g++

LIBS 	= `sdl2-config --libs` -lSDL2_ttf

CXXFLAGS  =  -std=c++14 `sdl2-config --cflags`

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard,./Source,*.cpp)
OBJ = $(SRC:.cpp=.o)

all: CXXFLAGS += -g
all: doarm

doarm: $(OBJ)
	$(CXX) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	rm -f doarm
	cd Test && make clean
	
doc:
	doxygen Doc/Doxyfile

test:
	cd ./Test && make

release: doarm

.PHONY: clean test doc release