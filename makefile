FLAGS = -pg -Wall -O3 -march=native -flto -ffast-math
INCLUDES = -Iheaders

all: main

main: FileReader.o Graph.o State.o Solver.o main.o
	g++ $(FLAGS) main.o FileReader.o Graph.o State.o Solver.o -o main

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

clean:
	rm -f *.o