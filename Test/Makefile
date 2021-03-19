CXX     = g++

LIBS 	= -lSDL2 -lSDL2_ttf -lSDL2_mixer -lcppunit

CXXFLAGS  =  -std=c++14 `sdl2-config --cflags`
CXXFLAGS += -g

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCTOTEST :=  $(call rwildcard,../Source,*.cpp)

SRC := $(call rwildcard,.,*.cpp) $(filter-out ../Source/main.cpp,$(SRCTOTEST))
OBJ = $(SRC:.cpp=.o)

#deps
CXXFLAGS += -MMD -MP
DEPS := $(OBJ:.o=.d)

all: test exec_test

test: $(OBJ)
	$(CXX) $(LDFLAGS)  $^ -o $@ $(LIBS)

exec_test:
	./test

%.o: %.cpp %.h
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f test

.PHONY: exec_test

-include $(DEPS)