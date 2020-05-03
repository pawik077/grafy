#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>

class Graph {
protected:
	int _vertices, _edges;
	double _density;
public:
	int getVertices() const { return _vertices; }
	int getEdges() const { return _edges; }
	virtual void fillGraph(const bool allowLoops) = 0;
	virtual void printGraph() const = 0;
	virtual const int readGraph(std::istream& in) = 0;
	virtual void saveGraph(const int& start, std::ostream& out) const = 0;
	virtual ~Graph() {};
	Graph() {};
	Graph(int vertices, int edges, double density) { _vertices = vertices; _edges = edges; _density = density; }
};