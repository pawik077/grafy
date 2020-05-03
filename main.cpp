#include <iostream>
#include "BellmanFord.hh"

template<class T>
void tests(std::ostream& out) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	int sizes[] = {10, 50, 100, 200, 500};
	double densities[] = {0.25, 0.5, 0.75, 1};
	int loops = 100;
	for(int vertices : sizes) {
		out << "\n** Number of graph vertices: " << vertices << "\n";
		std::uniform_int_distribution<int> dist(0, vertices - 1);
		for(double density : densities) {
			out << "\n* Graph density: " << density * 100 << "%\n";
			double sum = 0;
			for(int i = 0; i < loops; ++i) {
				std::shared_ptr<T> graph = std::make_shared<T>(vertices, density);
				int start = dist(gen);
				graph->fillGraph(true);
				sum += bellmanFord(std::move(graph), start, false);
				std::cout << (i * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			out << sum / loops << "\n";
			std::cout << "Finished solving graphs with " << vertices << " vertices and " << density * 100 << "% density\n";
		}
	}
}

int main() {
	int op = -1;
	std::shared_ptr<ListGraph> listGraph;
	std::shared_ptr<MatrixGraph> matrixGraph;
	int start = 0;
	int currentGraphType = 0;
	do {
		std::cout << "MENU:\n";
		std::cout << "1 - Generate graphs\n";
		std::cout << "2 - Read graph from file\n";
		std::cout << "3 - Save graph to file\n";
		std::cout << "4 - Print graph to stdout\n";
		std::cout << "5 - Solve currently loaded graph with Bellman-Ford algorithm\n";
		std::cout << "6 - Test Bellman Ford Algorithm\n";
		std::cout << "0 - Exit\n";
		std::cout << "Your choice: ";
		std::cin >> op;
		while(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			op = -1;
		}
		switch(op) {
			case 1: {
				int op = -1;
				int vertices;
				double density;
				std::string a = "";
				bool loops;
				std::random_device rd;
				std::default_random_engine gen(rd());
				std::cout << "Choose graph type (1 - ListGraph, 2 - MatrixGraph): ";
				std::cin >> op;
				while(std::cin.fail() || op != 1 && op != 2) {
					std::cerr << "Wrong graph type!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Choose graph type (1 - ListGraph, 2 - MatrixGraph): ";
					std::cin >> op;
				}
				std::cout << "Number of vertices? ";
				std::cin >> vertices;
				while(std::cin.fail() || vertices < 1) {
					std::cerr << "Wrong number of vertices!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Number of vertices? ";
					std::cin >> vertices;
				}
				std::cout << "Density of the graph? ";
				std::cin >> density;
				while(std::cin.fail()) {
					std::cerr << "Wrong graph density!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Density of the graph (%)? ";
					std::cin >> density;
				}
				std::cout << "Allow loops (Y/n)? ";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				getline(std::cin, a);
				while(std::cin.fail() || a[0] != 'y' && a[0] != 'Y' && a[0] != 't' && a[0] != 'T' && a[0] != 'n' && a[0] != 'N' && a != "") {
					std::cout << "Incorrect option!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					a = "";
					std::cout << "Allow loops (Y/n)? ";
					getline(std::cin, a);
				}
				switch(a[0]) {
					case 'y':
					case 'Y':
					case 't':
					case 'T':
					case '\0':
						loops = true;
						break;
					case 'n':
					case 'N':
						loops = false;
						break;
				}
				std::uniform_int_distribution<int> dist(0, (vertices - 1));
				start = dist(gen);
				switch(op) {
					case 1:
						listGraph = std::make_shared<ListGraph>(vertices, density / 100);
						listGraph->fillGraph(loops);
						currentGraphType = 1;
						break;
					case 2:
						matrixGraph = std::make_shared<MatrixGraph>(vertices, density / 100);
						matrixGraph->fillGraph(loops);
						currentGraphType = 2;
						break;
				}
				break;
			}
			case 2: {
				std::string fileName;
				int graphType;
				std::cout << "Input file name? ";
				std::cin >> fileName;
				std::ifstream file(fileName);
				while(std::cin.fail() || !file.is_open()) {
					std::cerr << "Incorrect file name!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Input file name? ";
					std::cin >> fileName;
					file.open(fileName);
				}
				std::cout << "Graph type (1 - ListGraph, 2 - MatrixGraph)? ";
				std::cin >> graphType;
				while(std::cin.fail() || graphType != 1 && graphType != 2) {
					std::cerr << "Incorrect graph type!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Graph type (1 - ListGraph, 2 - MatrixGraph)? ";
					std::cin >> graphType;
				}
				currentGraphType = graphType;
				switch(graphType) {
					case 1:
						listGraph = std::make_shared<ListGraph>();
						start = listGraph->readGraph(file);
						break;
					case 2:
						matrixGraph = std::make_shared<MatrixGraph>();
						start = matrixGraph->readGraph(file);
						break;
				}
				break;
			}
			case 3: {
				if(currentGraphType == 0) {
					std::cerr << "No graph currently loaded!" << std::endl;
					break;
				}
				std::string fileName;
				std::cout << "Output file name? ";
				std::cin >> fileName;
				std::ofstream file(fileName);
				while(std::cin.fail() || !file.is_open()) {
					std::cerr << "Incorrect file name!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Output file name? ";
					std::cin >> fileName;
					file.open(fileName);
				}
				switch(currentGraphType) {
					case 1:
						listGraph->saveGraph(start, file);
						break;
					case 2:
						matrixGraph->saveGraph(start, file);
						break;
				}
				break;
			}
			case 4:
				switch(currentGraphType) {
					case 0:
						std::cerr << "No graph currently loaded!" << std::endl;
						break;
					case 1:
						listGraph->printGraph();
						break;
					case 2:
						matrixGraph->printGraph();
						break;
				}
				break;
			case 5: {
				if(currentGraphType == 0) {
					std::cerr << "No graph currently loaded!" << std::endl;
					break;
				}
				std::string fileName;
				std::cout << "Output file name (leave empty for stdout)? ";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				getline(std::cin, fileName);
				std::ostream& out = fileName == "" ? std::cout : *(new std::ofstream(fileName));
				double solvingTime;
				switch(currentGraphType) {
					case 1:
						solvingTime = bellmanFord(std::move(listGraph), start, true, out);
						break;
					case 2:
						solvingTime = bellmanFord(std::move(matrixGraph), start, true, out);
						break;
				}
				out << "The graph was solved in " << solvingTime << " milliseconds\n";
				break;
			}
			case 6: {
				std::string fileName;
				std::cout << "Output file name (leave empty for stdout): ";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				getline(std::cin, fileName);
				std::ostream& out = fileName == "" ? std::cout : *(new std::ofstream(fileName));
				out << "*** ListGraph\n";
				tests<ListGraph>(out);
				out << "*** MatrixGraph\n";
				tests<MatrixGraph>(out);
				break;
			}
			case 0:
				break;
			default:
				std::cerr << "Incorrect option!" << std::endl;
				op = -1;
				break;
		}
	} while(op != 0);
	return 0;
}

