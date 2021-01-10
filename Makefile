# $@  cible
# $<  first dependency
# $^  dependencies list

CXX      = g++

LIBS 	= `sdl2-config --libs` -lSDL2_ttf

CXXFLAGS  =  -std=c++14 `sdl2-config --cflags`

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard,./Source,*.cpp)
OBJ = $(SRC:.cpp=.o)

#deps
CXXFLAGS += -MMD -MP
DEPS := $(OBJ:.o=.d)

PREFIX = /usr/local

all: CXXFLAGS += -g -DDEBUG_MODE
all: doarm

doarm: $(OBJ)
	$(CXX) $(LDFLAGS)  $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f doarm
	cd Test && make clean

doc: clean
	doxygen Doc/Doxyfile

test:
	cd ./Test && make

release: clean
release: doarm

install:
	mkdir -p ~/.doarm
	cp -r Res/ ~/.doarm/
	install -m 755 doarm $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/doarm
	cp -rf ~/.doarm/*
	rmdir ~./doarm


.PHONY: clean test doc release

-include $(DEPS)
