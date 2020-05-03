#include "ListGraph.hh"

void ListGraph::fillGraph(const bool allowLoops) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> weightDist(0, 50);
	if(_density == 1) {
		int flag = 0;
		for(int origin = 0; origin < _vertices; ++origin) {
			for(int destination = 0; destination < _vertices; ++destination) {
				if(origin != destination) {
					int weight = weightDist(gen);
					while(weight == 0) 
						weight = weightDist(gen);
					addEdge(origin, destination, weight, flag++);
				}
			}
		}
	} else {
		int edges = 0;
		std::uniform_int_distribution<int> nodeDist(0, _vertices - 1);
		while(edges < _edges) {
			int origin = nodeDist(gen);
			int destination = nodeDist(gen);
			if(!edgeExists(origin, destination)) {
				int weight;
				do 
					weight = weightDist(gen);
				while(weight == 0);
				if(origin != destination) addEdge(origin, destination, weight, edges++);
				else if(allowLoops) addEdge(origin, destination, weight, edges++);
			}
		}
	}
}

void ListGraph::printGraph() const {
	std::cout << "Adjacency list:\n";
	for(int origin = 0; origin < _vertices; ++origin) {
		std::cout << origin;
		for(int edge = 0; edge < _edges; ++edge) {
			if(_edgeArray[edge]._origin == origin)
				std::cout << "->[" << _edgeArray[edge]._destination << "|" << _edgeArray[edge]._weight << "]";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

const int ListGraph::readGraph(std::istream& in) {
	int start, origin, destination, weight;
	in >> _edges >> _vertices >> start;
	_edgeArray = new Edge[_edges];
	for(int edge = 0; edge < _edges; ++edge) {
		in >> origin >> destination >> weight;
		addEdge(origin, destination, weight, edge);
	}
	return start;
}

void ListGraph::saveGraph(const int& start, std::ostream& out) const {
	out << _edges << " " << _vertices << " " << start << "\n";
	for(int edge = 0; edge < _edges; ++edge)
		out << _edgeArray[edge]._origin << " " << _edgeArray[edge]._destination << " " << _edgeArray[edge]._weight << "\n";
}

void ListGraph::addEdge(int origin, int destination, int weight, int flag) {
	_edgeArray[flag]._origin = origin;
	_edgeArray[flag]._destination = destination;
	_edgeArray[flag]._weight = weight;
}

bool ListGraph::edgeExists(int origin, int destination) const {
	for(int edge = 0; edge < _edges; ++edge)
		if(_edgeArray[edge]._origin == origin && _edgeArray[edge]._destination == destination) return true;
	return false;
}
