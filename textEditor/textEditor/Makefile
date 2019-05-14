EXEFILE = run
HEADERS = opObj.hpp editClass.hpp
SOURCES = opObj.cpp editClass.cpp main.cpp 
OBJECTS = opObj.o editClass.o main.o

$(EXEFILE):$(OBJECTS)
	g++ -o $@ $(OBJECTS)
	
clear:
	rm -f *.o $(EXEFILE)
	
