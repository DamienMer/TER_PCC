lib.so : file.o
	g++ -fPIC -shared -o libGraph.so Arete.o Sommet.o Graphe.o Tuyau.o FordFulkerson.o CreerGraphe.o Dijkstra.o BellmanFord.o FloydWarshall.o Dmain.o

file.o : Arete.cpp Sommet.cpp Graphe.cpp Tuyau.cpp FordFulkerson.cpp CreerGraphe.cpp Dijkstra.cpp BellmanFord.cpp FloydWarshall.cpp Dmain.cpp
	g++ -o Arete.o -fPIC -c Arete.cpp
	g++ -o Sommet.o -fPIC -c Sommet.cpp
	g++ -o Graphe.o -fPIC -c Graphe.cpp
	g++ -o Tuyau.o -fPIC -c Tuyau.cpp
	g++ -o FordFulkerson.o -fPIC -c FordFulkerson.cpp
	g++ -o CreerGraphe.o -fPIC -c CreerGraphe.cpp
	
	g++ -o Dijkstra.o -fPIC -c Dijkstra.cpp
	g++ -o BellmanFord.o -fPIC -c BellmanFord.cpp
	g++ -o FloydWarshall.o -fPIC -c FloydWarshall.cpp
	g++ -o Dmain.o -fPIC -c Dmain.cpp

clean :
	rm *.so
	rm *.o
