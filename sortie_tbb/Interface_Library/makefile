CPPFLAGS=-I../ -g3

all: Interface.o Interface.so

%.so: %.cpp
	g++ ${CPPFLAGS} -shared -c $< -o $@