# Executable Name
EXENAME = finalproj

# Object Types
OBJS = main.o src/Graph.o src/FileParser.o src/BFS.o src/Dijkstra.o src/AStar.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include make/customClangEnforcement.mk

# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

test: output_msg catch/catchmain.cpp tests/tests.cpp src/Graph.cpp src/BFS.cpp src/Dijkstra.cpp src/AStar.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp src/Graph.cpp src/BFS.cpp src/Dijkstra.cpp src/AStar.cpp -o test

clean:
	-rm -f *.o $(EXENAME) test
