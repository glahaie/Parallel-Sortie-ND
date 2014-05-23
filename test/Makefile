CC=g++
CFLAGS_OBJ=-c -g -w -O2 -std=c++11
CFLAGS_EXE=-Wall -O2 -std=c++11
MYPATH=.
PATH_=../sortie_tbb
INCLUDE=-I$(MYPATH) -I$(MYPATH)/$(PATH_)/Core_Model/ -I$(MYPATH)/$(PATH_)/Core_Model/Behaviors/
LDFLAGS=-lgsl -lgslcblas -lxerces-c -ltbb -lcppunit
SOURCES=$(wildcard $(MYPATH)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

OBJ_1 := $(wildcard ./../sortie_tbb/Core_Model/*.o)
OBJ_2 := $(wildcard ./../sortie_tbb/Core_Model/Behaviors/*.o)
OBJ_3 := $(wildcard ./../sortie_tbb/Interface_Library/*.o)
OBJ_1 := $(filter-out ./../sortie_tbb/Core_Model/SORTIE.o, $(OBJ_1))

EXEC=Main

$(EXEC):$(OBJECTS)
	$(CC) $(MYPATH)/*.o $(OBJ_1) $(OBJ_2) -o $(MYPATH)/$(EXEC) $(CFLAGS_EXE) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS_OBJ) $(INCLUDE) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)
