all : trees3

main.o : main.cpp
	g++ -c -g3 main.cpp

trees3 : main.o
	g++ -o ../../$@.exe -g3 main.o

clean :
	rm ../../trees3.exe main.o
