all : trees5

main.o : main.cpp
	g++ -c -g3 main.cpp

trees5 : main.o
	g++ -o ../../$@.exe -g3 main.o

clean :
	rm ../../trees5.exe main.o
