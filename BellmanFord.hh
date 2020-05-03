#pragma once
#include "MatrixGraph.hh"
#include "ListGraph.hh"
#include <chrono>

double bellmanFord(std::shared_ptr<MatrixGraph> graph, int start, bool printOutput, std::ostream& out = std::cout);
double bellmanFord(std::shared_ptr<ListGraph> graph, int start, bool printOutput, std::ostream& out = std::cout);