#pragma once
#include "Graph.hh"
#include <memory>

class MatrixGraph : public Graph {
	std::unique_ptr<std::unique_ptr<int[]>[]> _adjacencyMatrix;
public:
	void fillGraph(const bool allowLoops);
	void printGraph() const;
	const int readGraph(std::istream& in);
	void saveGraph(const int& start, std::ostream& out) const;
	const int& getWeight(int i, int j) const { return _adjacencyMatrix[i][j]; }
	MatrixGraph(int vertices, double density);
	MatrixGraph(): Graph() {};
};

