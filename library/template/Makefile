CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wshadow -pedantic

all: main
.PHONY: all

main: main.cpp dbg.h
	g++ $(CXXFLAGS) main.cpp -o main

stupid: stupid.cpp dbg.h
	g++ $(CXXFLAGS) stupid.cpp -o stupid 

debug: main.cpp dbg.h
	g++ $(CXXFLAGS) -DLOCAL -g main.cpp -o main
.PHONY: debug

clean:
	rm -rf main.dSYM main
.PHONY: clean
