#include "BellmanFord.hh"
static const int inf = 1000000;

void printSolution(std::string path[], int distance[], int vertices, int start, std::ostream& out) {
	out << "Bellman-Ford algorithm solution\n";
	out << "The starting node was -> " << start << "\n";
	for(int vertex = 0; vertex < vertices; ++vertex) {
		if(distance[vertex] == -inf) {
			out << vertex << "->" << "-inf\n";
			continue;
		} else if(distance[vertex] == inf) {
			out << vertex << "->" << "inf\n";
			continue;
		} else
			out << vertex << "->" << distance[vertex];
		if(vertex < 10)
			out << "   ";
		else if(vertex < 100)
			out << "  ";
		else
			out << " ";
		if((distance[vertex] >= 100 && distance[vertex] < 1000) || (-100 > distance[vertex] && distance[vertex] < -10))
			out << " The shortest path: " << path[vertex] << vertex;
		else if(0 <= distance[vertex] && distance[vertex] < 10)
			out << "   The shortest path: " << path[vertex] << vertex;
		else if((distance[vertex] >= 10 && distance[vertex] < 100) || (-10 < distance[vertex] && distance[vertex] < 0))
			out << "  The shortest path: " << path[vertex] << vertex;
		else
			out << "The shortest path: " << path[vertex] << vertex;
		out << std::endl;
	}
	if(&out != &std::cout)
		delete(&out);
}

double bellmanFord(std::shared_ptr<MatrixGraph> graph, int start, bool printOutput, std::ostream& out) {
	std::string* path = new std::string[graph->getVertices()];
	std::chrono::time_point<std::chrono::steady_clock> tStart, tEnd;
	tStart = std::chrono::high_resolution_clock::now();
	int* distance = new int[graph->getVertices()];
	for(int vertex = 0; vertex < graph->getVertices(); ++vertex)
		distance[vertex] = inf;
	distance[start] = 0;
	for(int i = 1; i < graph->getVertices(); ++i) {
		for(int row = 0; row < graph->getVertices(); ++row) {
			for(int col = 0; col < graph->getVertices(); ++col) {
				int origin = row;
				int destination = col;
				int weight = graph->getWeight(row, col);
				if(distance[origin] + weight < distance[destination]) {
					distance[destination] = distance[origin] + weight;
					if(printOutput) {
						path[destination].clear();
						path[destination].append(path[origin] + std::to_string(origin) + "->");
					}
				}
			}
		}
	}
	//checking for negative cycles
	for(int i = 1; i < graph->getVertices(); ++i) {
		for(int row = 0; row < graph->getVertices(); ++row) {
			for(int col = 0; col < graph->getVertices(); ++col) {
				int origin = row;
				int destination = col;
				int weight = graph->getWeight(row, col);
				if(distance[origin] + weight < distance[destination]) {
					if(distance[origin] > inf / 2) distance[origin] = inf;
					else if(weight == inf) continue;
					else distance[destination] = -inf;
				}
				else if(distance[origin] > inf / 2) distance[origin] = inf;
			}
		}
	}
	tEnd = std::chrono::high_resolution_clock::now();
	if(printOutput)
		printSolution(std::move(path), std::move(distance), graph->getVertices(), start, out);
	delete[] distance;
	delete[] path;
	return std::chrono::duration<double, std::milli>(tEnd - tStart).count();
}

double bellmanFord(std::shared_ptr<ListGraph> graph, int start, bool printOutput, std::ostream& out) {
	std::string* path = new std::string[graph->getVertices()];
	std::chrono::time_point<std::chrono::steady_clock> tStart, tEnd;
	tStart = std::chrono::high_resolution_clock::now();
	int* distance = new int[graph->getVertices()];
	for(int vertex = 0; vertex < graph->getVertices(); ++vertex)
		distance[vertex] = inf;
	distance[start] = 0;
	for(int vertex = 1; vertex < graph->getVertices(); ++vertex) {
		for(int edge = 0; edge < graph->getEdges(); ++edge) {
			int origin = graph->getEdgeStruct()[edge]._origin;
			int destination = graph->getEdgeStruct()[edge]._destination;
			int weight = graph->getEdgeStruct()[edge]._weight;
			if(distance[origin] + weight < distance[destination]) {
				distance[destination] = distance[origin] + weight;
				if(printOutput) {
					path[destination].clear();
					path[destination].append(path[origin] + std::to_string(origin) + "->");
				}
			}
		}
	}
	//checking for negative cycles
	for(int vertex = 1; vertex < graph->getVertices(); ++vertex) {
		for(int edge = 0; edge < graph->getEdges(); ++edge) {
			int origin = graph->getEdgeStruct()[edge]._origin;
			int destination = graph->getEdgeStruct()[edge]._destination;
			int weight = graph->getEdgeStruct()[edge]._weight;
			if(distance[origin] + weight < distance[destination]) {
				if(distance[origin] > inf / 2) distance[origin] = inf;
				else distance[destination] = -inf;
			}
			else if(distance[origin] > inf / 2) distance[origin] = inf;
		}
	}
	tEnd = std::chrono::high_resolution_clock::now();
	if(printOutput)
		printSolution(std::move(path), std::move(distance), graph->getVertices(), start, out);
	delete[] distance;
	delete[] path;
	return std::chrono::duration<double, std::milli>(tEnd - tStart).count();
}
