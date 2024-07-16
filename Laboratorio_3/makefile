all: multithread forkjoin

multithread:
	javac Laberinto.java SolverThread.java
	java SolverThread

forkjoin:
	javac Laberinto.java MazeSolver.java
	java MazeSolver

clean:
	rm *.class
