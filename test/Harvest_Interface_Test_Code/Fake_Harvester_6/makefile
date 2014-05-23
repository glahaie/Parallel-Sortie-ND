all : trees6

main.o : main.cpp
	g++ -c -g3 main.cpp

trees6 : main.o
	g++ -o ../../$@.exe -g3 main.o

clean :
	rm ../../trees6.exe main.o
