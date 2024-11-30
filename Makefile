# Alejandro Castro, Santiago Mendoza, Sebastian Arce, Daniel Gamarra - Proyecto Sistemas Operativos 1
# Arquitectura Computacional y Sistemas Operativos tutor: Estefany Castellon

all: main

CXX = g++
override CXXFLAGS += -Wall -Wno-ignored-attributes


SRCS = $(shell find . -maxdepth 1 -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -maxdepth 1 -type f -name '*.hpp' -print)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o myshell