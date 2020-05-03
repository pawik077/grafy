#include "MatrixGraph.hh"
static const int inf = 1000000;

MatrixGraph::MatrixGraph(int vertices, double density):
	Graph(vertices, static_cast<int>(density * vertices * (vertices - 1)), density), //density=(max edges)/(vertices*(vertrices-1))
	_adjacencyMatrix(std::make_unique<std::unique_ptr<int[]>[]>(vertices)) {

	for (int row = 0; row < _vertices; ++row) {
		_adjacencyMatrix[row] = std::make_unique<int[]>(vertices);
		for (int col = 0; col < _vertices; ++col) {
			if (row == col) _adjacencyMatrix[row][col] = 0;
			else _adjacencyMatrix[row][col] = inf;
		}
	}
}

void MatrixGraph::fillGraph(const bool allowLoops) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> weightDist(0, 50);
	if (_density == 1) {
		for (int row = 0; row < _vertices; ++row) {
			for (int col = 0; col < _vertices; ++col) {
				if (row != col) {
					int weight = weightDist(gen);
					while (weight == 0) weight = weightDist(gen);
					_adjacencyMatrix[row][col] = weight;
				}
			}
		}
	} else {
		int edges = _edges;
		std::uniform_int_distribution<int> nodeDist(0, _vertices - 1);
		while (edges) {
			int row = nodeDist(gen);
			int col = nodeDist(gen);
			if (_adjacencyMatrix[row][col] == 0 || _adjacencyMatrix[row][col] == inf) {
				int weight;
				do
					weight = weightDist(gen);
				while(weight == 0);
				if (row != col) {
					_adjacencyMatrix[row][col] = weight;
					--edges;
				} else if(allowLoops) {
					_adjacencyMatrix[row][col] = weight;
					--edges;
				}
			}
		}
	}
}

void MatrixGraph::printGraph() const {
	std::cout << "Adjacency matrix:\n";
	for (int i = 0; i < _vertices; ++i) {
		if (i <= 10) std::cout << "    " << i;
		else if (i <= 100) std::cout << "   " << i;
		else std::cout << "  " << i;
	}
	std::cout << "\n";
	for (int row = 0; row < _vertices; ++row) {
		std::cout << row;
		if (row <= 10) std::cout << "   ";
		else if (row <= 100) std::cout << "  ";
		else std::cout << " ";
		for (int col = 0; col < _vertices; ++col) {
			int weight = _adjacencyMatrix[row][col];
			if (weight == inf) std::cout << "*";
			else std::cout << weight;
			if (abs(weight) < 10 || abs(weight) == inf) std::cout << "    ";
			else if (abs(weight) < 100) std::cout << "   ";
			else std::cout << "  ";
			if (weight < 0) std::cout << '\b';
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

const int MatrixGraph::readGraph(std::istream& in) {
	int start, origin, destination, weight;
	in >> _edges >> _vertices >> start;
	_adjacencyMatrix = std::make_unique<std::unique_ptr<int[]>[]>(_vertices);
	for (int row = 0; row < _vertices; ++row) {
		_adjacencyMatrix[row] = std::move(std::make_unique<int[]>(_vertices));
		for (int col = 0; col < _vertices; ++col) {
			if (row == col) _adjacencyMatrix[row][col] = 0;
			else _adjacencyMatrix[row][col] = inf;
		}
	}
	for (int edge = 0; edge < _edges; ++edge) {
		in >> origin >> destination >> weight;
		_adjacencyMatrix[origin][destination] = weight;
	}
	return start;
}

void MatrixGraph::saveGraph(const int& start, std::ostream& out) const {
	out << _edges << " " << _vertices << " " << start << "\n";
	for (int row = 0; row < _vertices; ++row) {
		for (int col = 0; col < _vertices; ++col) {
			if (_adjacencyMatrix[row][col] != inf && _adjacencyMatrix[row][col] != 0)
				out << row << " " << col << " " << _adjacencyMatrix[row][col] << "\n";
		}
	}
}