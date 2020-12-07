CC      = g++

LIBS 	= -lSDL2 -lSDL2_ttf -lcppunit

CFLAGS  =  -std=c++14 `sdl2-config --cflags`
CFLAGS += -g

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCTOTEST :=  $(call rwildcard,../Source,*.cpp)
SRC := $(call rwildcard,.,*.cpp) $(filter-out ../Source/main.cpp,$(SRCTOTEST))
OBJ = $(SRC:.cpp=.o)

all: test exec_test

test: $(OBJ)
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)

exec_test:
	./test

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f test

.PHONY: exec_test