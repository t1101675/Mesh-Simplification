CC = g++
OPT =
CFLAGS = -Wall -std=c++11 $(OPT)
LDFLAGS = -Wall
LDLIBS = $(LDFLAGS)


TARGETS = main
OBJECTS = main.o mesh.o vertex.o face.o heap.o mat4.o pair.o vec3.o vec4.o 
HEADERS = mesh.h vertex.h
HPPS = vec3.hpp vec4.hpp pair.hpp mat4.hpp heap.hpp face.hpp

.PHONY: default
default: all

.PHONY: all
all: $(TARGETS)
main: main.o mesh.o vertex.o
	$(CC) -o $@ $^ $(LDLIBS)

%.o: %.cpp $(HEADERS) $(HPPS)
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.hpp $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o main

.PHONY: clean
clean:
	rm -rf $(TARGETS) $(OBJECTS)