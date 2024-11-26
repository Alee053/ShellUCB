all: main

CXX = g++
override CXXFLAGS += -Wall

SRCS = $(shell find . -maxdepth 1 -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -maxdepth 1 -type f -name '*.hpp' -print)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o myshell