FLAGS = -pg -std=c++11 -Wall -O2 -march=native -flto -ffast-math
INCLUDES = -Iheaders

all: main makeTests

main: FileReader.o Graph.o State.o Solver.o main.o
	g++ $(FLAGS) main.o FileReader.o Graph.o State.o Solver.o -o main

testState: FileReader.o Graph.o State.o testState.o
	g++ $(FLAGS) testState.o FileReader.o Graph.o State.o -o testState

testGraph: FileReader.o Graph.o testGraph.o
	g++ $(FLAGS) testGraph.o FileReader.o Graph.o -o testGraph

Graph.o: headers/Graph.h source/Graph.cpp 
	g++ -c $(FLAGS) $(INCLUDES) source/Graph.cpp -o Graph.o

State.o: headers/State.h source/State.cpp 
	g++ -c $(FLAGS) $(INCLUDES) source/State.cpp -o State.o

Solver.o: headers/Solver.h source/Solver.cpp 
	g++ -c $(FLAGS) $(INCLUDES) source/Solver.cpp -o Solver.o

FileReader.o: headers/FileReader.h source/FileReader.cpp
	g++ -c $(FLAGS) $(INCLUDES) source/FileReader.cpp -o FileReader.o

main.o: main.cpp headers/Graph.h headers/State.h headers/Solver.h
	g++ -c $(FLAGS) $(INCLUDES) main.cpp -o main.o

testGraph.o: tdatest/testGraph.cpp headers/State.h headers/Graph.h headers/FileReader.h
	g++ -c $(FLAGS) $(INCLUDES) tdatest/testGraph.cpp -o testGraph.o

testState.o: tdatest/testState.cpp headers/State.h headers/FileReader.h
	g++ -c $(FLAGS) $(INCLUDES) tdatest/testState.cpp -o testState.o

makeTests: testGraph testState

clean:
	rm -f *.o testState testGraph