CC=g++
CFLAGS_OBJ=-c -g -w -O2 -std=c++11
CFLAGS_EXE=-Wall -O2 -std=c++11
MYPATH=.
INCLUDE=-I$(MYPATH)/Core_Model/ -I$(MYPATH)/Core_Model/Behaviors/ -I$(MYPATH)/Interface_Library/
LDFLAGS=-lgsl -lgslcblas -lxerces-c -ltbb
SOURCES=$(wildcard $(MYPATH)/Core_Model/Behaviors/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
SRC=$(wildcard $(MYPATH)/Core_Model/*.cpp)
OBJ=$(SRC:.cpp=.o)

EXEC=sortie

$(EXEC):$(OBJECTS) $(OBJ)
	$(CC) $(MYPATH)/Core_Model/Behaviors/*.o $(MYPATH)/Interface_Library/*.o $(MYPATH)/Core_Model/*.o -o $(MYPATH)/$(EXEC) $(CFLAGS_EXE) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS_OBJ) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(OBJ)
	rm -f $(EXEC)
