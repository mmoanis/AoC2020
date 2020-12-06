SRC := $(patsubst %.cpp, %.out, $(wildcard *.cpp))

all: $(SRC)

clean:
	rm -rf *.out

%.out: %.cpp
	clang++ -std=c++14 -o $@ $^


