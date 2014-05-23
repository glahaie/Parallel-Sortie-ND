all : trees4

main.o : main.cpp
	g++ -c -g3 main.cpp

trees4 : main.o
	g++ -o ../../$@.exe -g3 main.o

clean :
	rm ../../trees4.exe main.o
