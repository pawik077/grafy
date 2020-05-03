#pragma once
#include "Graph.hh"

struct Edge {
	int _origin, _destination, _weight;
};

class ListGraph : public Graph {
	Edge* _edgeArray;
public:
	void fillGraph(const bool allowLoops);
	void printGraph() const;
	const int readGraph(std::istream& in);
	void saveGraph(const int& start, std::ostream& out) const;
	const Edge* getEdgeStruct() const { return _edgeArray; }
	void addEdge(int origin, int destination, int weight, int flag);
	bool edgeExists(int origin, int destination) const;
	ListGraph(int vertices, double density):
		Graph(vertices, static_cast<int>(density*vertices*(vertices - 1)), density),
		_edgeArray(new Edge[static_cast<int>(density*vertices*(vertices - 1))]) {}
	ListGraph(): Graph() {};
	~ListGraph() { delete[] _edgeArray; }
};

